#include "translator.hpp"

#include <sstream>

#include "../external/dlplan/include/dlplan/policy.h"

#include "../extended_sketch/memory_state.hpp"
#include "../extended_sketch/register.hpp"
#include "../extended_sketch/features.hpp"
#include "../extended_sketch/rules.hpp"
#include "../extended_sketch/extended_sketch.hpp"


namespace sketches::extended_sketch::parser {

static std::string translate(Context&, const error_handler_type&, const ast::Name& node) {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;;
    return ss.str();
}

static std::string translate(Context&, const error_handler_type&, const ast::QuotedString& node) {
    return node.characters;
}

static std::string translate(Context& context, const error_handler_type& error_handler, const ast::NameEntry& node) {
    return translate(context, error_handler, node.name);
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryStateDefinition& node) {
    return context.memory_state_factory.make_memory_state(translate(context, error_handler, node.key));
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryStateReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto memory_state = context.memory_state_factory.get_memory_state(key);
    if (!memory_state) {
        error_handler(node, "undefined memory state " + key);
    }
    return memory_state;
}

static MemoryStateMap translate(Context& context, const error_handler_type& error_handler, const ast::MemoryStatesEntry& node) {
    MemoryStateMap memory_states;
    for (const auto& child : node.definitions) {
        auto memory_state = translate(context, error_handler, child);
        memory_states.emplace(memory_state->get_key(), memory_state);
    }
    return memory_states;
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::InitialMemoryStateEntry& node) {
    return translate(context, error_handler, node.reference);
}

static Register translate(Context& context, const error_handler_type& error_handler, const ast::RegisterDefinition& node) {
    return context.register_factory.make_register(translate(context, error_handler, node.key));
}

static Register translate(Context& context, const error_handler_type& error_handler, const ast::RegisterReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto register_ = context.register_factory.get_register(key);
    if (!register_) {
        error_handler(node, "undefined register " + key);
    }
    return register_;
}

static RegisterMap translate(Context& context, const error_handler_type& error_handler, const ast::RegistersEntry& node) {
    RegisterMap registers;
    for (const auto& child : node.definitions) {
        auto register_ = translate(context, error_handler, child);
        registers.emplace(register_->get_key(), register_);
    }
    return registers;
}

static Boolean translate(Context& context, const error_handler_type& error_handler, const ast::BooleanDefinition& node) {
    return context.boolean_factory.make_boolean(
        translate(context, error_handler, node.key),
        translate(context, error_handler, node.repr));
}

static Boolean translate(Context& context, const error_handler_type& error_handler, const ast::BooleanReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto boolean = context.boolean_factory.get_boolean(key);
    if (!boolean) {
        error_handler(node, "undefined boolean " + key);
    }
    return boolean;
}

static BooleanMap translate(Context& context, const error_handler_type& error_handler, const ast::BooleansEntry& node) {
    BooleanMap booleans;
    for (const auto& child : node.definitions) {
        auto boolean = translate(context, error_handler, child);
        booleans.emplace(boolean->get_key(), boolean);
    }
    return booleans;
}

static Numerical translate(Context& context, const error_handler_type& error_handler, const ast::NumericalDefinition& node) {
    return context.numerical_factory.make_numerical(
        translate(context, error_handler, node.key),
        translate(context, error_handler, node.repr));
}

static Numerical translate(Context& context, const error_handler_type& error_handler, const ast::NumericalReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto numerical = context.numerical_factory.get_numerical(key);
    if (!numerical) {
        error_handler(node, "undefined numerical " + key);
    }
    return numerical;
}

static NumericalMap translate(Context& context, const error_handler_type& error_handler, const ast::NumericalsEntry& node) {
    NumericalMap numericals;
    for (const auto& child : node.definitions) {
        auto numerical = translate(context, error_handler, child);
        numericals.emplace(numerical->get_key(), numerical);
    }
    return numericals;
}

static Concept translate(Context& context, const error_handler_type& error_handler, const ast::ConceptDefinition& node) {
    return context.concept_factory.make_concept(
        translate(context, error_handler, node.key),
        translate(context, error_handler, node.repr));
}

static Concept translate(Context& context, const error_handler_type& error_handler, const ast::ConceptReference& node) {
    auto key = translate(context, error_handler, node.key);
    auto concept_ = context.concept_factory.get_concept(key);
    if (!concept_) {
        error_handler(node, "undefined concept " + key);
    }
    return concept_;
}

static ConceptMap translate(Context& context, const error_handler_type& error_handler, const ast::ConceptsEntry& node) {
    ConceptMap concepts;
    for (const auto& child : node.definitions) {
        auto concept_ = translate(context, error_handler, child);
        concepts.emplace(concept_->get_key(), concept_);
    }
    return concepts;
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryConditionEntry& node) {
    return translate(context, error_handler, node.reference);
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryEffectEntry& node) {
    return translate(context, error_handler, node.reference);
}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::PositiveBooleanConditionEntry& node) {
    return context.policy_builder->add_pos_condition(translate(context, error_handler, node.reference)->get_boolean());
}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::NegativeBooleanConditionEntry& node) {
    return context.policy_builder->add_neg_condition(translate(context, error_handler, node.reference)->get_boolean());
}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::GreaterNumericalConditionEntry& node) {
    return context.policy_builder->add_gt_condition(translate(context, error_handler, node.reference)->get_numerical());
}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::EqualNumericalConditionEntry& node) {
    return context.policy_builder->add_eq_condition(translate(context, error_handler, node.reference)->get_numerical());
}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::PositiveBooleanEffectEntry& node) {
    return context.policy_builder->add_pos_effect(translate(context, error_handler, node.reference)->get_boolean());
}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::NegativeBooleanEffectEntry& node) {
    return context.policy_builder->add_neg_effect(translate(context, error_handler, node.reference)->get_boolean());
}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::UnchangedBooleanEffectEntry& node) {
    return context.policy_builder->add_bot_effect(translate(context, error_handler, node.reference)->get_boolean());
}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::IncrementNumericalEffectEntry& node) {
    return context.policy_builder->add_inc_effect(translate(context, error_handler, node.reference)->get_numerical());
}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::DecrementNumericalEffectEntry& node) {
    return context.policy_builder->add_dec_effect(translate(context, error_handler, node.reference)->get_numerical());
}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::UnchangedNumericalEffectEntry& node) {
    return context.policy_builder->add_bot_effect(translate(context, error_handler, node.reference)->get_numerical());
}


class FeatureConditionEntryVisitor : public boost::static_visitor<> {
private:
    Context& context;
    const error_handler_type& error_handler;

public:
    Condition result;

    FeatureConditionEntryVisitor(Context& context, const error_handler_type& error_handler)
        : context(context), error_handler(error_handler) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = translate(context, error_handler, node);
    }
};

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::FeatureConditionEntry& node) {
    FeatureConditionEntryVisitor visitor(context, error_handler);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}


class FeatureEffectEntryVisitor : public boost::static_visitor<> {
private:
    Context& context;
    const error_handler_type& error_handler;

public:
    Effect result;

    FeatureEffectEntryVisitor(Context& context, const error_handler_type& error_handler)
        : context(context), error_handler(error_handler) { }

    template<typename Node>
    void operator()(const Node& node) {
        result = translate(context, error_handler, node);
    }
};

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::FeatureEffectEntry& node) {
    FeatureEffectEntryVisitor visitor(context, error_handler);
    boost::apply_visitor(visitor, node);
    return visitor.result;
}


static LoadRule translate(Context& context, const error_handler_type& error_handler, const ast::LoadRuleEntry& node) {
    auto memory_condition = translate(context, error_handler, node.memory_condition);
    auto memory_effect = translate(context, error_handler, node.memory_effect);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(translate(context, error_handler, condition_node));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(translate(context, error_handler, effect_node));
    }
    auto register_ = translate(context, error_handler, node.register_reference);
    auto concept_ = translate(context, error_handler, node.concept_reference);
    return create_load_rule(memory_condition, memory_effect, feature_conditions, feature_effects, register_, concept_);
}

static CallRule translate(Context& context, const error_handler_type& error_handler, const ast::CallRuleEntry& node) {

}

static ActionRule translate(Context& context, const error_handler_type& error_handler, const ast::ActionRuleEntry& node) {

}

static SearchRule translate(Context& context, const error_handler_type& error_handler, const ast::SearchRuleEntry& node) {
    auto memory_condition = translate(context, error_handler, node.memory_condition);
    auto memory_effect = translate(context, error_handler, node.memory_effect);
    ConditionSet feature_conditions;
    for (const auto& condition_node : node.feature_conditions) {
        feature_conditions.insert(translate(context, error_handler, condition_node));
    }
    EffectSet feature_effects;
    for (const auto& effect_node : node.feature_effects) {
        feature_effects.insert(translate(context, error_handler, effect_node));
    }
    return create_iwsearch_rule(memory_condition, memory_effect, feature_conditions, feature_effects);
}


static std::variant<LoadRule, CallRule, ActionRule, SearchRule>
translate(Context& context, const error_handler_type& error_handler, const ast::RuleEntry& node) {

}


static std::tuple<LoadRuleList, CallRuleList, ActionRuleList, SearchRuleList>
translate(Context& context, const error_handler_type& error_handler, const ast::Rules& node) {

}

ExtendedSketch translate(Context& context, const error_handler_type& error_handler, const ast::ExtendedSketch& node) {
    auto name = translate(context, error_handler, node.name);
    auto memory_states = translate(context, error_handler, node.memory_states);
    auto initial_memory_state = translate(context, error_handler, node.initial_memory_state);
    auto registers = translate(context, error_handler, node.registers);
    auto booleans = translate(context, error_handler, node.booleans);
    auto numericals = translate(context, error_handler, node.numericals);
    auto concepts = translate(context, error_handler, node.concepts);
    auto load_rules = LoadRuleList();
    auto call_rules = CallRuleList();
    auto action_rules = ActionRuleList();
    auto search_rules = SearchRuleList();
    return create_extended_sketch(
        name,
        memory_states, initial_memory_state,
        registers,
        booleans, numericals, concepts,
        load_rules, call_rules, action_rules, search_rules);
}

}