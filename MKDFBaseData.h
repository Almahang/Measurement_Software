#ifndef MDFBASEDATA_H
#define MDFBASEDATA_H

#include <QtCore>

#include "MDFConversion.h"

namespace MDFlib {
    class CBaseData
	{
	public:
		CBaseData();
		virtual ~CBaseData();
        virtual double valueAt(int index) = 0;
        virtual QList<double>* getDataList() = 0;
        virtual void readDataFromFile(QFile *file, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short byteOrder) = 0;

        MDFConversion* myConv;
		int Test;
		
	};
}

#endif // MDFBASEDATA_H
