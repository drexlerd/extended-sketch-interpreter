#include "parser_def.hpp"

#include "src/private/dlplan/include/dlplan/common/parsers/config.hpp"

using namespace dlplan;


namespace mimir::extended_sketch::parser
{
    BOOST_SPIRIT_INSTANTIATE(
        name_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        memory_state_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        memory_state_reference_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        memory_states_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        initial_memory_state_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        register_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        register_reference_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        registers_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        memory_condition_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        memory_effect_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        load_rule_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        argument_register_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        argument_concept_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        argument_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        call_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        call_rule_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        action_reference_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        action_rule_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        search_rule_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        rule_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        rules_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        extended_sketch_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        extended_sketch_root_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(
        module_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(
        module_root_type, iterator_type, context_type)
}
