/**
 * \file 		Random.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef MATH_RANDOM_H
#define MATH_RANDOM_H

#include "Timing/Chrono.h"

namespace Math {

	/** internal class random based on PC clock
	 */
	class Random {
	
	private:
		/** internal base chrono definition */
		Timing::Chrono * m_chrono;

	public:
		Random();
		~Random();

		/** get the next integer value between 0 and iMaxValue */
		int getNextInt(int iMaxValue);
	};
};

#endif /* MATH_RANDOM_H */