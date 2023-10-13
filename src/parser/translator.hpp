#ifndef SRC_PARSER_TRANSLATOR_HPP_
#define SRC_PARSER_TRANSLATOR_HPP_

#include <tuple>
#include <variant>

#include "../extended_sketch/declarations.hpp"

#include "ast.hpp"
#include "context.hpp"


namespace sketches::extended_sketch::parser {

/// @brief Translates AST into extended sketches language.
class Translator {
public:
    std::string translate(Context& context, const ast::Name& node) const;
    std::string translate(Context& context, const ast::QuotedString& node) const;

    std::string translate(Context& context, const ast::NameEntry& node) const;

    MemoryState translate(Context& context, const ast::MemoryStateDefinition& node) const;
    MemoryState translate(Context& context, const ast::MemoryStateReference& node) const;
    MemoryStateMap translate(Context& context, const ast::MemoryStatesEntry& node) const;

    Register translate(Context& context, const ast::RegisterDefinition& node) const;
    Register translate(Context& context, const ast::RegisterReference& node) const;
    RegisterMap translate(Context& context, const ast::RegistersEntry& node) const;

    Boolean translate(Context& context, const ast::BooleanDefinition& node) const;
    Boolean translate(Context& context, const ast::BooleanReference& node) const;
    BooleanMap translate(Context& context, const ast::BooleansEntry& node) const;

    Numerical translate(Context& context, const ast::NumericalDefinition& node) const;
    Numerical translate(Context& context, const ast::NumericalReference& node) const;
    NumericalMap translate(Context& context, const ast::NumericalsEntry& node) const;

    Concept translate(Context& context, const ast::ConceptDefinition& node) const;
    Concept translate(Context& context, const ast::ConceptReference& node) const;
    ConceptMap translate(Context& context, const ast::ConceptsEntry& node) const;

    MemoryState translate(Context& context, const ast::MemoryConditionEntry& node) const;
    MemoryState translate(Context& context, const ast::MemoryEffectEntry& node) const;

    Condition translate(Context& context, const ast::PositiveBooleanConditionEntry& node) const;
    Condition translate(Context& context, const ast::NegativeBooleanConditionEntry& node) const;
    Condition translate(Context& context, const ast::GreaterNumericalConditionEntry& node) const;
    Condition translate(Context& context, const ast::EqualNumericalConditionEntry& node) const;
    Effect translate(Context& context, const ast::PositiveBooleanEffectEntry& node) const;
    Effect translate(Context& context, const ast::NegativeBooleanEffectEntry& node) const;
    Effect translate(Context& context, const ast::UnchangedBooleanEffectEntry& node) const;
    Effect translate(Context& context, const ast::IncrementNumericalEffectEntry& node) const;
    Effect translate(Context& context, const ast::DecrementNumericalEffectEntry& node) const;
    Effect translate(Context& context, const ast::UnchangedNumericalEffectEntry& node) const;

    Condition translate(Context& context, const ast::FeatureConditionEntry& node) const;
    Effect translate(Context& context, const ast::FeatureEffectEntry& node) const;

    LoadRule translate(Context& context, const ast::LoadRuleEntry& node) const;
    CallRule translate(Context& context, const ast::CallRuleEntry& node) const;
    ActionRule translate(Context& context, const ast::ActionRuleEntry& node) const;
    SearchRule translate(Context& context, const ast::SearchRuleEntry& node) const;

    std::variant<LoadRule, CallRule, ActionRule, SearchRule>
    translate(Context& context, const ast::RuleEntry& node) const;

    std::tuple<LoadRuleList, CallRuleList, ActionRuleList, SearchRuleList>
    translate(Context& context, const ast::Rules& node) const;

    ExtendedSketch translate(Context& context, const ast::ExtendedSketch& node) const;
};

}

#endif

