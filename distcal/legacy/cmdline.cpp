#include "cmdline.h"

#include "../utilities/exception.h"

namespace distcal
{
   namespace config
   {  
      CommandLine::CommandLine(int argc, char* argv[])
         :m_args {
            std::make_pair(option_verbosity,     Value()),          //C++11 <3
            std::make_pair(option_log_file,      Value()),
            std::make_pair(option_no_log,        Value()),
            std::make_pair(option_console_log,   Value()),

            std::make_pair(option_data_file,     Value()),
            std::make_pair(option_queries_file,  Value()),
            std::make_pair(option_data_count,    Value()),
            std::make_pair(option_queries_count, Value()),
            std::make_pair(option_dimension,     Value()), }
      {
         for( int i = 1; i < argc; ++i )
         {
            if( argv[i][0] == '-' )
            {
               auto it = find(argv[i]);
               if( it == m_args.end() )
               {
                  throw ConfigException("Invalid option " + std::string(argv[i]));
               }

               if( it->first.isFlag() )
               {
                  it->second = "true";
                  continue;
               }

               ++i;
               if( i >= argc || argv[i][0] == '-' )
               {
                  throw ConfigException("No value for option " + std::string(argv[i - 1]));
               }

               it->second = argv[i];
            }
         }
      }

      Value CommandLine::get(const Option& flag)
      {
         for( auto it = m_args.begin(); it != m_args.end(); ++it )
         {
            if( flag == it->first )
            {
               return it->second;
            }
         }
         return Value();
      }

      CommandLine::Arguments::iterator CommandLine::find( std::string argument )
      {
         for( auto it = m_args.begin(); it != m_args.end(); ++it )
         {
            if( it->first.compare(argument) )
            {
               return it;
            }
         }
         return m_args.end();
      }

   }; //namespace config
}; //namespace distcal