#include "driver.hpp"

#include <cassert>
#include <fstream>


#include "stage_1/parser.hpp"
#include "stage_2/parser.hpp"


using namespace dlplan;
using namespace sketches::extended_sketch;


namespace sketches::parsers::extended_sketch {

Driver::Driver(
    const mimir::formalism::DomainDescription& domain_description,
    const std::shared_ptr<dlplan::policy::PolicyFactory>& policy_factory)
    : domain_description(domain_description),
      policy_factory(policy_factory) { }

ExtendedSketch Driver::parse(
    const std::string& source,
    const std::string& filename) {

    iterator_type iter(source.begin());
    iterator_type const end(source.end());

    return parse(iter, end, filename);
}

ExtendedSketch Driver::parse(
    iterator_type& iter,
    iterator_type end,
    const std::string& filename) {

    // Our error handler
    error_handler_type error_handler(iter, end, std::cerr, filename);

    // Stage 1 parse
    auto root_node = stage_1::parser::parse(iter, end, error_handler);

    // Stage 2 parse
    stage_2::Context context(domain_description, policy_factory);
    auto sketch = stage_2::parser::parse(root_node, error_handler, context);

    return sketch;
}

}
