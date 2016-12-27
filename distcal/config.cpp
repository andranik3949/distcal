#include "config.h"

#include <fstream>
#include <sstream>

#include "utilities/exception.h"
#include "utilities/timestamp.h"

namespace distcal
{
   namespace config
   {
      namespace
      {
         bool file_exists(const std::string& file)
         {
            std::ifstream test(file);
            return test.good();
         }

         std::string generate_log_filename()
         {
            std::string name;
            std::string sign = Timestamp(std::chrono::system_clock::now()).getDatetime();
            char suffix = '0';
            do
            {
               name = "log_" + sign + ".txt";
               sign = sign + "_" + std::to_string(++suffix);
            }
            while( file_exists(name) );
            return name;
         }

         const Option option_verbosity   ("v", "verbosity");
         const Option option_log_file    ("l", "log-file");
         const Option option_no_log      ("" , "no-log", true);
         const Option option_console_log ("" , "console-log", true);

         const Option option_data_file   ("D", "data-file");
         const Option option_query_file  ("Q", "queries-file");
         const Option option_data_count  ("d", "data-count");
         const Option option_query_count ("q", "queries-count");
         const Option option_dimension   ("s", "dimension");

         const Option option_min         ("min" , "");
         const Option option_max         ("max" , "");


         const size_t      default_verbosity   = 2; //Info
         const std::string default_log_file    = "";
         const bool        default_no_log      = false;
         const bool        default_console_log = false;

         const std::string default_data_file   = "";
         const std::string default_query_file  = "";
         const size_t      default_data_count  = 1024;
         const size_t      default_query_count = 1024;
         const size_t      default_dimension   = 512;

         const double      default_min         = -1024.;
         const double      default_max         =  1024.;

      }; //namespace

      Config::Config(int argc, char* argv[])
         :verbosity   ( default_verbosity ),
          log_file    ( default_log_file ),
          console_log ( default_no_log ),
          no_log      ( default_console_log ),

          data_file   ( default_data_file ),
          query_file  ( default_query_file ),
          data_count  ( default_data_count ),
          query_count ( default_query_count ),
          dimension   ( default_dimension ),

          min         ( default_min ),
          max         ( default_max )
      {  
         set(argc, argv);
      }

      void Config::set(int argc, char* argv[])
      {
         std::string commandline = "";
         for( int i = 1; i < argc; ++i )
         {
            commandline += argv[i];
            commandline += " ";
         }
         
         std::istringstream optionsStream(commandline);
         std::string option;
         while( optionsStream >> option )
         {
            if( option_verbosity.compare(option) )
            {
               optionsStream >> verbosity;
               if( verbosity < 0 || verbosity > 3 )
               {
                  throw ConfigException("Invalid verbosity level [" + std::to_string(verbosity) + "]");
               }
            }
            else if( option_log_file.compare(option) )
            {
               optionsStream >> log_file;
            }
            else if( option_console_log.compare(option) )
            {
               console_log = true;
            }
            else if( option_no_log.compare(option) )
            {
               no_log = true;
            }
            else if( option_data_file.compare(option) )
            {
               optionsStream >> data_file;
            }
            else if( option_query_file.compare(option) )
            {
               optionsStream >> query_file;
            }
            else if( option_data_count.compare(option) )
            {
               optionsStream >> data_count;
            }
            else if( option_query_count.compare(option) )
            {
               optionsStream >> query_count;
            }
            else if( option_dimension.compare(option) )
            {
               optionsStream >> dimension;
            }
            else if( option_min.compare(option) )
            {
               optionsStream >> min;
            }
            else if( option_max.compare(option) )
            {
               optionsStream >> max;
            }
            else
            {
               throw ConfigException("Invalid option [" + option + "]");
            }

            if( !optionsStream.good() )
            {
               throw ConfigException("Invalid value for [" + option + "]");
            }
         }

         if( !no_log && !console_log && log_file.empty() )
         {
            log_file = generate_log_filename();
         }
      }

      std::ostream& operator <<( std::ostream& out, const Config& rhs )
      {
         out << "configuration\n";
         out << "\tVerbosity        = <" << rhs.verbosity   << ">\n";
         out << "\tLog Filename     = <" << rhs.log_file    << ">\n"; 
         out << "\tLog Disabled     = <" << rhs.no_log      << ">\n";
         out << "\tLog to console   = <" << rhs.console_log << ">\n";

         out << "\tData Filename    = <" << rhs.data_file   << ">\n";
         out << "\tQuery Filename   = <" << rhs.query_file  << ">\n"; 
         out << "\tData Count       = <" << rhs.data_count  << ">\n"; 
         out << "\tQuery Count      = <" << rhs.query_count << ">\n"; 
         out << "\tVector Dimension = <" << rhs.dimension   << ">\n";

         out << "\tmin Coords       = <" << rhs.min         << ">\n";
         out << "\tmax Coords       = <" << rhs.max         << ">";
         return out;
      }

   }; //namespace config
}; //namespace distcal