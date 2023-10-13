#include "translator.hpp"

#include <sstream>

#include "../extended_sketch/memory_state.hpp"


namespace sketches::extended_sketch::parser {

std::string Translator::translate(Context& context, const ast::Name& node) const {
    std::stringstream ss;
    ss << node.alphabetical;
    ss << node.suffix;
    return ss.str();
}

std::string Translator::translate(Context& context, const ast::QuotedString& node) const {
    return node.characters;
}

std::string Translator::translate(Context& context, const ast::NameEntry& node) const {
    return translate(context, node.name);
}

MemoryState Translator::translate(Context& context, const ast::MemoryStateDefinition& node) const {
    return context.memory_state_factory.make_memory_state(translate(context, node.key));
}

MemoryState Translator::translate(Context& context, const ast::MemoryStateReference& node) const {
    return context.memory_state_factory.get_memory_state(translate(context, node.key));
}

MemoryStateMap Translator::translate(Context& context, const ast::MemoryStatesEntry& node) const {
    MemoryStateMap memory_states;
    for (const auto& child : node.definitions) {
        auto memory_state = translate(context, child);
        memory_states.emplace(memory_state->get_key(), memory_state);
    }
    return memory_states;
}

Register Translator::translate(Context& context, const ast::RegisterDefinition& node) const {
    return context.register_factory.make_register(translate(context, node.key));
}

Register Translator::translate(Context& context, const ast::RegisterReference& node) const {
    return context.register_factory.get_register(translate(context, node.key));
}

RegisterMap Translator::translate(Context& context, const ast::RegistersEntry& node) const {

}

Boolean Translator::translate(Context& context, const ast::BooleanDefinition& node) const {

}

Boolean Translator::translate(Context& context, const ast::BooleanReference& node) const {

}

BooleanMap Translator::translate(Context& context, const ast::BooleansEntry& node) const {

}

Numerical Translator::translate(Context& context, const ast::NumericalDefinition& node) const {

}

Numerical Translator::translate(Context& context, const ast::NumericalReference& node) const {

}

NumericalMap Translator::translate(Context& context, const ast::NumericalsEntry& node) const {

}

Concept Translator::translate(Context& context, const ast::ConceptDefinition& node) const {

}

Concept Translator::translate(Context& context, const ast::ConceptReference& node) const {

}

ConceptMap Translator::translate(Context& context, const ast::ConceptsEntry& node) const {

}

MemoryState Translator::translate(Context& context, const ast::MemoryConditionEntry& node) const {

}

MemoryState Translator::translate(Context& context, const ast::MemoryEffectEntry& node) const {

}

Condition Translator::translate(Context& context, const ast::PositiveBooleanConditionEntry& node) const {

}

Condition Translator::translate(Context& context, const ast::NegativeBooleanConditionEntry& node) const {

}

Condition Translator::translate(Context& context, const ast::GreaterNumericalConditionEntry& node) const {

}

Condition Translator::translate(Context& context, const ast::EqualNumericalConditionEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::PositiveBooleanEffectEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::NegativeBooleanEffectEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::UnchangedBooleanEffectEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::IncrementNumericalEffectEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::DecrementNumericalEffectEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::UnchangedNumericalEffectEntry& node) const {

}


Condition Translator::translate(Context& context, const ast::FeatureConditionEntry& node) const {

}

Effect Translator::translate(Context& context, const ast::FeatureEffectEntry& node) const {

}


LoadRule Translator::translate(Context& context, const ast::LoadRuleEntry& node) const {

}

CallRule Translator::translate(Context& context, const ast::CallRuleEntry& node) const {

}

ActionRule Translator::translate(Context& context, const ast::ActionRuleEntry& node) const {

}

SearchRule Translator::translate(Context& context, const ast::SearchRuleEntry& node) const {

}


std::variant<LoadRule, CallRule, ActionRule, SearchRule>
Translator::translate(Context& context, const ast::RuleEntry& node) const {

}


std::tuple<LoadRuleList, CallRuleList, ActionRuleList, SearchRuleList>
Translator::translate(Context& context, const ast::Rules& node) const {

}

ExtendedSketch Translator::translate(Context& context, const ast::ExtendedSketch& node) const {

}

}