#pragma once

#include "generic.h"
#include "quadratic.h"

#include "../dataset.h"
#include "../utilities/performance.h"

namespace distcal
{
   namespace calculation
   {
      /// @brief Factory-like class for dynamicly changing the calculation engine and metrics
      class Engine
      {
      public:
         /// @brief Constructs class, stores references to the data that will have to be processed and sets Engine and Metric
         /// @param eType, The type of engine, default is quadratic
         /// @param mType, The type of metrics, default is L2
         Engine( const DataSet& data, const DataSet& queries, DataSet& result, 
                 GenericEngine::EngineType eType = GenericEngine::EngineType::QUADRATIC_TYPE, 
                 Metric::MetricType        mType = Metric::MetricType::L2_TYPE )
            :m_data( data ), m_queries( queries ), m_result( result ), m_engineImpl(nullptr)
         {             
            setEngine( eType );
            setMetric( mType );
         }

         /// @brief Sets the engine to the given type, deletes the old one
         /// @parm engine, The type of new engine
         void setEngine( GenericEngine::EngineType engine )
         {
            if( m_engineImpl != nullptr )
            {
               delete m_engineImpl;
            }

            switch( engine )
            {
            case GenericEngine::EngineType::QUADRATIC_TYPE:
            default:
               m_engineImpl = new QuadraticEngine( m_data, m_queries, m_result );
            }
         }

         /// @brief Sets the metrics to the given type
         /// @parm metric, The type of new metric
         void setMetric( Metric::MetricType metric )
         {
            switch( metric )
            {
            case Metric::MetricType::HAMMING_TYPE:
               m_metricImpl = Metric::Hamming;
               break;
            case Metric::MetricType::L1_TYPE:
               m_metricImpl = Metric::L1;
               break;
            case Metric::MetricType::L2_TYPE:
            default:
               m_metricImpl = Metric::L2;
            }
         }

         /// @brief Calls calculate() method of the underlying engine, with the underlying metrics
         /// @return The performance of the underlying engine during the calculations
         Performance::Result calculate()
         {
            return m_engineImpl->calculate( m_metricImpl );
         }

      private:
         const DataSet& m_data;     
         const DataSet& m_queries;
         DataSet& m_result;

         GenericEngine* m_engineImpl; ///< Pointer to the current engine
         DistanceMetric m_metricImpl; ///< Metric function
      };


   }; //namespace calculation
}; //namespace distcal