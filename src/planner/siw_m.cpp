#include <string>
#include <iostream>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/filesystem.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/external/mimir-iw/src/private/pddl/pddl_parser.hpp"

#include "src/extended_sketch/module.hpp"
#include "src/parsers/driver.hpp"
#include "src/parsers/semantic/context.hpp"


using namespace std;
using namespace dlplan;
using namespace dlplan::core;
using namespace dlplan::policy;
using namespace mimir::formalism;
using namespace mimir::parsers;
using namespace sketches::extended_sketch;


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
    auto policy_factory = make_shared<PolicyFactory>(element_factory);
    // 4. Parse the extended sketch
    Driver driver(domain_description, policy_factory);
    const auto source = read_file(sketch_file);
    iterator_type iter(source.begin());
    iterator_type const end(source.end());
    ModuleList modules;
    while (iter != end) {
        sketches::extended_sketch::Context context(domain_description, policy_factory);
        auto module_ = driver.parse_module(iter, end, context, sketch_file);
        modules.push_back(module_);
        cout << module_->compute_signature() << endl;
    }
    // 4. Run SIW_M
    return 0;
}


// cmake -S . -B build && cmake --build build -j16 && ./build/src/planner/siw_r benchmarks/gripper/domain.pddl benchmarks/gripper/p-1-0.pddl benchmarks/gripper/success.sketch