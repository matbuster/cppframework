
#include "SizeFileConversion.h"

// ----------------------------------------------------
double Tools::Conversion::convertOctetsToKiloOctets(uint64_t _ui64SizeInOctets) {

	double _dConvertedSize = (double)(_ui64SizeInOctets / CONVERTION_CONSTANT);
	return _dConvertedSize;
}
// ----------------------------------------------------
double Tools::Conversion::convertOctetsToMegaOctets(uint64_t _ui64SizeInOctets) {
	
	double _dConvertedSize = (double)(_ui64SizeInOctets / (CONVERTION_CONSTANT * CONVERTION_CONSTANT));
	return _dConvertedSize;
}
// ----------------------------------------------------