#include "csv.h"

#include <sstream>
#include <regex>

#include "exception.h"

#include "../dataset.h"

namespace distcal
{
   CSV::CSV(const std::string& filename)
      :m_filename(filename), m_file(filename)
   {
      if( !m_file.good() )
      {
         throw CsvException("[" + m_filename + "] can't be opened");
      }
   }

   void CSV::fill(DataSet& data)
   {
      std::string line;
      std::istringstream lineStream;

      for( size_t i = 0; i < data.count(); ++i )
      {
         std::getline(m_file, line);

         lineStream.str(line + ',');
         for( size_t j = 0; j < data.dimension(); ++j )
         {
            char dummy;
            lineStream >> data[i][j] >> dummy;
            if (!lineStream.good() || dummy != ',')
            {
               throw CsvException("[" + m_filename + "] contains invalid data on line <" + std::to_string(i));
            }
         }
      }
      if( !m_file.eof() )
      {
         throw CsvException("[" + m_filename + "] contains more data than expected");
      }
    }

}; //namespace distcal