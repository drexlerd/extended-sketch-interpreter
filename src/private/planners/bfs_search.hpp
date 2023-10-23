#if !defined(PLANNERS_BFS_SEARCH_HPP_)
#define PLANNERS_BFS_SEARCH_HPP_

#include "../formalism/action.hpp"
#include "../formalism/domain.hpp"
#include "../formalism/problem.hpp"
#include "../generators/successor_generator_factory.hpp"

#include <vector>

namespace std {

template<class T, size_t C>
std::ostream &operator<<(std::ostream &stream, const std::array<T, C> &arr) {
    stream << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i != 0)
            stream << ", ";
        stream << arr[i];
    }
    stream << "]";
    return stream;
}


template<class T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &vec) {
    stream << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0)
            stream << ", ";
        stream << vec[i];
    }
    stream << "]";
    return stream;
}

template<class T>
std::ostream &operator<<(std::ostream &stream, const std::unordered_set<T> &set) {
    stream << "{";
    for (size_t i = 0; i < set.size(); ++i) {
        if (i != 0)
            stream << ", ";
        stream << set[i];
    }
    stream << "}";
    return stream;
}

template<class T, class U>
std::ostream &operator<<(std::ostream &stream, const std::pair<T, U> &pair) {
    stream << "<" << pair.first << "," << pair.second << ">";
    return stream;
}

}

namespace planners
{
    class BreadthFirstSearch
    {
      protected:
        formalism::ProblemDescription problem_;
        planners::SuccessorGeneratorType successor_generator_type_;
        bool print_;

      public:
        uint32_t generated;
        uint32_t expanded;
        uint32_t max_expanded;

        int64_t time_total_ns;
        int64_t time_successors_ns;

        BreadthFirstSearch(const formalism::ProblemDescription& problem, planners::SuccessorGeneratorType successor_generator_type);

        bool find_plan(std::vector<formalism::Action>& plan);

        void print_progress(bool flag);

        void set_max_expanded(uint32_t max);
    };
}  // namespace planners

#endif  // PLANNERS_BFS_SEARCH_HPP_
