#include "dlplan_utils.hpp"

#include <sstream>
#include <fstream>


namespace mimir::planners {
std::string to_string(
    const dlplan::core::InstanceInfo& instance_info,
    const dlplan::core::ConceptDenotation& denotation) {
    const auto& objects = instance_info.get_objects();
    const auto& object_indices = denotation.to_sorted_vector();
    std::stringstream ss;
    ss << "{";
    for (size_t i = 0; i < object_indices.size(); ++i) {
        if (i != 0) ss << ", ";
        ss << objects[object_indices[i]].get_name();
    }
    ss << "}";
    return ss.str();
}
}