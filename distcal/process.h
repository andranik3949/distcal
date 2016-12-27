#pragma once

#include "config.h"

#include "calculation/engine.h"
#include "dataset.h"

namespace distcal
{
   /// @brief Contains the configuration, data and the program logic 
   class Process
   {
   public:
      /// @brief Initializes config, datasets, engine and logger
      Process( int argc, char* argv[] );

      /// @brief Runs the main program logic
      void run();

   private:
      config::Config m_config;      ///< Configuration

      DataSet m_data;               ///< Initial data dataset
      DataSet m_queries;            ///< Queries dataset
      DataSet m_result;             ///< Resulting m_data and m_result distances matrix

      calculation::Engine m_engine; ///< Contains actual calculation engine and metrics
   };

}; //namespace distcal