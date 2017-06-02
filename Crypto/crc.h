#ifndef CRYPTO_CRC_H
#define CRYPTO_CRC_H

// ----------------------------------------------------------
// defines
#define	P_16				0xA001
#define P_DNP				0xA6BC

#define	MAX_CRC16_SIZE		256

// ----------------------------------------------------------
// includes
#include <string>

namespace Crypto {
	
	/** enumeration associated to the type of algo */
	typedef enum {
		crc16,
		dnp
	} CRC16_ALGO;

	class CRC16 {

	private:
		/** internal initialization value */
		bool m_b_crc_tab16_init;
		
		bool m_b_crc_tabdnp_init;

		/** intenral crc tab value */
		unsigned short m_crc_tab16[MAX_CRC16_SIZE];
		unsigned short m_crc_tabdnp[MAX_CRC16_SIZE];
		
		/** internal input value definition */
		std::string m_str_input_value;

		/** init algo */
		void init_crc16_tab( void );
		void init_crcdnp_tab( void );
		
		// ------------------------------------------------------------
		/** 
		 * The function update_crc_16 calculates a  new  CRC-16  value
		 * based  on  the  previous value of the CRC and the next byte
		 * of the data to be checked.
		 */
		unsigned short update_crc_16( unsigned short crc, char c );

		// ------------------------------------------------------------
		/**
		 * The function update_crc_dnp calculates a new CRC-DNP  value
		 * based  on  the  previous value of the CRC and the next byte
		 * of the data to be checked. 
		 */
		unsigned short update_crc_dnp( unsigned short crc, char c );

		/** getter on the crc16 value */
		unsigned short get(unsigned short usStartValue, CRC16_ALGO algo);
	
	public:
		CRC16(const std::string value);
		~CRC16();

		/** getter on the crc16 value */
		unsigned short getCrc16Value();

		/** getter on the crc16 modbus value */
		unsigned short getCrc16ModbusValue();

		/** getter on the crc16 dnp value */
		unsigned short getCrc16DnpValue();
	};

	/** get the CRC16 value of the input string*/
	unsigned short getCRC16(const std::string value);

	/** get the CRC16 Modbus value of the input string */
	unsigned short getCRC16Modbus(const std::string value);

	/** get the CRC16 Dnp value of the input string */
	unsigned short getCRC16Dnp(const std::string value);
};

#endif // CRYPTO_CRC_H