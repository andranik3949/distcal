#pragma once

#include <iostream>

namespace distcal
{
   /// @brief Utility for showing a progress of an action
   class ProgressBar
   {
   public:
      ProgressBar(long long target)
         :m_partition(target / 10 ), m_progress(0)
      {
         std::cerr << "progress ";
      }

      ~ProgressBar()
      {
         std::cerr << std::endl;
      }

      void update()
      {
         ++m_progress;
         if( m_progress % (m_partition) == 0 )
         {
            std::cerr << '.';
         }
      }

   private:
      long long m_partition;
      long long m_progress;
   };

}; //namespace distcal