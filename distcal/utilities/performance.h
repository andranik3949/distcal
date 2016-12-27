#pragma once

#include <vector>
#include <queue>

#include <chrono>

namespace distcal
{
   /// @brief Helper class for microsec precision timing
   class Timer
   {
   public:
      /// @brief Default constrcutor
      Timer()
      { }

      /// @brief Starts the timer, sets m_start to now
      void start();

      /// @brief Stops the timer, stores the delta between now and m_start
      void stop();

      /// @brief Getter for the stored duration
      /// @return Returns the latest duration stored by stop()
      std::chrono::microseconds getDuration();

   private:
      std::chrono::duration<double> m_duration;               ///< The duration between any consequent start and stop calls
      std::chrono::high_resolution_clock::time_point m_start; ///< Point in time on which the timer was started.
   };

   /// @brief Helper class for calculating an engine performance
   /// 
   /// Hold a global timer for overall performance, and a container with Timers for each iteration
   class Performance
   {
   public:
      /// @brief Basic struct for passing performance calculation results in microseconds
      struct Result
      {
         Result()
            :m_total(0), m_average(0.), m_count(0)
         { }

         double m_total;
         double m_average;
         long long m_count;
      };

   public:
      /// @brief Default constructor
      Performance()
      { }

      /// @brief Starts the global timer
      void start();

      /// @brief Stops the global timer and stores the result for global performance
      void stop();

      /// @brief Starts a timer for an iteration
      /// @return Returns an index of the timer, that the iteration is tied to.
      ///
      /// Checks if there's a free timer available and uses it, otherwise adds a new one
      int registerIteration();

      /// @brief Stops the timer with given id
      /// @param id, The id of the timer to stop
      ///
      /// After stopping the timer it puts the id into the pool with free timers 
      void endIteration( int id );

      /// @brief Getter for the stored results
      /// @return Result instance containing performance results
      Result getResult() { return m_result; }

   private:
      Timer m_global;                  ///< The global timer for overall performance calculation
      std::vector<Timer> m_iterations; ///< The container with Timers for each iteration performance calculation
      std::queue<int> m_free;          ///< A queue that holds ids of free timers, this acts as pool

      Result m_result;                 ///< Result instance that gets updated on each iteration, and at stop()
   };

}; //namespace distcal