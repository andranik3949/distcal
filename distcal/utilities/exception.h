#pragma once

#include <string>

namespace distcal
{
   #define DEF_EXCEPTION( name, description )                    \
   struct name : public std::exception                           \
   {                                                             \
      name(const std::string& msg = std::string())               \
         :m_msg(msg)                                             \
      { }                                                        \
                                                                 \
      virtual const char* what() const { return description; }   \
      std::string msg() const { return m_msg; }                  \
                                                                 \
      const std::string m_msg;                                   \
   };                                                            \

   /// @brief Exception for errors related to error caused by bad configuration 
   DEF_EXCEPTION(ConfigException, "Configuration exception")

   /// @brief Exception for errors related to CSV file processing
   DEF_EXCEPTION(CsvException, "CSV file exception")


}; //namespace distcal