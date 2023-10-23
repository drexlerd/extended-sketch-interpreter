#include "utils.hpp"

#include "../private/pddl/parsers.hpp"
#include "../private/planners/iw_search.hpp"
#include "../private/planners/goal_test.hpp"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    if (argc != 5) {
        throw std::runtime_error("Correct usage: ./iw <domain:str> <problem:str> <arity:int> <enable_grounding:bool>");
    }
    std::cout << "Started iw search." << std::endl;
    std::string domain_filename(argv[1]);
    std::string problem_filename(argv[2]);
    int arity = atoi(argv[3]);
    bool enable_grounding = utils::to_bool(argv[4]);
    parsers::DomainParser domain_parser(domain_filename);
    auto domain = domain_parser.parse();
    parsers::ProblemParser problem_parser(problem_filename);
    auto problem = problem_parser.parse(domain);

    auto goal_test = std::make_unique<planners::TopGoalTest>(problem);

    auto successor_generator_type = planners::SuccessorGeneratorType::LIFTED;
    if (enable_grounding) successor_generator_type = planners::SuccessorGeneratorType::GROUNDED;

    planners::IWSearch planner(problem, successor_generator_type, std::move(goal_test), arity);

    formalism::ActionList plan;
    bool found_plan = planner.find_plan(plan);
    std::cout << std::endl;
    std::cout << "Overall search statistics:" << std::endl;
    planner.print_statistics();
    if (found_plan)
    {
        std::cout << "Plan length: " << plan.size() << std::endl;
        std::ofstream plan_file("plan.txt");
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
