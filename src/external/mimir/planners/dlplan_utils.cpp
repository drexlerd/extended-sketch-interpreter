#include "dlplan_utils.hpp"

#include <sstream>
#include <fstream>


namespace mimir::planners {
    std::shared_ptr<dlplan::core::VocabularyInfo> construct_vocabulary(
        const formalism::DomainDescription& domain) {
        const auto vocabulary = std::make_shared<dlplan::core::VocabularyInfo>();
        for (const auto& predicate : domain->predicates) {
            vocabulary->add_predicate(predicate->name, predicate->arity, false);
            vocabulary->add_predicate(predicate->name + "_g", predicate->arity, false);  // goal version
        }
        for (const auto& predicate : domain->static_predicates) {
            vocabulary->add_predicate(predicate->name, predicate->arity, true);
        }
        for (const auto& constant : domain->constants) {
            vocabulary->add_constant(constant->name);
        }
        for (const auto& type : domain->types) {
            vocabulary->add_predicate(type->name, 1, true);
        }
        return vocabulary;
    }

    std::shared_ptr<dlplan::core::InstanceInfo> construct_instance(
        const formalism::ProblemDescription& problem,
        std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary) {
        auto instance = std::make_shared<dlplan::core::InstanceInfo>(vocabulary);
        for (const auto object : problem->objects) {
            auto type = object->type;
            while (type != nullptr) {
                instance->add_static_atom(type->name, {object->name});
                type = type->base;
            }
        }
        for (const auto atom : problem->get_static_atoms()) {
            std::vector<std::string> object_names;
            for (const auto& object : atom->arguments) {
                object_names.push_back(object->name);
            }
            instance->add_static_atom(atom->predicate->name, object_names);
        }
        for (const auto literal : problem->goal) {
            if (literal->negated) {
                throw std::runtime_error("Negated goal literals are not supported.");
            }
            const auto atom = literal->atom;
            std::vector<std::string> object_names;
            for (const auto& object : atom->arguments) {
                object_names.push_back(object->name);
            }
            instance->add_static_atom(atom->predicate->name + "_g", object_names);
        }
        return instance;
    }

    dlplan::policy::Policy read_sketch(
        std::shared_ptr<dlplan::core::VocabularyInfo> vocabulary,
        const std::string& sketch_filename) {
        dlplan::core::SyntacticElementFactory factory(vocabulary);
        dlplan::policy::PolicyBuilder builder;
        std::ifstream file(sketch_filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return *dlplan::policy::PolicyReader().read(buffer.str(), builder, factory);
    }
}