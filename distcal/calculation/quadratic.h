#pragma once

#include "generic.h"

#include "../utilities/progressbar.h"

namespace distcal
{
   namespace calculation
   {
      /// @brief Quadratic engine, has a complexity of O(data * queries * dim)
      class QuadraticEngine : public GenericEngine
      {
      public:
         QuadraticEngine( const DataSet& data, const DataSet& queries, DataSet& result )
            :GenericEngine( data, queries, result ) 
         { };

      private:
         virtual void engineImpl( DistanceMetric distance )
         {
            ProgressBar pb(m_data.count());
            for( unsigned int i = 0; i < m_data.count(); ++i )
            {
               pb.update();
               for( unsigned int j = 0; j < m_queries.count(); ++j )
               {
                  const int id = m_performance.registerIteration();
                  m_result[i][j] = distance(m_data[i], m_queries[j]);
                  m_performance.endIteration( id );
               }
            }
         }		 
      };

   }; //namespace calculation
}; //namespace distcal