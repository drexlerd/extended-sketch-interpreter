#ifndef SRC_PARSER_COMMON_CONFIG_HPP_
#define SRC_PARSER_COMMON_CONFIG_HPP_

#include <boost/spirit/home/x3.hpp>

#include "error_handler.hpp"


namespace sketches::extended_sketch { namespace parser
{
    // Our Iterator Type
    typedef std::string::const_iterator iterator_type;

    // The Phrase Parse Context
    typedef
        x3::phrase_parse_context<x3::ascii::space_type>::type
    phrase_context_type;

    // Our Error Handler
    typedef error_handler<iterator_type> error_handler_type;

    // Combined Error Handler and Phrase Parse Context
    typedef x3::context<
        error_handler_tag
      , std::reference_wrapper<error_handler_type>
      , phrase_context_type>
    context_type;
}}

#endif