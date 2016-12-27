#pragma once

#include "timestamp.h"

#include <ostream>
#include <sstream>
#include <string>

#include <memory>

#include <chrono>

#include "../config.h"

namespace distcal
{
   /// @brief Singleton class for logging
	class Log
	{
	public:
      enum Level     ///< Enumerated levels of logs
      {
         DISABLED = -1,
         FATAL    = 0,
         ERROR    = 0,
         WARNING  = 1,
         INFO     = 2,
         DEBUG    = 3
		};

   private:
      /// @brief Helper class, keeps an internal buffer, and dumps to stream on destruction
      class Buffer
      {
      public:
         /// @brief Default constructor
         Buffer() 
         { }

         /// @brief Copy constructor
         Buffer( const Buffer& rhs )
            :m_stream(rhs.m_stream), m_prefix(rhs.m_prefix), m_now( rhs.m_now )
         { }
         
         /// @brief Constrcuts Buffer that will dump to a given stream with a given prefix
         /// @param stream, A stream to which everything in the buffer will be dumped on destruction
         /// @param prefix, The buffer contents will be prefixed with this string, default is empty (no prefix)
         Buffer( std::shared_ptr<std::ostream> stream, const std::string& prefix = std::string() )
            :m_stream(stream), m_prefix(prefix), m_now( std::chrono::system_clock::now() )
         { }

         /// @brief Destructor, dumps internal buffer to the stream, if the stream is initialized and the log message is not empty
         ///
         /// Outputs a timesamp for current time, followed by the prefix, the actual log message and a newline.
         ~Buffer()
         {
            std::string log = m_buf.str();
            if( m_stream && !log.empty() )
            {
               *m_stream << m_now << ": " << m_prefix << log << std::endl;
            }
         }

         /// @brief Output operator that will accept anything that the underlying buffer can
         /// @param item, the data that needs to be output
         /// @return Returns reference to 'this' for subsequent output operator calls
         template <typename Item>
         Buffer& operator << (const Item& item) { return push(item); }

         /// @brief Output operator that will accept any stream manipulator
         /// @param manip, function pointer to the manipulator that need to be applied
         /// @return Returns reference to 'this' for subsequent output operator calls
         Buffer& operator << (std::ostream& (*manip)(std::ostream&)) { return push(manip); }

      private:
         /// @brief Outputs the data to the internal buffer, if the target stream is initialized
         /// @return Returns reference to 'this' for subsequent output operator calls
         template <typename Item>
         Buffer& push(const Item& item)
         {
            if( m_stream != nullptr )
               m_buf << item;
            return *this;
         }

         std::shared_ptr<std::ostream> m_stream; ///< Target stream, if left uninitialized, will prevent any data to be stored in the internal buffer

         std::string m_prefix;                   ///< The contents of the buffer will be prefixed by this
         Timestamp m_now;                        ///< The time when the buffer was created. We consider the time of log to be the start of the call to log
         std::ostringstream m_buf;               ///< The actual buffer, string stream will accomodate for the correct formatting of the output data
      };

	private:
      /// @brief Default constructor
      ///
      /// Private, as this class is a singleton, so the only way to construct Log is to call instance()
		Log()
		{ }

      /// @brief Copy constructor
      ///
      /// Private, as this class is non-copyable
      Log(const Log& rhs)
      { }

   public:
      /// @brief Creates an instance of Log, if it doesn't exist yet
      /// @return Reference to the only Log instance
		static Log& instance() 
      {
         if( m_instance == nullptr )
            m_instance = new Log();
         return *m_instance;
      }

      /// @brief Initializes logging with the given configuration
      /// @param conf, reference to program configuration
      void init(const config::Config& conf);

      /// @brief Unconditional log, will always be logged, independent on the verbosity and will only be prefixed with timestamp
      /// @return A temporary Buffer object, which will process all subsequent Log output operator calls, and dump the message to the Log stream
      static Log::Buffer log();

      static Log::Buffer fatal();
      static Log::Buffer error();
      static Log::Buffer warning();
      static Log::Buffer info();
      static Log::Buffer debug();
		
	private:
      /// @brief Checks if the logging is disabled for a given level
      /// @param level, The level which will be compared to the verbosity
      /// @return true if the level is higher than verbosity (logging for the given level is disabled) or false otherwise
      static bool disabled( Level level ) { return level > m_instance->m_verbosity; }

		Level m_verbosity;                      ///< The current verbosity for logging
		std::shared_ptr<std::ostream> m_stream; ///< The stream to which all messages will be output. This is a ofstream if logging was initialized with a filename

		static Log* m_instance;                 ///< Static pointer to the only Log instance
	};

}; //namespace distcal