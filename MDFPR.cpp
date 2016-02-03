#include "MDFPR.h"

MDFlib::MDFPR::MDFPR(QFile *file, long pTX, unsigned short byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString blockType;
    unsigned short blockSize;
    QString data;

    if(byteOrder == 0)
    {
        instream.setByteOrder(QDataStream::LittleEndian);
    }
    else
    {
        instream.setByteOrder(QDataStream::BigEndian);
    }
    myMDFFile->seek(pTX);

    byteArray = myMDFFile->read(2);
    blockType.append(byteArray.data());

    myMDFFile->seek(pTX + 2);
    instream >> blockSize;

    myMDFFile->seek(pTX + 4);
    byteArray = myMDFFile->read(blockSize);
    data.append(byteArray.data());

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setData(&data);
}

QString *MDFlib::MDFPR::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFPR::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFPR::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFPR::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

QString *MDFlib::MDFPR::getData()
{
    return m_data;
}

void MDFlib::MDFPR::setData(QString *value)
{
    m_data = new QString(*value);
}

