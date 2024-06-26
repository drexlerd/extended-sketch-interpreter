#include <string>
#include <iostream>

#include "../private/dlplan/include/dlplan/common/parsers/filesystem.hpp"
#include "../private/dlplan/include/dlplan/core.h"
#include "../private/dlplan/include/dlplan/policy.h"
#include "../private/formalism/domain.hpp"
#include "../private/pddl/pddl_parser.hpp"

#include "../private/extended_sketch/module.hpp"
#include "../private/parsers/driver.hpp"
#include "../private/parsers/semantic/parser.hpp"
#include "../private/parsers/semantic/context.hpp"
#include "../private/planners/siw_m.hpp"


using namespace std;
using namespace dlplan;
using namespace dlplan::core;
using namespace dlplan::policy;
using namespace mimir::formalism;
using namespace mimir::parsers;
using namespace mimir::extended_sketch;


shared_ptr<VocabularyInfo>
construct_vocabulary_info(const DomainDescription& domain_description) {
    shared_ptr<VocabularyInfo> vocabulary_info = make_shared<VocabularyInfo>();
    for (const auto& constant : domain_description->constants) {
        vocabulary_info->add_constant(constant->name);
    }
    for (const auto& predicate : domain_description->static_predicates) {
        vocabulary_info->add_predicate(predicate->name, predicate->arity, true);
    }
    for (const auto& predicate : domain_description->predicates) {
        vocabulary_info->add_predicate(predicate->name, predicate->arity, false);
        vocabulary_info->add_predicate(predicate->name + "_g", predicate->arity, false);
    }
    return vocabulary_info;
}

shared_ptr<InstanceInfo>
construct_instance_info(
    shared_ptr<VocabularyInfo> vocabulary_info,
    const ProblemDescription& problem_description) {
    shared_ptr<InstanceInfo> instance_info = make_shared<InstanceInfo>(0, vocabulary_info);
    for (const auto& object : problem_description->objects) {
        instance_info->add_object(object->name);
    }
    for (const auto& static_atom : problem_description->get_static_atoms()) {
        std::vector<std::string> object_names;
        for (const auto& argument : static_atom->arguments) {
            object_names.push_back(argument->name);
        }
        instance_info->add_static_atom(static_atom->predicate->name, object_names);
    }
    for (const auto& atom : problem_description->goal) {
        std::vector<std::string> object_names;
        for (const auto& argument : atom->atom->arguments) {
            object_names.push_back(argument->name);
        }
        instance_info->add_static_atom(atom->atom->predicate->name + "_g", object_names);
    }
    return instance_info;
}


int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: interpreter <domain:str> <problem:str> <modules:str>" << endl;
        return 1;
    }
    string domain_file = argv[1];
    string problem_file = argv[2];
    string sketch_file = argv[3];

    // 1. Parse the domain
    DomainParser domain_parser(domain_file);
    auto domain_description = domain_parser.parse();
    // 2. Parse the problem
    ProblemParser problem_parser(problem_file);
    // 3. Initialize DLPlan
    auto problem_description = problem_parser.parse(domain_description);
    auto vocabulary_info = construct_vocabulary_info(domain_description);
    auto instance_info = construct_instance_info(vocabulary_info, problem_description);
    auto element_factory = make_shared<SyntacticElementFactory>(vocabulary_info);
    // 4. Parse the extended sketch
    const auto source = read_file(sketch_file);
    iterator_type iter(source.begin());
    iterator_type const end(source.end());
    error_handler_type error_handler(iter, end, std::cerr, sketch_file);
    ModuleList modules;
    while (iter != end) {
        auto policy_factory = make_shared<PolicyFactory>(element_factory);
        Driver driver(domain_description, policy_factory);
        mimir::extended_sketch::Context context(domain_description, policy_factory);
        auto module_ = driver.parse_module(iter, end, error_handler, context, sketch_file);
        modules.push_back(module_);
        cout << module_->compute_signature() << endl;
    }
    resolve_function_calls(modules);
    if (modules.empty()) {
        throw std::runtime_error("Modules is empty");
    }
    // 4. Run SIW_M
    int max_arity = 2;
    mimir::planners::SIWMSearch siwm(domain_description, problem_description, instance_info, modules, mimir::planners::SuccessorGeneratorType::LIFTED, max_arity);
    mimir::formalism::ActionList plan;
    bool solution_found = siwm.find_plan(plan);
    if (solution_found) {
        std::cout << std::endl << "Solution found!" << std::endl;
        siwm.print_statistics();
        std::cout << "Plan cost: " << plan.size() << std::endl;
        for (const auto& action : plan) {
            std::cout << action << std::endl;
        }
    } else {
        std::cout << std::endl << "No solution found!" << std::endl;
    }

    return 0;
}


// cmake -S . -B build && cmake --build build -j16 && ./build/src/public/siw_m benchmarks/blocks-tower/domain.pddl benchmarks/blocks-tower/p-4-0.pddl benchmarks/blocks-tower/module.pddl