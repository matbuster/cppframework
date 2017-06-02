#ifndef ENUM_SERIALIZER_DETECTION_H
#define ENUM_SERIALIZER_DETECTION_H

namespace Serialization {
	
	/**! enumeration associated to the serializer detection
 	*/
	enum EnumSerializerDetection {
		
		initialized,
		detectTag,
		detectSize,
		detectBuffer,
		end,
		lost
	};
};

#endif /** ENUM_SERIALIZER_DETECTION_H */