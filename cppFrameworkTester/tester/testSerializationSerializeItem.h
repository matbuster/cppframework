#ifndef TESTER_SERIALIZER_SERILIZE_ITEM_H
#define TESTER_SERIALIZER_SERILIZE_ITEM_H

namespace Test {
	
	// ---------------------------------------------------
	/**! tester serializer for bool
	 * \return error code
	 */
	int tester_serialization_serialize_bool();

	// ---------------------------------------------------
	/**! tester serializer for short
	 * \return error code
	 */
	int tester_serialization_serialize_short();
	
	// ---------------------------------------------------
	/**! tester serializer for integer
	 * \return error code
	 */
	int tester_serialization_serialize_int();

	// ---------------------------------------------------
	/**! tester serializer for float
	 * \return error code
	 */
	int tester_serialization_serialize_float();

	// ---------------------------------------------------
	/**! tester serializer for double
	 * \return error code
	 */
	int tester_serialization_serialize_double();

	// ---------------------------------------------------
	/**! tester serializer for long
	 * \return error code
	 */
	int tester_serialization_serialize_long();
	
	// ---------------------------------------------------
	/**! tester serializer for string
	 * \return error code
	 */
	int tester_serialization_serialize_string();

	// ---------------------------------------------------
	/**! tester serializer 
	 * \return error code
	 */
	int tester_serialization_serializer();

	// ---------------------------------------------------
	/**! generic test function to test all functionnalities associated
	 * to the SerializeItem
	 * \return errot code
	 */
	int tester_serialization_serialize_item();
	// ---------------------------------------------------
};

#endif // TESTER_SERIALIZER_SERILIZE_ITEM_H

