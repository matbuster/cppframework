#ifndef MATH_H
#define MATH_H

namespace Math {

	// -------------------------------------------------------
	/**! getter on the min value between val1 and val2
	 * \param [in] _iVal1: first input value
	 * \param [in] _iVal2: second input value
	 * \return min between _iVal1 & _iVal2
	 */
	int Min(int _iVal1, int _iVal2);

	// -------------------------------------------------------
	/**! getter on the min value between val1 and val2
	 * \param [in] _fVal1: first input value
	 * \param [in] _fVal2: second input value
	 * \return min between _fVal1 & _fVal2
	 */
	float Min(float _fVal1, float _fVal2);

	// -------------------------------------------------------
	/**! getter on the min value between val1 and val2
	 * \param [in] _dVal1: first input value
	 * \param [in] _dVal2: second input value
	 * \return min between _dVal1 & _dVal2
	 */
	double Min(double _dVal1, double _dVal2);

	// -------------------------------------------------------
	/**! getter on the max value between val1 and val2
	 * \param [in] _iVal1: first input value
	 * \param [in] _iVal2: second input value
	 * \return max between _iVal1 & _iVal2
	 */
	int Max(int _iVal1, int _iVal2);

	// -------------------------------------------------------
	/**! getter on the max value between val1 and val2
	 * \param [in] _fVal1: first input value
	 * \param [in] _fVal2: second input value
	 * \return max between _fVal1 & _fVal2
	 */
	float Max(float _fVal1, float _fVal2);

	// -------------------------------------------------------
	/**! getter on the max value between val1 and val2
	 * \param [in] _dVal1: first input value
	 * \param [in] _dVal2: second input value
	 * \return max between _dVal1 & _dVal2
	 */
	double Max(double _dVal1, double _dVal2);
	
	// -------------------------------------------------------
	/**! round function
	 * \param [in] _fValue: float value to be rounded
	 * \param [in] _iPrecision : precision, number of digits
	 * \return rounded float value
	 */
	float Round(float _fValue, int _iPrecision);

	// -------------------------------------------------------	
	/**! round function
	 * \param [in] _dValue: double value to be rounded
	 * \param [in] _iPrecision : precision, number of digits
	 * \return rounded float value
	 */
	double Round(double _dValue, int _iPrecision);
};

#endif // MATH_H<