#ifndef MDFCC_H
#define MDFCC_H

#include<QtCore>

#include "MDFBaseData.h"
#include "MDFData.h"
#include "MDFCCLinear.h"
#include "MDFCCTextTable.h"

namespace MDFlib {
    class MDFCC
    {
    public:
        MDFCC();
        MDFCC(QFile *file, unsigned long pCC, unsigned short dataType, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short byteOrder);

//BlockType
        QString* getBlockType();
        void setBlockType(QString* value);
//BlockSize
        unsigned short getBlockSize();
        void setBlockSize(unsigned short value);
//PhysValueRange
        unsigned short getPhysValueRange();
        void setPhysValueRange(unsigned short value);
//PhysMin
        double getPhysMin();
        void setPhysMin(double value);
//PhysMax
        double getPhysMax();
        void setPhysMax(double value);
//PhysUnit
        QString* getPhysUnit();
        void setPhysUnit(QString* value);
//Conversion
        unsigned short getConversion();
        void setConversion(unsigned short value);
//SizeInfo
        unsigned short getSizeInfo();
        void setSizeInfo(unsigned short value);

//Data
        QList<double>* getData();

    private:
        QFile*          myMDFFile;
        CBaseData*		m_Data;
        void CreateConversions(unsigned long pCCL, unsigned short byteOrder, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short newByteOrder);

        QString*        m_blockType;
        unsigned short  m_blockSize;
        unsigned short	m_physValueRange;
        double			m_physMin;
        double			m_physMax;
        QString*		m_physUnit;
        unsigned short	m_conversion;
        unsigned short	m_sizeInfo;
    };
}

#endif // MDFCC_H
