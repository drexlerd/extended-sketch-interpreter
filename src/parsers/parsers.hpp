#ifndef SRC_PARSERS_PARSERS_HPP_
#define SRC_PARSERS_PARSERS_HPP_

#include <memory>

#include "../external/mimir/formalism/domain.hpp"
#include "../extended_sketch/declarations.hpp"

#include "extended_sketch/context.hpp"


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


namespace mimir::parsers
{
    class DomainParser
    {
      private:
        const fs::path domain_path;

      public:
        DomainParser(const fs::path& domain_path);

        formalism::DomainDescription parse();
    };

    class ProblemParser
    {
      private:
        const fs::path problem_path;

      public:
        ProblemParser(const fs::path& problem_path);

        formalism::ProblemDescription parse(const formalism::DomainDescription& domain);
    };
}  // namespace mimir::parsers

namespace sketches::extended_sketch::parser
{
    class ExtendedSketchParser
    {
      private:
        const fs::path m_sketch_path;

      public:
        ExtendedSketchParser(const fs::path& sketch_path);

        ExtendedSketch parse(Context& context);
    };
}  // namespace sketches::extended_sketch::parsers

#endif  // PDDL_PARSER_DOMAIN_HPP_
