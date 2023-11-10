#if !defined(PLANNERS_IW_SEARCH_STATISTICS_HPP_)
#define PLANNERS_IW_SEARCH_STATISTICS_HPP_


#include <iostream>
#include <limits>


namespace mimir::planners {

    struct IWSearchStatistics {
        uint32_t pruned = 0;
        uint32_t generated = 0;
        uint32_t expanded = 0;
        int effective_arity = std::numeric_limits<int>::max();

        int64_t time_successors_ns = 0;
        int64_t time_apply_ns = 0;
        int64_t time_goal_test_ns = 0;
        int64_t time_grounding_ns = 0;
        int64_t time_search_ns = 0;
        int64_t time_total_ns = 0;

        void operator+=(const IWSearchStatistics& other) {
            pruned += other.pruned;
            generated += other.generated;
            expanded += other.expanded;
            effective_arity = other.effective_arity;  // this is not added but overwritten instead

            time_successors_ns += other.time_successors_ns;
            time_apply_ns += other.time_apply_ns;
            time_goal_test_ns += other.time_goal_test_ns;
            time_grounding_ns += other.time_grounding_ns;
            time_search_ns += other.time_search_ns;
            time_total_ns += other.time_total_ns;
        }

        void print(int num_indent=0) const;
    };
}

#endif
