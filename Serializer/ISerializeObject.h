#ifndef I_SERIALIZE_OBJECT_H
#define I_SERIALIZE_OBJECT_H

namespace Serialization {

	class ISerializeObject
	{
	public:

		virtual ~ISerializeObject() {}

		virtual serialize() = 0;

		virtual deserialize(unsigned char * pBufferSerilized, unsigned long pBufferSerilizedLength) = 0;

	};
};

#endif /** I_SERIALIZE_OBJECT_H */