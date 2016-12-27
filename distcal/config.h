#pragma once

#include <iostream>
#include <string>

namespace distcal
{
   namespace config
   {
      /// @brief Helper struct for storing command line options
      struct Option
      {
         explicit Option(const std::string& shortName, const std::string& longName, bool isFlag = false)
            :m_short(shortName), m_long(longName), m_isFlag(isFlag)
         { }

         std::string getShort() const { return ( m_short.empty() ? "" : "-" + m_short ); }
         std::string getLong()  const { return ( m_long.empty()  ? "" : "--" + m_long ); }
         
         bool isFlag() const { return m_isFlag; }

         bool compare(const std::string& line) const
         {
            return this->getShort() == line || this->getLong() == line;
         }

      private:
         std::string m_short;
         std::string m_long;

         bool m_isFlag;
      };

      /// @brief Holds all the configurable values 
      struct Config
      {
      public:
         /// @brief Parses command line parameters and sets appropriate values
         /// 
         /// Also initalizes logging
         Config(int argc, char* argv[]);

         void set(int argc, char* argv[]);

         size_t      verbosity;
         std::string log_file;
         bool        no_log;
         bool        console_log;

         std::string data_file;
         std::string query_file;
         size_t      data_count;
         size_t      query_count;
         size_t      dimension;

         double      min;
         double      max;
      };

      std::ostream& operator <<( std::ostream& out, const Config& rhs );

   }; //namespace config
}; //namespace distcal