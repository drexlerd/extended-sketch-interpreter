#if !defined(PDDL_PROBLEM_PARSER_HPP_)
#define PDDL_PROBLEM_PARSER_HPP_

#include <memory>

#include "../formalism/domain.hpp"


// Older versions of LibC++ does not have filesystem (e.g., ubuntu 18.04), use the experimental version
// https://stackoverflow.com/questions/55474690/stdfilesystem-has-not-been-declared-after-including-experimental-filesystem
#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#  if __cplusplus >= 201703L && __has_include(<filesystem>)
#    include <filesystem>
     namespace fs = std::filesystem;
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
     namespace fs = std::experimental::filesystem;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
     namespace fs = boost::filesystem;
#  endif
#endif


namespace mimir::pddl
{
    class ProblemParser
    {
      private:
        const fs::path problem_path;

      public:
        ProblemParser(const fs::path& problem_path);

        formalism::ProblemDescription parse(const formalism::DomainDescription& domain);
    };
}  // namespace mimir::pddl

#endif  // PDDL_PARSER_DOMAIN_HPP_
