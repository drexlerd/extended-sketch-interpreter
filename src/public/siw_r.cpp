#include <string>
#include <iostream>

#include "../private/dlplan/include/dlplan/common/parsers/filesystem.hpp"
#include "../private/dlplan/include/dlplan/core.h"
#include "../private/dlplan/include/dlplan/policy.h"
#include "../private/formalism/domain.hpp"
#include "../private/pddl/pddl_parser.hpp"

#include "../private/extended_sketch/extended_sketch.hpp"
#include "../private/parsers/driver.hpp"
#include "../private/planners/siw_r.hpp"


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
    shared_ptr<InstanceInfo> instance_info = make_shared<InstanceInfo>(vocabulary_info);
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
        std::cout << "Usage: interpreter <domain:str> <problem:str> <sketch:ExtendedSketch>" << std::endl;
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
    auto element_factory = std::make_shared<SyntacticElementFactory>(vocabulary_info);
    auto policy_factory = std::make_shared<PolicyFactory>(element_factory);
    // 4. Parse the extended sketch
    Driver driver(domain_description, policy_factory);
    auto extended_sketch = driver.parse_sketch(read_file(sketch_file), sketch_file);
    std::cout << extended_sketch->compute_signature() << std::endl;
    // 4. Run SIW_R
    int max_arity = 2;
    SIWRSearch siwr(domain_description, problem_description, instance_info, extended_sketch, mimir::planners::SuccessorGeneratorType::LIFTED, max_arity);
    std::vector<mimir::formalism::Action> plan;
    bool solution_found = siwr.find_plan(plan);
    if (solution_found) {
        std::cout << std::endl << "Solution found!" << std::endl;
        siwr.print_statistics();
    } else {
        std::cout << std::endl << "No solution found!" << std::endl;
    }
    return 0;
}


// cmake -S . -B build && cmake --build build -j16 && ./build/src/public/siw_r benchmarks/blocks-4-clear/domain.pddl benchmarks/blocks-4-clear/p-200-0.pddl benchmarks/blocks-4-clear/sketch.pddl