#include "config.h"

#include <fstream>

#include "../utilities/log.h"
#include "../utilities/exception.h"
#include "../utilities/timestamp.h"


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
               name = "Log\\log_" + sign + ".txt";
               sign = sign + "_" + (++suffix);     // correct, unless the program is launched more than 10 times in one second, which is quite hard to do
            }
            while( file_exists(name) );
            return name;
         }

         template<typename T> 
         T convert(const Value& value, T defaultValue)
         {
            if( value.empty() )
            {
               return defaultValue;
            }

            return (T)value;
         }

      }; //namespace

      Config::Config(int argc, char* argv[])
         :commandline(argc, argv),
          verbosity   ( convert(commandline.get(option_verbosity),     default_verbosity) ),
          log_file    ( convert(commandline.get(option_log_file),      default_log_file) ),
          console_log ( convert(commandline.get(option_console_log),   default_console_log) ),
          no_log      ( convert(commandline.get(option_no_log),        default_no_log) ),

          data_file   ( convert(commandline.get(option_data_file),     default_data_file) ),
          query_file  ( convert(commandline.get(option_queries_file),  default_query_file) ),
          data_count  ( convert(commandline.get(option_data_count),    default_data_count) ),
          query_count ( convert(commandline.get(option_queries_count), default_query_count) ),
          dimension   ( convert(commandline.get(option_dimension),     default_dimension) )
      {  
         if( verbosity < Log::FATAL || verbosity > Log::DEBUG )
         {
            throw ConfigException("Invalid verbosity level " + std::to_string(verbosity));
         }

         if (!no_log)
         {
            if (!console_log)
            {
               if (log_file.empty())
                  log_file = generate_log_filename();
               Log::instance().init(Log::Level(verbosity), log_file);
            }
            else
            {
               Log::instance().init(Log::Level(verbosity), std::cerr);
            }
         }
         else
         {
            Log::instance().init(Log::Level::DISABLED);
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
         out << "\tVector Dimension = <" << rhs.dimension   << ">";
         return out;
      }

   }; //namespace config
}; //namespace distcal