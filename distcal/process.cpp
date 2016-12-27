#include "version.h"
#include "process.h"
#include "utilities/log.h"
#include "utilities/performance.h"

#include <iostream>
#include <fstream>

namespace distcal
{
   Process::Process( int argc, char* argv[] )
      :m_config( argc, argv ), 

       m_data    (m_config.data_count,  m_config.dimension),
       m_queries (m_config.query_count, m_config.dimension),
       m_result  (m_config.data_count,  m_config.query_count),

       m_engine  (m_data, m_queries, m_result)
   {
      Log::instance().init(m_config);

      Log::info() << "distcal v" << Version;
      Log::info() << m_config;
   };

   void Process::run()
   {
      std::cerr << "fetching data" << std::endl;
      if( m_config.data_file.empty() || !m_data.fetch(m_config.data_file) )
      {
         Log::info() << "generating random data dataset";
         m_data.randomize(m_config.min, m_config.max);

         Log::debug() << m_data;
      }

      std::cerr << "fetching queries" << std::endl;
      if( m_config.query_file.empty() || !m_queries.fetch(m_config.query_file) )
      {
         Log::info() << "generating random queries dataset";
         m_queries.randomize(m_config.min, m_config.max);

         Log::debug() << m_queries;
      }

      std::cerr << "data fetched, calculating" << std::endl;
      Performance::Result perf = m_engine.calculate();

      std::cerr << "done: [" << perf.m_count << "] iterations in [" << perf.m_total / 1000 << "ms], averaged at [" << perf.m_average << "mcs]" << std::endl;
      std::cout << m_result;
   }

}; //namespace distcal