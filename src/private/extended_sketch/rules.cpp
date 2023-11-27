#include "rules.hpp"

#include <sstream>

#include "extended_sketch.hpp"
#include "module.hpp"
#include "memory_state.hpp"
#include "register.hpp"
#include "../formalism/state.hpp"
#include "../dlplan/include/dlplan/core.h"
#include "../generators/lifted_successor_generator.hpp"
#include "../planners/atom_registry.hpp"
#include "../planners/dlplan_utils.hpp"


namespace mimir::extended_sketch {

ExtendedRuleImpl::ExtendedRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : m_memory_state_condition(memory_state_condition),
      m_memory_state_effect(memory_state_effect),
      m_feature_conditions(feature_conditions),
      m_feature_effects(feature_effects) { }

ExtendedRuleImpl::~ExtendedRuleImpl() = default;

std::string ExtendedRuleImpl::compute_signature() const {
    std::stringstream ss;
    compute_signature(ss);
    return ss.str();
}

const MemoryState& ExtendedRuleImpl::get_memory_state_condition() const {
    return m_memory_state_condition;
}

const MemoryState& ExtendedRuleImpl::get_memory_state_effect() const {
    return m_memory_state_effect;
}

const ConditionSet& ExtendedRuleImpl::get_feature_conditions() const {
    return m_feature_conditions;
}

const EffectSet& ExtendedRuleImpl::get_feature_effects() const {
    return m_feature_effects;
}

bool ExtendedRuleImpl::evaluate_conditions(const ExtendedState& state) const {
    if (state.memory != m_memory_state_condition) return false;
    for (const auto& feature_condition : m_feature_conditions) {
        if (!feature_condition->evaluate(*state.dlplan)) return false;
    }
    return true;
}


LoadRuleImpl::LoadRuleImpl(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Concept& reg,
    const Concept& concept)
    : ExtendedRuleImpl(condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_register(reg), m_concept(concept) { }

LoadRuleImpl::~LoadRuleImpl() = default;

void LoadRuleImpl::apply(
    const ExtendedState& current_state,
    const std::unordered_map<Concept, int>& register_mapping,
    ExtendedState& successor_state) {
    const auto denotation = m_concept->get_element()->evaluate(*current_state.dlplan);
    if (denotation.size() == 0) {
        throw std::runtime_error("Tried to load object from empty concept into register");
    }
    int object_index = denotation.to_sorted_vector().front();
    std::vector<int> register_contents = current_state.dlplan->get_state_extension()->get_register_contents();
    register_contents[register_mapping.at(m_register)] = object_index;

    successor_state = ExtendedState {
        get_memory_state_effect(),
        current_state.mimir,
        std::make_shared<dlplan::core::State>(
            current_state.dlplan->get_index(),
            current_state.dlplan->get_instance_info(),
            current_state.dlplan->get_atom_indices(),
            std::make_shared<dlplan::core::StateExtension>(
                register_contents,
                current_state.dlplan->get_state_extension()->get_concept_argument_contents(),
                std::vector<dlplan::core::RoleDenotation>{}))  // We keep the state the same, hence we cannot use caching
    };

    const std::string& object_name = current_state.dlplan->get_instance_info()->get_objects()[object_index].get_name();
    std::cout << "    Set content of register " << m_register->get_key() << " to object " << object_name << std::endl;
    std::cout << "    Set current memory state to " << get_memory_state_effect()->compute_signature() << std::endl;
}

void LoadRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:load_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str() << " ";
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    for (const auto& effect : m_feature_effects) {
        out << effect->str() << " ";
    }
    out << "(:load (" << m_register->get_key() << " " << m_concept->get_key() << ")) ";
    out << ") ";  // effects
    out << ")";  // rule
}

LoadRule make_load_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const Concept& reg,
    const Concept& concept) {
    return std::make_shared<LoadRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects,
        reg, concept);
}


CallRuleImpl::CallRuleImpl(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const ModuleCall& call)
    : ExtendedRuleImpl(condition_memory_state, effect_memory_state, feature_conditions, feature_effects),
      m_call(call),
      m_callee() { }

CallRuleImpl::~CallRuleImpl() = default;

void CallRuleImpl::apply(
    const ExtendedState& current_state,
    ExtendedState& successor_state,
    Module& callee,
    ExtendedState& callee_state) {
    // Only memory state of current state changes to m'
    successor_state = current_state;
    std::cout << "    Set memory state in caller: " << get_memory_state_effect()->compute_signature() << std::endl;
    successor_state.memory = get_memory_state_effect();
    // Get a shared reference to the callee
    callee = m_callee.lock();
    std::cout << "    Callee: " << callee->get_signature().compute_signature() << std::endl;
    // Initialize the registers with 0
    std::vector<int> register_contents(callee->get_extended_sketch()->get_register_mapping().size(), 0);
    // Evaluate the arguments.
    std::cout << "    Arguments: ";
    std::vector<dlplan::core::ConceptDenotation> argument_contents;
    for (const auto& concept : m_call.get_concept_arguments()) {
        auto denotation = concept->get_element()->evaluate(*current_state.dlplan);
        std::cout << mimir::planners::to_string(*current_state.dlplan->get_instance_info(), denotation) << " ";
        argument_contents.push_back(denotation);
    }
    std::cout << std::endl;
    callee_state = ExtendedState {
        callee->get_extended_sketch()->get_initial_memory_state(),
        current_state.mimir,
        std::make_shared<dlplan::core::State>(
            current_state.dlplan->get_index(),
            current_state.dlplan->get_instance_info(),
            current_state.dlplan->get_atom_indices(),
            std::make_shared<dlplan::core::StateExtension>(register_contents, argument_contents, std::vector<dlplan::core::RoleDenotation>{}))  // We keep the state the same, hence we cannot use caching
    };
    std::cout << "    Initial memory state in callee: " << callee->get_extended_sketch()->get_initial_memory_state()->compute_signature() << std::endl;
}

const ModuleCall& CallRuleImpl::get_call() const {
    return m_call;
}

void CallRuleImpl::set_callee(const Module& module) {
    m_callee = module;
}

void CallRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:call_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str() << " ";
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    out << "(:call " << m_call.compute_signature() << ") ";
    out << ") ";  // effects
    out << ")";  // rule
}

CallRule make_call_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const ModuleCall& call) {
    return std::make_shared<CallRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects,
        call);
}


ActionRuleImpl::ActionRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const ActionCall& call)
    : ExtendedRuleImpl( memory_state_condition, memory_state_effect, feature_conditions, feature_effects),
      m_call(call) { }

ActionRuleImpl::~ActionRuleImpl() = default;

void ActionRuleImpl::apply(
    const mimir::formalism::ProblemDescription& problem,
    const ExtendedState& current_state,
    ExtendedState& successor_state,
    mimir::formalism::Action& action) {
    mimir::planners::LiftedSchemaSuccessorGenerator schema_successor_generator(m_call.get_action_schema(), problem);
    std::vector<dlplan::core::ConceptDenotation> denotations;
    std::cout << current_state.dlplan->str() << std::endl;
    std::cout << "    Denotations: ";
    for (const auto& concept : m_call.get_arguments()) {
        dlplan::core::ConceptDenotation denotation = concept->get_element()->evaluate(*current_state.dlplan);
        denotations.push_back(denotation);
        std::cout << concept->get_key() << "=" << mimir::planners::to_string(*current_state.dlplan->get_instance_info(), denotation) << " ";
    }
    std::cout << std::endl;
    std::cout << "    Arguments: ";
    mimir::formalism::ObjectList object_list;
    for (size_t i = 0; i < denotations.size(); ++i) {
        const auto& denotation = denotations[i];
        if (denotation.empty()) {
            throw std::runtime_error("Cannot apply action " + m_call.get_action_schema()->name + " because of empty denotation.");
        }
        auto object = problem->get_object(denotation.to_sorted_vector().front());
        std::cout << m_call.get_arguments()[i]->get_key() << "=" << object << " ";
        object_list.push_back(object);
    }
    std::cout << std::endl;
    action = schema_successor_generator.create_action(std::move(object_list));
    std::cout << "    Action: " << action << std::endl;
    auto successor_state_mimir = mimir::formalism::apply(action, current_state.mimir);
    auto instance_info = current_state.dlplan->get_instance_info();
    mimir::planners::DLPlanAtomRegistry atom_registry(problem, instance_info);

    successor_state.memory = get_memory_state_effect();
    successor_state.mimir = successor_state_mimir;
    successor_state.dlplan = std::make_shared<dlplan::core::State>(
        current_state.dlplan->get_index(),
        current_state.dlplan->get_instance_info(),
        atom_registry.convert_state(successor_state_mimir),
        current_state.dlplan->get_state_extension());
    std::cout << "    Set current memory state to " << successor_state.memory->compute_signature() << std::endl;
}

void ActionRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:action_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str() << " ";
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    out << "(:action " << m_call.compute_signature() << ") ";
    out << ") ";  // effects
    out << ")";  // rule
}

ActionRule make_action_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects,
    const ActionCall& call) {
    return std::make_shared<ActionRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects,
        call);
}


SearchRuleImpl::SearchRuleImpl(
    const MemoryState& memory_state_condition,
    const MemoryState& memory_state_effect,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects)
    : ExtendedRuleImpl(memory_state_condition, memory_state_effect, feature_conditions, feature_effects) { }

SearchRuleImpl::~SearchRuleImpl() = default;

void SearchRuleImpl::compute_signature(std::stringstream& out) const {
    out << "(:search_rule "
        << "(:conditions ";
    out << "(:memory " << m_memory_state_condition->name << ") ";
    for (const auto& condition : m_feature_conditions) {
        out << condition->str() << " ";
    }
    out << ") ";  // conditions
    out << "(:effects ";
    out << "(:memory " << m_memory_state_effect->name << ") ";
    for (const auto& effect : m_feature_effects) {
        out << effect->str() << " ";
    }
    out << ") ";  // effects
    out << ")";  // rule
}

SearchRule make_search_rule(
    const MemoryState& condition_memory_state,
    const MemoryState& effect_memory_state,
    const ConditionSet& feature_conditions,
    const EffectSet& feature_effects) {
    return std::make_shared<SearchRuleImpl>(
        condition_memory_state, effect_memory_state,
        feature_conditions, feature_effects);
}

}