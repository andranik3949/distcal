#pragma once

#include "metric.h"

#include "../utilities/performance.h"

namespace distcal
{
   namespace calculation
   {
      /// @brief Abstract class that defines the engine interface 
      class GenericEngine
      {
      public:
         enum EngineType       ///< Enumerated types of engines
         {
            QUADRATIC_TYPE = 0
         };

      public:
         /// @brief Constructs engine and sets the references to the data it will be working with
         GenericEngine( const DataSet& data, const DataSet& queries, DataSet& result )
            :m_data( data ), m_queries( queries ), m_result( result ) 
         { };

         /// @brief Starts the global timer for performance calculation and initiates the actual engine logic
         /// @param distance, The metric function that will be used during calculations
         /// @return The performance of the engine during the calculation
         Performance::Result calculate( DistanceMetric distance ) 
         { 
            m_performance.start();

            engineImpl( distance );

            m_performance.stop();
            return m_performance.getResult();
         }

      private:
         /// @brief The actual engine logic
         /// @param distance, The metric function that will be used during calculations
         virtual void engineImpl( DistanceMetric distance ) = 0;

      protected:
         Performance m_performance;    ///< Current performance of the engine

         const DataSet& m_data;
         const DataSet& m_queries;
         DataSet& m_result;
      };

   }; //namespace calculation
}; //namespace distcal