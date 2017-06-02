/**
 * \file 		CommonStats.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef MATH_STATS_H
#define MATH_STATS_H

#include <list>

#define MAX_DOUBLE	100000000000000.0f
#define MIN_DOUBLE	-100000000000000.0f

namespace Math {

	namespace Statistics {
	
		/** class to calculate min, max, average, stdev on a simple list of values */
		class CommonStats {

		private:
			/** internal lists of values */
			std::list<double> * m_dValues;

			/** minimum value */
			double m_dMin;

			/** maximum value */
			double m_dMax;

			/** last value inserted in value */
			double m_dLastValue;

		public:
			/** constructor and destructor */
			CommonStats();
			~CommonStats();
			
			// -------------------------------------------------------------
			/**! function to merge an existing instance of common stats with 
			 * the current instance of the object
			 * \param [in] stats : instance of existing stats
			 */
			void mergeValues(CommonStats * stats);
			
			// -------------------------------------------------------------
			/**! add a new value to the list of existing values
			 * \param [in] value: new input value
			 */
			void AddValue(double value);
			
			// -------------------------------------------------------------
			/**! getter on the list of existing values
			 * \return list of existing values
			 */
			std::list<double> * getValues();

			// -------------------------------------------------------------
			/**! getter of the average  value calculated from the internal list values
			 * \return the average value
			 */
			double getAverage();

			// -------------------------------------------------------------
			/**! getter on the stdev value calculated from the internal list values 
			 * \return the stdev value
			 */
			double getStdev();

			// -------------------------------------------------------------
			/**! getter on the variance value calculated from the internal list values 
			 * \return the stdev value
			 */
			double getVariance();

			// -------------------------------------------------------------
			/**! getter on the last value of the list
			 * \return last value of the list
			 */
			double getLastValue();

			// -------------------------------------------------------------
			/**! getter on the min value of the list
			 * \return min value of the list
			 */
			double getMin();

			// -------------------------------------------------------------
			/**! getter on the max value of the list
			 * \return max value of the list
			 */
			double getMax();
		};
	};
};

#endif /* MATH_STATS_H */


