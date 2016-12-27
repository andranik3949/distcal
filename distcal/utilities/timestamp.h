#pragma once

#include <ostream>
#include <string>

#include <chrono>


namespace distcal
{
   /// @brief Helper class, creates timestamps with millisecond precision
   class Timestamp
   {
   public:
      /// @brief Default constructor, initializes everything to 0
      Timestamp();

      /// @brief Constrcuts a timestamp from a std::chrono::time_point 
      /// @param tp, point in time the Timestamp will represent (stupid parameter) 
      Timestamp( std::chrono::time_point<std::chrono::system_clock> tp );

      int mlsec() const { return m_mlsec; }
      int   sec() const { return m_rest.tm_sec; }
      int   min() const { return m_rest.tm_min; }
      int  hour() const { return m_rest.tm_hour; }
      int  mday() const { return m_rest.tm_mday; }
      int   mon() const { return m_rest.tm_mon; }
      int  year() const { return m_rest.tm_year + 1900; }

      /// @brief Returns the timestamp in YYYYMMDD_HHMMSS format
      std::string getDatetime() const;

      /// @brief Returns the timestamp in HH:MM:SS.mmm format
      std::string getTime() const;

   private:
      long long m_absolute; ///< Number of tics in the initial time_point
      int m_mlsec;          ///< Millisecond part of the timestamp
      tm m_rest;            ///< Other parts of the timestamp
   };

   /// @brief Outputs Timestamp instance represented in HH:MM:SS.mmm format
   ///
   /// Used heavily in logging, so to be quicker it doesn't use getTime() 
   std::ostream& operator <<( std::ostream& out, const Timestamp& rhs );

}; //namespace distcal