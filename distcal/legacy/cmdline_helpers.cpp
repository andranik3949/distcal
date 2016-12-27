#include "cmdline_helpers.h"

#include <sstream>

#include "../utilities/exception.h"

namespace distcal
{
   namespace config
   {
      Value::operator std::string() const
      {
         return m_raw;
      }

      Value::operator size_t() const
      {
         size_t result;
         std::istringstream integer(m_raw + " ");
         integer >> result;

         if( !integer.good() )
         {
            throw ConfigException("Invalid size " + m_raw);
         }

         return result;
      }

      Value::operator bool() const
      {
         if( !m_raw.empty() )
         {
            return true;
         }
         return false;
      }

   }; //namespace config
}; //namespace distcal