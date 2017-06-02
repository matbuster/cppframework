
#include "crc.h"

#include <string.h>

// -------------------------------------------------------------
Crypto::CRC16::CRC16(const std::string value)
{
	m_b_crc_tab16_init = false;
	m_b_crc_tabdnp_init = false;
	memset(m_crc_tab16, 0x00, MAX_CRC16_SIZE);
	memset(m_crc_tabdnp, 0x00, MAX_CRC16_SIZE);

	m_str_input_value = value;
}
// -------------------------------------------------------------
Crypto::CRC16::~CRC16()
{
}
// -------------------------------------------------------------
void Crypto::CRC16::init_crc16_tab( void ) {

    int i, j;
    unsigned short crc, c;

    for (i=0; i<MAX_CRC16_SIZE; i++) {

        crc = 0;
        c   = (unsigned short) i;

        for (j=0; j<8; j++) {

            if ( (crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ P_16;
            else                      crc =   crc >> 1;

            c = c >> 1;
        }

        m_crc_tab16[i] = crc;
    }

    m_b_crc_tab16_init = true;

}  
// -------------------------------------------------------------
/* init_crc16_tab */
void Crypto::CRC16::init_crcdnp_tab( void ) {

    int i, j;
    unsigned short crc, c;

    for (i=0; i<256; i++) {

        crc = 0;
        c   = (unsigned short) i;

        for (j=0; j<8; j++) {

            if ( (crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ P_DNP;
            else                      crc =   crc >> 1;

            c = c >> 1;
        }

        m_crc_tabdnp[i] = crc;
    }

    m_b_crc_tabdnp_init = true;

}  /* init_crcdnp_tab */
// -------------------------------------------------------------
unsigned short Crypto::CRC16::update_crc_16( unsigned short crc, char c ) {

    unsigned short tmp, short_c;

    short_c = 0x00ff & (unsigned short) c;

    if ( ! m_b_crc_tab16_init ) init_crc16_tab();

    tmp =  crc       ^ short_c;
    crc = (crc >> 8) ^ m_crc_tab16[ tmp & 0xff ];

    return crc;

}  /* update_crc_16 */
// -------------------------------------------------------------
unsigned short Crypto::CRC16::update_crc_dnp( unsigned short crc, char c ) {

    unsigned short tmp, short_c;

    short_c = 0x00ff & (unsigned short) c;

    if ( ! m_b_crc_tabdnp_init ) init_crcdnp_tab();

    tmp =  crc       ^ short_c;
    crc = (crc >> 8) ^ m_crc_tabdnp[ tmp & 0xff ];

    return crc;

}  /* update_crc_dnp */
// -------------------------------------------------------------
unsigned short Crypto::CRC16::get(unsigned short usStartValue, Crypto::CRC16_ALGO algo)
{
	const char *ptr = m_str_input_value.c_str();
	unsigned short crc_16 = usStartValue;

	while ( *ptr ) {

		if(crc16 == algo) {
			crc_16 = update_crc_16(crc_16, *ptr );
		} else if(dnp == algo) {
			crc_16 = update_crc_dnp(crc_16, *ptr);
		}
		ptr++;
	}

	return crc_16;

}
// -------------------------------------------------------------
unsigned short Crypto::CRC16::getCrc16Value()
{
	return get(0, crc16);
}
// -------------------------------------------------------------
unsigned short Crypto::CRC16::getCrc16ModbusValue()
{
	return get(0xffff, crc16);
}
// -------------------------------------------------------------
unsigned short Crypto::CRC16::getCrc16DnpValue()
{
	return get(0, dnp);
}
// -------------------------------------------------------------
unsigned short Crypto::getCRC16(const std::string value)
{
	Crypto::CRC16 * calcCrc16 = new Crypto::CRC16(value);
	unsigned short usResult = calcCrc16->getCrc16Value();
	delete calcCrc16;

	return usResult;
}
// -------------------------------------------------------------
unsigned short Crypto::getCRC16Modbus(const std::string value)
{
	Crypto::CRC16 * calcCrc16 = new Crypto::CRC16(value);
	unsigned short usResult = calcCrc16->getCrc16ModbusValue();
	delete calcCrc16;

	return usResult;
}
// -------------------------------------------------------------
unsigned short Crypto::getCRC16Dnp(const std::string value)
{
	Crypto::CRC16 * calcCrc16 = new Crypto::CRC16(value);

	unsigned short low_byte, high_byte;
	unsigned short crc_dnp = calcCrc16->getCrc16DnpValue();

    crc_dnp    = ~crc_dnp;
    low_byte   = (crc_dnp & 0xff00) >> 8;
    high_byte  = (crc_dnp & 0x00ff) << 8;
    crc_dnp    = low_byte | high_byte;

	delete calcCrc16;

	return crc_dnp;
}
// -------------------------------------------------------------

