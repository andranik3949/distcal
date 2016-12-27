#pragma once

#include <string>
#include <vector>

namespace distcal
{
   typedef std::vector<double> DataVector;

   /// @brief Holds sets of vectors
   ///
   /// The DataSets can be fetched from a file, otherwise they will be randomly generated
   class DataSet
   {
   public:
      /// @brief Constructs DataSet
      /// @param count, the number of vectors in the set
      /// @param dimension, the number of coordinates of each vector
      DataSet( size_t count, size_t dimension )
         :m_count( count ), m_dimension( dimension ), m_dataset( count, DataVector( dimension ) )
      { }

      /// @brief Fetches the data from a given file, calls randomize() if filename is empty
      /// @param filename, the file containing data
      bool fetch( const std::string& filename = "" );

      /// @brief Fills DataSet with random real values in the [minimum, maximum) range.
      void randomize(double minimum, double maximum);

      size_t count() const { return m_count; }
      size_t dimension() const { return m_dimension; }

      void dump(const std::string& filename) const;

      DataVector& operator[]( size_t index ) { return m_dataset[index]; }
      const DataVector& operator[]( size_t index ) const { return m_dataset[index]; }
 
   private:
      std::vector<DataVector> m_dataset; ///< Vector containg the data itself 
      size_t m_count;                    ///< Number of vectors
      size_t m_dimension;                ///< Number of coordinates of each vector
   };      

   std::ostream& operator <<( std::ostream& out, const DataSet& rhs );

}; //namespace distcal