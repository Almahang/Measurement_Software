#include "MDFTX.h"

MDFlib::MDFTX::MDFTX(QFile* file, long pTX, unsigned short byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString blockType;
    unsigned short blockSize;
    QString text;

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
    text.append(byteArray.data());

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setText(&text);
}

MDFlib::MDFTX::~MDFTX()
{
}

QString *MDFlib::MDFTX::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFTX::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFTX::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFTX::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

QString *MDFlib::MDFTX::getText()
{
    return m_text;
}

void MDFlib::MDFTX::setText(QString *value)
{
    m_text = new QString(*value);
}
