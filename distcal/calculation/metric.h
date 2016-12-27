#pragma once

#include <cmath>
#include <functional>

#include "../dataset.h"

namespace distcal
{
   typedef std::function<double( const DataVector&, const DataVector& )> DistanceMetric;

   /// @brief Class that holds all the metrics
   class Metric
   {
   public:
      enum MetricType       ///< Enumerated types of metrics
      {
         HAMMING_TYPE = 0,
         L1_TYPE,
         L2_TYPE
      };

      static double Hamming(const DataVector& lhs, const DataVector& rhs)
      {
         const double eps = 1e-10;
         double res = 0;
         for( unsigned int i = 0; i < lhs.size(); ++i )
         {
            res += (int)(lhs[i] + rhs[i] + eps) % 2;
         }
         return res;
      }

      static double L1(const DataVector& lhs, const DataVector& rhs)
      {
         double res = 0;
         for( unsigned int i = 0; i < lhs.size(); ++i )
         {
            res += std::abs(lhs[i] - rhs[i]);
         }
         return res;
      }

      static double L2(const DataVector& lhs, const DataVector& rhs)
      {
         double res = 0;
         for( unsigned int i = 0; i < lhs.size(); ++i )
         {
            double delta = lhs[i] - rhs[i];
            res += delta * delta;
         }
         return std::sqrt(res);
      }
   }; 

}; //namespace distcal