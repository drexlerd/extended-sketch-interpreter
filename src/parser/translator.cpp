#include "translator.hpp"

#include <sstream>

#include "../extended_sketch/memory_state.hpp"
#include "../extended_sketch/register.hpp"
#include "../extended_sketch/features.hpp"


namespace sketches::extended_sketch::parser {

static std::string translate(Context& context, const error_handler_type& error_handler, const ast::Name& node) {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;;
    return ss.str();
}

static std::string translate(Context& context, const error_handler_type& error_handler, const ast::QuotedString& node) {
    return node.characters;
}

static std::string translate(Context& context, const error_handler_type& error_handler, const ast::NameEntry& node) {
    return translate(context, error_handler, node.name);
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryStateDefinition& node) {
    return context.memory_state_factory.make_memory_state(translate(context, error_handler, node.key));
}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryStateReference& node) {
    std::string key = translate(context, error_handler, node.key);
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

static Register translate(Context& context, const error_handler_type& error_handler, const ast::RegisterDefinition& node) {
    return context.register_factory.make_register(translate(context, error_handler, node.key));
}

static Register translate(Context& context, const error_handler_type& error_handler, const ast::RegisterReference& node) {
    std::string key = translate(context, error_handler, node.key);
    auto register_ = context.register_factory.get_register(key);
    if (!register_) {
        error_handler(node, "undefined register state " + key);
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

}

static Boolean translate(Context& context, const error_handler_type& error_handler, const ast::BooleanReference& node) {

}

static BooleanMap translate(Context& context, const error_handler_type& error_handler, const ast::BooleansEntry& node) {

}

static Numerical translate(Context& context, const error_handler_type& error_handler, const ast::NumericalDefinition& node) {

}

static Numerical translate(Context& context, const error_handler_type& error_handler, const ast::NumericalReference& node) {

}

static NumericalMap translate(Context& context, const error_handler_type& error_handler, const ast::NumericalsEntry& node) {

}

static Concept translate(Context& context, const error_handler_type& error_handler, const ast::ConceptDefinition& node) {

}

static Concept translate(Context& context, const error_handler_type& error_handler, const ast::ConceptReference& node) {

}

static ConceptMap translate(Context& context, const error_handler_type& error_handler, const ast::ConceptsEntry& node) {

}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryConditionEntry& node) {

}

static MemoryState translate(Context& context, const error_handler_type& error_handler, const ast::MemoryEffectEntry& node) {

}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::PositiveBooleanConditionEntry& node) {

}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::NegativeBooleanConditionEntry& node) {

}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::GreaterNumericalConditionEntry& node) {

}

static Condition translate(Context& context, const error_handler_type& error_handler, const ast::EqualNumericalConditionEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::PositiveBooleanEffectEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::NegativeBooleanEffectEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::UnchangedBooleanEffectEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::IncrementNumericalEffectEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::DecrementNumericalEffectEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::UnchangedNumericalEffectEntry& node) {

}


static Condition translate(Context& context, const error_handler_type& error_handler, const ast::FeatureConditionEntry& node) {

}

static Effect translate(Context& context, const error_handler_type& error_handler, const ast::FeatureEffectEntry& node) {

}


static LoadRule translate(Context& context, const error_handler_type& error_handler, const ast::LoadRuleEntry& node) {

}

static CallRule translate(Context& context, const error_handler_type& error_handler, const ast::CallRuleEntry& node) {

}

static ActionRule translate(Context& context, const error_handler_type& error_handler, const ast::ActionRuleEntry& node) {

}

static SearchRule translate(Context& context, const error_handler_type& error_handler, const ast::SearchRuleEntry& node) {

}


static std::variant<LoadRule, CallRule, ActionRule, SearchRule>
translate(Context& context, const error_handler_type& error_handler, const ast::RuleEntry& node) {

}


static std::tuple<LoadRuleList, CallRuleList, ActionRuleList, SearchRuleList>
translate(Context& context, const error_handler_type& error_handler, const ast::Rules& node) {

}

ExtendedSketch translate(Context& context, const error_handler_type& error_handler, const ast::ExtendedSketch& node) {

}

}