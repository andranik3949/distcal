#pragma once

#include <fstream>
#include <string>

#include "../dataset.h"

namespace distcal
{
   /// @brief Helper class for reading and validating CSV files.
   class CSV
   {
   public:
      /// @brief Constructs ifstream and opens it
      /// @param filename, target csv file
      /// @throw CsvException if file failed to opened or doesn't exist
      CSV(const std::string& filename);

      /// @brief Fills referenced DataSet with the data from file
      /// @param data, reference to DataSet which will be filled with the data
      /// @throw CsvException, if file doesn't contain exactly the expected amount of data
      ///
      /// Harsh validation here, extra leading and tailing newlines are considered a format violation.
      void fill(DataSet& data);
      
   private:
      const std::string m_filename;
      std::ifstream     m_file;
   };

}; //namespace distcal