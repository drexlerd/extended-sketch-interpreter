#include "driver.hpp"

#include <cassert>
#include <fstream>


#include "syntactic/parser.hpp"
#include "semantic/parser.hpp"


using namespace dlplan;
using namespace mimir::extended_sketch;


namespace mimir::extended_sketch {

Driver::Driver(
    const mimir::formalism::DomainDescription& domain_description,
    const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory)
    : domain_description(domain_description),
      policy_factory(policy_factory) { }

ExtendedSketch Driver::parse_sketch(
    const std::string& source,
    const std::string& filename) {

    iterator_type iter(source.begin());
    iterator_type const end(source.end());

    error_handler_type error_handler(iter, end, std::cerr, filename);

    Context context(domain_description, policy_factory);

    return parse_sketch(iter, end, error_handler, context, filename);
}

ExtendedSketch Driver::parse_sketch(
    iterator_type& iter,
    iterator_type end,
    error_handler_type& error_handler,
    Context& context,
    const std::string& filename) {

    // Stage 1 parse
    auto root_node = parse_sketch_ast(iter, end, error_handler);

    // Stage 2 parse
    auto sketch = parse(root_node, error_handler, context);

    return sketch;
}


Module Driver::parse_module(
    const std::string& source,
    const std::string& filename) {

    iterator_type iter(source.begin());
    iterator_type const end(source.end());

    error_handler_type error_handler(iter, end, std::cerr, filename);

    Context context(domain_description, policy_factory);

    return parse_module(iter, end, error_handler, context, filename);
}

Module Driver::parse_module(
    iterator_type& iter,
    iterator_type end,
    error_handler_type& error_handler,
    Context& context,
    const std::string& filename) {

    // Stage 1 parse
    auto root_node = parse_module_ast(iter, end, error_handler);

    // Stage 2 parse
    auto module_ = parse(root_node, error_handler, context);

    return module_;
}

}
