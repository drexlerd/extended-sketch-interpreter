#include <string>
#include <iostream>

#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/common/parsers/filesystem.hpp"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/core.h"
#include "src/external/mimir-iw/src/private/dlplan/include/dlplan/policy.h"
#include "src/external/mimir-iw/src/private/formalism/domain.hpp"
#include "src/external/mimir-iw/src/private/pddl/pddl_parser.hpp"

#include "src/module/module.hpp"
#include "src/parsers/module/driver.hpp"


using namespace std;


std::shared_ptr<dlplan::core::VocabularyInfo>
construct_vocabulary_info(const mimir::formalism::DomainDescription& domain_description) {
    std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary_info = std::make_shared<dlplan::core::VocabularyInfo>();
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

std::shared_ptr<dlplan::core::InstanceInfo>
construct_instance_info(
    std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary_info,
    const mimir::formalism::ProblemDescription& problem_description) {
    std::shared_ptr<dlplan::core::InstanceInfo> instance_info = std::make_shared<dlplan::core::InstanceInfo>(vocabulary_info);
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
    mimir::parsers::DomainParser domain_parser(domain_file);
    auto domain_description = domain_parser.parse();
    // 2. Parse the problem
    mimir::parsers::ProblemParser problem_parser(problem_file);
    // 3. Initialize DLPlan
    auto problem_description = problem_parser.parse(domain_description);
    auto vocabulary_info = construct_vocabulary_info(domain_description);
    auto instance_info = construct_instance_info(vocabulary_info, problem_description);
    auto element_factory = std::make_shared<dlplan::core::SyntacticElementFactory>(vocabulary_info);
    auto policy_factory = std::make_shared<dlplan::policy::PolicyFactory>(element_factory);
    // 4. Parse the extended sketch
    sketches::parsers::module::Driver driver(domain_description, policy_factory);
    driver.parse(dlplan::common::parsers::read_file(sketch_file), sketch_file);
    // 4. Run SIW_M
    return 0;
}


// cmake -S . -B build && cmake --build build -j16 && ./build/src/planner/siw_r benchmarks/gripper/domain.pddl benchmarks/gripper/p-1-0.pddl benchmarks/gripper/success.sketch