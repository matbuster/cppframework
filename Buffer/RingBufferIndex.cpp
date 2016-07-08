
#include "RingBufferIndex.h"

// --------------------------------------------------------------
Buffer::RingBufferIndex::RingBufferIndex(long _lSizeBuffer)
{
	m_rbiTrailer = new Buffer::RingBufferPos(_lSizeBuffer);
	m_rbiRead = new Buffer::RingBufferPos(_lSizeBuffer);
	m_rbiWrite = new Buffer::RingBufferPos(_lSizeBuffer);
}
// --------------------------------------------------------------
Buffer::RingBufferIndex::~RingBufferIndex()
{
	delete m_rbiTrailer;
	delete m_rbiRead;
	delete m_rbiWrite;
}
// --------------------------------------------------------------
int Buffer::RingBufferIndex::CalculePosition(int * _allowedLenghtTillEnd, int * _allowedFromBeginning)
{
	//3 configurations valables TRW(1) RWT(2) WTR(3)
	//3 configurations non valables TWR(4) RTW(5) WRT(6)
	if(m_rbiRead->getNPosition()<=m_rbiWrite->getNPosition())//R<=W
	{
		if(m_rbiWrite->getNPosition()<m_rbiTrailer->getNPosition())//W<T
		{
			//R<=W et W<T = RWT(2)
			*_allowedLenghtTillEnd=m_rbiTrailer->getNPosition()-m_rbiWrite->getNPosition();//on peut remplir le buffer jusqu'à la fin
			*_allowedFromBeginning=0;
			return RBI_OK;
		}
		else//T<=W
		{
			//R<=W et T<=W //T<->R inconnu
			//R<T<=W serait une erreur RTW(5)
			if(m_rbiRead->getNPosition()<m_rbiTrailer->getNPosition())
			{
				return RBI_WRONG_INDEX_CFG;//R<T
			}
			//R<=W et T<=W et T<=R = TRW(1)
			*_allowedLenghtTillEnd=m_rbiWrite->getBufferLen()-m_rbiWrite->getNPosition();//on peut remplir le buffer jusqu'à la fin
			*_allowedFromBeginning=m_rbiTrailer->getNPosition();
			return RBI_OK;
		}
	}
	else if(m_rbiWrite->getNPosition()<m_rbiTrailer->getNPosition())
	{
		//W<=R et W<T
		//W<=R<T serait une erreur WRT(6)
		if(m_rbiRead->getNPosition()<m_rbiTrailer->getNPosition())
		{
			return RBI_WRONG_INDEX_CFG;//R<T
		}
		//W<R et W<T et T<=R = WTR(3)
		*_allowedLenghtTillEnd=m_rbiTrailer->getNPosition()-m_rbiWrite->getNPosition();//on peut remplir le buffer jusqu'au début de la partie non traitée
		*_allowedFromBeginning=0;
		return RBI_OK;
	}
	else
	{
		// T<=W<R est un cas d'erreur TWR(4)
		return RBI_WRONG_INDEX_CFG;
	}

	// retour sans erreur
	return RBI_OK;
}
// --------------------------------------------------------------