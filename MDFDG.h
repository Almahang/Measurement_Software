#ifndef MDFDG_H
#define MDFDG_H

#include <QtCore>

#include "MDFCG.h"

namespace MDFlib {
    class MDFDG
	{
	public:
		MDFDG(void);
        MDFDG(QFile* file, unsigned long pDG, unsigned short byteOrder);
        virtual ~MDFDG(void);

//ChannelGroups
        QList<MDFCG*>* getChannelGroups();
        void setChannelGroups( QList< MDFCG* >* value);

//BlockType
        QString* getBlockType();
        void setBlockType(QString* value);
//BlockSize
        unsigned short getBlockSize();
        void setBlockSize(unsigned short value);
//NextDGBlockPTR
        unsigned long getNextDGBlockPTR();
        void setNextDGBlockPTR(unsigned long value);
//CGBlockPTR
        unsigned long getCGBlockPTR();
        void setCGBlockPTR(unsigned long value);
//Reserved1
        unsigned long getReserved1();
        void setReserved1(unsigned long value);
//DataPTR
        unsigned long getDataPTR();
        void setDataPTR(unsigned long value);
//NumOfCG
        unsigned short getNumOfCG();
        void setNumOfCG(unsigned short value);
//NumOfRecIDs
        unsigned short getNumOfRecIDs();
        void setNumOfRecIDs(unsigned short value);
//Reserved2;
        quint32 getReserved2();
        void setReserved2(quint32 value);

    private:
        int				GetChanGroupBlocks(unsigned short byteOrder);
        QFile*			myMDFFile;
        QList<MDFCG*>*  m_mdfCG;

        QString*        m_blockType;
        unsigned short  m_blockSize;
        unsigned long   m_pNextDGBlock;
        unsigned long   m_pCGBlock;
        unsigned long   m_reserved1;
        unsigned long   m_pDataRecord;
        unsigned short	m_numOfCG;
        unsigned short	m_numOfRecIDs;
        qint32          m_reserved2;
	};
}

#endif // MDFDG_H
