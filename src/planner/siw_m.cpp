
#include <iostream>
#include <memory>
#include <vector>

#include "../external/dlplan/include/dlplan/core.h"
#include "../external/dlplan/include/dlplan/policy.h"

#include "../external/mimir/pddl/domain_parser.hpp"
#include "../external/mimir/pddl/problem_parser.hpp"
#include "../parser/extended_sketch_parser.hpp"
#include "../extended_sketch/declarations.hpp"

using namespace std;
using namespace sketches::extended_sketch;

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
    if (argc < 2) {
        std::cout << "Usage: interpreter <domain:str> <problem:str> [<sketch:ExtendedSketch>,...]" << std::endl;
        return 1;
    }
    string domain_file = argv[1];
    string problem_file = argv[2];
    vector<string> sketch_files;
    for (int i = 3; i < argc; ++i) {
        sketch_files.push_back(argv[i]);
    }

    // 1. Parse the domain
    mimir::pddl::DomainParser domain_parser(domain_file);
    auto domain_description = domain_parser.parse();
    // 2. Parse the problem
    mimir::pddl::ProblemParser problem_parser(problem_file);
    // 3. Initialize DLPlan
    auto problem_description = problem_parser.parse(domain_description);
    auto vocabulary_info = construct_vocabulary_info(domain_description);
    auto instance_info = construct_instance_info(vocabulary_info, problem_description);
    auto syntactic_element_factory = std::make_shared<dlplan::core::SyntacticElementFactory>(vocabulary_info);
    auto policy_builder = std::make_shared<dlplan::policy::PolicyBuilder>();
    // 4. Parse the modules
    ExtendedSketchList sketch_list;
    for (const auto& sketch_file : sketch_files) {
        parser::ExtendedSketchParser sketch_parser(sketch_file);
        sketch_list.push_back(sketch_parser.parse(domain_description, syntactic_element_factory, policy_builder));
    }
    // 4. Run SIW_M
    return 0;
}

// cmake -S . -B build && cmake --build build -j16 && ./build/src/planner/siwm  benchmarks/gripper/domain.pddl benchmarks/gripper/p-1-0.pddl benchmarks/gripper/sketch.pddl