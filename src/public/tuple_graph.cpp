#include "../private/dlplan/include/dlplan/novelty.h"
#include "../private/dlplan/include/dlplan/state_space.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    if (argc != 5) {
        throw std::runtime_error("Correct usage: ./tg <domain:str> <problem:str> <arity:int> <state:int>");
    }
    std::string domain_filename(argv[1]);
    std::string problem_filename(argv[2]);
    int arity = atoi(argv[3]);
    int state_index = atoi(argv[4]);

    auto result = dlplan::state_space::generate_state_space(domain_filename, problem_filename);
    auto state_space = result.state_space;

    auto tuple_graph = dlplan::novelty::TupleGraph(
        std::make_shared<const dlplan::novelty::NoveltyBase>(state_space->get_instance_info()->get_atoms().size(), arity),
        state_space,
        state_index);


    std::ofstream out_file_state_space("state_space.dot");
    out_file_state_space << state_space->to_dot(1);
    out_file_state_space.close();

    std::ofstream out_file("graph.dot");
    out_file << tuple_graph.to_dot(1);
    out_file.close();
    return 0;
}