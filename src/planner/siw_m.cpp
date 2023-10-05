
#include <iostream>
#include <vector>

#include "../external/mimir/pddl/parsers.hpp"


using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: interpreter <domain:str> <problem:str> [<module:Module>,...]" << std::endl;
        return 1;
    }
    string domain_file = argv[1];
    string problem_file = argv[2];
    vector<string> module_files;
    for (size_t i = 3; i < argc; ++i) {
        module_files.push_back(argv[i]);
    }

    // 1. Parse the domain
    parsers::DomainParser domain_parser(domain_file);
    auto domain_description = domain_parser.parse();
    // 2. Parse the problem
    parsers::ProblemParser problem_parser(problem_file);
    auto problem_description = problem_parser.parse(domain_description);
    // 3. Parse the modules
    // 4. Run SIW_M
    return 0;
}