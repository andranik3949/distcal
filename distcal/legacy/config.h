#pragma once

#include <iostream>
#include <string>

#include "../utilities/log.h"
#include "cmdline.h"

namespace distcal
{
   namespace config
   {
      namespace
      {
         const size_t      default_verbosity   = Log::Level::INFO;
         const std::string default_log_file    = "";
         const bool        default_no_log      = false;
         const bool        default_console_log = false;

         const std::string default_data_file   = "";
         const std::string default_query_file  = "";
         const size_t      default_data_count  = 1024;
         const size_t      default_query_count = 1024;
         const size_t      default_dimension   = 512;

      }; //namespace

      /// @brief Holds all the configurable values 
      struct Config
      {
      public:
         /// @brief Parses command line parameters and sets appropriate values
         /// 
         /// Also initalizes logging
         Config(int argc, char* argv[]);

      private:
         CommandLine commandline;

      public:
         size_t      verbosity;
         std::string log_file;
         bool        no_log;
         bool        console_log;

         std::string data_file;
         std::string query_file;
         size_t      data_count;
         size_t      query_count;
         size_t      dimension;
      };

      std::ostream& operator <<( std::ostream& out, const Config& rhs );

   }; //namespace config
}; //namespace distcal