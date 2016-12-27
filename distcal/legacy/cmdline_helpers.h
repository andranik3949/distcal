#pragma once

#include <string>

namespace distcal
{
   namespace config
   {
      /// @brief Helper struct for storing and casting raw string values to actual value
      struct Value
      {
         Value(std::string raw = "")
            :m_raw(raw)
         { }

         void operator =(const std::string& rhs) { m_raw = rhs; }
         bool empty() const { return m_raw.empty(); }

         explicit operator std::string() const;
         explicit operator size_t()      const;
         explicit operator bool()        const;

      private:
         std::string m_raw;
      };


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

         bool operator ==(const Option& rhs) const
         {
            return this->m_short == rhs.m_short && this->m_long == rhs.m_long;
         }

      private:
         std::string m_short;
         std::string m_long;

         bool m_isFlag;
      };

   }; //namespace config
}; //namespace distcal