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

		public:
			CommonStats();
			~CommonStats();
			void mergeValues(CommonStats * stats);
			void AddValue(double value);
			std::list<double> * getValues();
			double getAverage();
			double getStdev();
			double getMin();
			double getMax();
		};
	};
};

#endif /* MATH_STATS_H */


