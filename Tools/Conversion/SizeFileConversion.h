#ifndef SIZE_FILE_CONVERSION_H
#define SIZE_FILE_CONVERSION_H

#include <stdint.h>

#define CONVERTION_CONSTANT		1024.0

namespace Tools {
	
	namespace Conversion {
		
			/**! function to convert a size in byte to kilobyte 
			 * @param _ui64SizeInOctets size in octets / bytes 
			 * @return converted value in kilo bytes
			 */
			double convertOctetsToKiloOctets(uint64_t _ui64SizeInOctets);

			/**! function to convert a size in byte to megabyte 
			 * @param _ui64SizeInOctets size in octets / bytes 
			 * @return converted value in mego bytes
			 */
			double convertOctetsToMegaOctets(uint64_t _ui64SizeInOctets);
	};
};

#endif // SIZE_FILE_CONVERSION_H