#pragma once

#include <string>
#include <list>

#include "cmdline_helpers.h"

namespace distcal
{
   namespace config
   {
      namespace
      {
         const Option option_verbosity     ("v", "verbosity");
         const Option option_log_file      ("l", "log-file");
         const Option option_no_log        ("" , "no-log", true);
         const Option option_console_log   ("" , "console-log", true);

         const Option option_data_file     ("D", "data-file");
         const Option option_queries_file  ("Q", "queries-file");
         const Option option_data_count    ("d", "data-count");
         const Option option_queries_count ("q", "queries-count");
         const Option option_dimension     ("s", "dimension");

      }; //namespace

      /// @brief Helper class for storing and parsing command line arguments
      class CommandLine
      {
      public:
         CommandLine(int argc, char* argv[]);

         Value get(const Option& flag);

      private:
         typedef std::list<std::pair<Option, Value>> Arguments;
         Arguments::iterator find(std::string argument);

         Arguments m_args;
      };

   }; //namespace config
}; //namespace distcal