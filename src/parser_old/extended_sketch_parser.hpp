#ifndef SRC_PARSER_EXTENDED_SKETCH_PARSER_HPP_
#define SRC_PARSER_EXTENDED_SKETCH_PARSER_HPP_

#include <memory>

#include "../extended_sketch/declarations.hpp"

#include "../external/dlplan/include/dlplan/core.h"
#include "../external/dlplan/include/dlplan/policy.h"
#include "../external/mimir/formalism/domain.hpp"


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


namespace sketches::extended_sketch::parser
{
    class ExtendedSketchParser
    {
      private:
        const fs::path m_sketch_path;

      public:
        ExtendedSketchParser(const fs::path& sketch_path);

        ExtendedSketch parse(
          const mimir::formalism::DomainDescription& domain_description,
          std::shared_ptr<dlplan::core::SyntacticElementFactory> factory,
          std::shared_ptr<dlplan::policy::PolicyBuilder> builder);
    };
}  // namespace sketches::extended_sketch::parsers

#endif  // PDDL_PARSER_DOMAIN_HPP_
