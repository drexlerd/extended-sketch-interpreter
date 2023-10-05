
#include <iostream>
#include <vector>

#include "../external/mimir/pddl/parsers.hpp"
#include "../extended_sketch/parser/parser.hpp"
#include "../extended_sketch/declarations.hpp"

using namespace std;
using namespace sketches::extended_sketch;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: interpreter <domain:str> <problem:str> [<sketch:ExtendedSketch>,...]" << std::endl;
        return 1;
    }
    string domain_file = argv[1];
    string problem_file = argv[2];
    vector<string> sketch_files;
    for (size_t i = 3; i < argc; ++i) {
        sketch_files.push_back(argv[i]);
    }

    // 1. Parse the domain
    mimir::parsers::DomainParser domain_parser(domain_file);
    auto domain_description = domain_parser.parse();
    // 2. Parse the problem
    mimir::parsers::ProblemParser problem_parser(problem_file);
    auto problem_description = problem_parser.parse(domain_description);
    // 3. Parse the modules
    ExtendedSketchList sketch_list;
    for (const auto& sketch_file : sketch_files) {
        parser::ExtendedSketchParser sketch_parser(sketch_file);
        sketch_list.push_back(sketch_parser.parse());
    }
    // 4. Run SIW_M
    return 0;
}