#include "driver.hpp"

#include <fstream>

#include "common/error_handler.hpp"
#include "stage_1_ast/parser.hpp"
#include "stage_2_sketch/parser.hpp"


namespace sketches::extended_sketch::parser {

Driver::Driver(const fs::path& sketch_path)
    : m_sketch_path(sketch_path) { }

ExtendedSketch Driver::parse(
    const mimir::formalism::DomainDescription& domain_description,
    std::shared_ptr<dlplan::core::SyntacticElementFactory> factory,
    std::shared_ptr<dlplan::policy::PolicyBuilder> builder) {

    std::ifstream sketch_stream(this->m_sketch_path.c_str());
    if (sketch_stream.is_open()) {
        std::stringstream buffer;
        buffer << sketch_stream.rdbuf();
        std::string source = buffer.str();

        // Stage 1 parse
        auto result = parse_ast(source);

        // Stage 2 parse
        Context context(domain_description, factory, builder);
        auto sketch = parse_sketch(context, result.error_handler, result.root_node);

        return sketch;
    }
    throw std::runtime_error("extended sketch file does not exist");
}

}
