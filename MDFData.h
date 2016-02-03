#ifndef MDFDATA_H
#define MDFDATA_H

#include <QtCore>

#include "MDFBaseData.h"

namespace MDFlib {
    template <class T>
    class CData : public CBaseData
    {
    public:
        CData();
        virtual ~CData();
        virtual double valueAt(int index);
        virtual QList<double>* getDataList();
        virtual void readDataFromFile(QFile *file, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short byteOrder);

    private:
        QList<double>* data;
        unsigned long numElements;
        QFile* myMDFFile;
        unsigned long m_pData;
        unsigned long m_numOfRec;        //m_elements
        unsigned long m_sizeOfDataRec;   //m_blockSize
        unsigned short m_firstBitPos;    //m_firstBit
        double sampleRate;
    };
}


template <class T>
MDFlib::CData<T>::CData()
{
    data = new QList<double>();
}

template <class T>
MDFlib::CData<T>::~CData()
{
}

template <class T>
double MDFlib::CData<T>::valueAt(int index)
{
    double myvalue = 0.0;
    if (index >= m_numOfRec || index <= 0){
        return myvalue;
    }
    else
    {
        return data->at(index);
    }
}


template <class T>
QList<double>* MDFlib::CData<T>::getDataList()
{
    return data;
}

template <class T>
void MDFlib::CData<T>::readDataFromFile(QFile *file, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short byteOrder)
{
    T value;
    qint64 pos;
    qint64 buffer;
    qint64 mask;
    myMDFFile = file;
    QDataStream instream(myMDFFile);
    m_numOfRec = numOfRec;
    m_firstBitPos = firstBitPos;
    m_pData = pDataRecord;
    m_sizeOfDataRec = sizeOfDataRec;

    if(byteOrder == 0)
    {
        instream.setByteOrder(QDataStream::LittleEndian);
    }
    else
    {
        instream.setByteOrder(QDataStream::BigEndian);
    }

    for(int i = 0; i < numOfRec; i++)
    {
        pos = pDataRecord + (i * sizeOfDataRec) + (firstBitPos / 8);
        int numOfReadableBytes = (numOfBits + (firstBitPos % 8) + (8 - (numOfBits % 8) - (firstBitPos % 8))) / 8;

        myMDFFile->seek(pos);
        instream >> buffer;

        int shift;
        if(byteOrder == 0)
        {
            shift = (firstBitPos % 8);
        }
        else
        {
            shift = (firstBitPos % 8) + ((9 - numOfReadableBytes) * 8);
        }

        buffer = buffer >> shift;
        mask = (int)qPow((double)2,(double)numOfBits) - 1;

        qint64 tempValue = buffer & mask;
        value = (T)tempValue;

        if (myConv)
        {
            data->append(myConv->Convert(double(value)));
        }
        else
        {
            data->append(double(value));
        }
    }
}

#endif // MDFDATA_H
