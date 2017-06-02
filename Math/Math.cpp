
#include "Math.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// ---------------------------------------------------------------------
int Math::Min(int _iVal1, int _iVal2)
{
	return (_iVal1 > _iVal2) ? _iVal2 : _iVal1;
}
// ---------------------------------------------------------------------
float Math::Min(float _fVal1, float _fVal2)
{
	return (_fVal1 > _fVal2) ? _fVal2 : _fVal1;
}
// ---------------------------------------------------------------------
double Math::Min(double _dVal1, double _dVal2)
{
	return (_dVal1 > _dVal2) ? _dVal2 : _dVal1;
}
// ---------------------------------------------------------------------
int Math::Max(int _iVal1, int _iVal2)
{
	return (_iVal1 < _iVal2) ? _iVal2 : _iVal1;
}
// ---------------------------------------------------------------------
float Math::Max(float _fVal1, float _fVal2)
{
	return (_fVal1 < _fVal2) ? _fVal2 : _fVal1;
}
// ---------------------------------------------------------------------
double Max(double _dVal1, double _dVal2)
{
	return (_dVal1 < _dVal2) ? _dVal2 : _dVal1;
}
// ---------------------------------------------------------------------
float Math::Round(float val, int precision)
{
	std::stringstream s;
    s << std::setprecision(precision) << std::setiosflags(std::ios_base::fixed) << val;
    s >> val;
    return val;
}
// ---------------------------------------------------------------------
double Math::Round(double val, int precision)
{
    std::stringstream s;
    s << std::setprecision(precision) << std::setiosflags(std::ios_base::fixed) << val;
    s >> val;
    return val;
}
// ---------------------------------------------------------------------
