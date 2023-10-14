#include "driver.hpp"

#include <cassert>
#include <fstream>

#include "src/parsers/common/utility.hpp"
#include "common/error_handler.hpp"
#include "stage_1_ast/parser.hpp"
#include "stage_2_sketch/parser.hpp"


namespace sketches::parsers::extended_sketch {

Driver::Driver(
    const mimir::formalism::DomainDescription& domain_description,
    const std::shared_ptr<dlplan::core::SyntacticElementFactory>& element_factory,
    const std::shared_ptr<dlplan::policy::PolicyBuilder>& policy_builder)
    : domain_description(domain_description),
      element_factory(element_factory),
      policy_builder(policy_builder) { }

ExtendedSketch Driver::parse(
    const std::string& filename,
    const std::string& source) {

    iterator_type iter(source.begin());
    iterator_type const end(source.end());
    return parse(filename, source, iter, end);
}

ExtendedSketch Driver::parse(
    const std::string& filename,
    const std::string& source,
    iterator_type& iter,
    iterator_type end) {
    assert(in_bounds(source, iter, end));

    // Our error handler
    sketches::parsers::error_handler_type error_handler(iter, end, std::cerr, filename);

    // Stage 1 parse
    auto root_node = stage_1::parser::parse_ast(iter, end, error_handler);

    // Stage 2 parse
    stage_2::Context context(domain_description, element_factory, policy_builder);
    auto sketch = parse_sketch(context, error_handler, root_node);

    return sketch;
}

}
