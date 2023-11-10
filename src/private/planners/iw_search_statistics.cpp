#include "iw_search_statistics.hpp"

#include <iomanip>


namespace mimir::planners {
    void IWSearchStatistics::print(int num_indent) const { 
        std::string indent(num_indent, ' ');
        std::cout << indent << "Expanded " << expanded << " states" << std::endl;
        std::cout << indent << "Generated " << generated << " states" << std::endl;
        std::cout << indent << "Pruned " << pruned << " states" << std::endl;
        std::cout << indent << "Successor time: " << time_successors_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_successors_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Apply time: " << time_apply_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_apply_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Grounding time: " << time_grounding_ns / (int64_t) 1E6 << " ms"
                    << " (" << std::fixed << std::setprecision(3) << (100.0 * time_grounding_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Goal time: " << time_goal_test_ns / (int64_t) 1E6 << " ms"
                << " (" << std::fixed << std::setprecision(3) << (100.0 * time_goal_test_ns) / time_total_ns << "%)" << std::endl;
        std::cout << indent << "Search time: " << time_search_ns / (int64_t) 1E6 << " ms" << std::endl;
        std::cout << indent << "Total time: " << time_total_ns / (int64_t) 1E6 << " ms" << std::endl;
    }
}