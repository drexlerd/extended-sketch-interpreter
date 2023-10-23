#include "utils.hpp"

#include "../private/pddl/parsers.hpp"
#include "../private/planners/bfs_search.hpp"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>

using namespace mimir;


int main(int argc, char* argv[]) {
    if (argc != 4) {
        throw std::runtime_error("Correct usage: ./bfrs <domain.pddl> <problem.pddl> <enable_grounding:bool>");
    }
    std::cout << "Started bfrs search." << std::endl;
    std::string domain_filename(argv[1]);
    std::string problem_filename(argv[2]);
    bool enable_grounding = utils::to_bool(argv[3]);
    parsers::DomainParser domain_parser(domain_filename);
    auto domain = domain_parser.parse();
    parsers::ProblemParser problem_parser(problem_filename);
    auto problem = problem_parser.parse(domain);

    auto successor_generator_type = planners::SuccessorGeneratorType::LIFTED;
    if (enable_grounding) successor_generator_type = planners::SuccessorGeneratorType::GROUNDED;

    planners::BreadthFirstSearch planner(problem, successor_generator_type);

    formalism::ActionList plan;
    bool found_plan = planner.find_plan(plan);
    std::cout << "Expanded " << planner.expanded << " states" << std::endl;
    std::cout << "Generated " << planner.generated << " states" << std::endl;
    std::cout << "Successor time: " << planner.time_successors_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * planner.time_successors_ns) / planner.time_total_ns << "%)" << std::endl;
    std::cout << "Total time: " << planner.time_total_ns / (int64_t) 1E6 << " ms" << std::endl;
    std::cout << std::endl;

    if (found_plan)
    {
        std::fstream plan_file("plan.txt");
        for (const auto& action : plan)
        {
            plan_file << action << std::endl;
        }
        plan_file.close();
    } else {
        std::cout << "No solution found!" << std::endl;
    }
    return 0;
}
