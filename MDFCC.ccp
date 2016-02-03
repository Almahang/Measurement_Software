#include "MDFCC.h"

MDFlib::MDFCC::MDFCC()
{
}

MDFlib::MDFCC::MDFCC(QFile* file, unsigned long pCC, unsigned short dataType, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);
    unsigned short newByteOrder;
    
    QString blockType;
    unsigned short blockSize;
    unsigned short physValueRange;
    double physMin;
    double physMax;
    QString physUnit;
    unsigned short conversion;
    unsigned short sizeInfo;
    
    myMDFFile->seek(pCC);
    if(byteOrder == 0)
    {
        instream.setByteOrder(QDataStream::LittleEndian);
    }
    else
    {
        instream.setByteOrder(QDataStream::BigEndian);
    }
    
    byteArray = myMDFFile->read(2);
    blockType.append(byteArray.data());
    
    myMDFFile->seek(pCC + 2);
    instream >> blockSize;
    myMDFFile->seek(pCC + 4);
    instream >> physValueRange;
    myMDFFile->seek(pCC + 6);
    instream >> physMin;
    myMDFFile->seek(pCC + 14);
    instream >> physMax;
    
    myMDFFile->seek(pCC + 22);
    byteArray = myMDFFile->read(20);
    physUnit.append(byteArray.data());
    
    myMDFFile->seek(pCC + 42);
    instream >> conversion;
    myMDFFile->seek(pCC + 44);
    instream >> sizeInfo;

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setPhysValueRange(physValueRange);
    setPhysMin(physMin);
    setPhysMax(physMax);
    setPhysUnit(&physUnit);
    setConversion(conversion);
    setSizeInfo(sizeInfo);
    
    m_Data =NULL;
    
    switch(dataType)
    {
    case 0:
        if(numOfBits <= 8 && numOfBits >= 1) m_Data = new CData<unsigned char>;
        else if(numOfBits <= 16 && numOfBits >= 9) m_Data = new CData<unsigned short>;
        else if(numOfBits <= 32 && numOfBits >= 17) m_Data = new CData<unsigned int>;
        else if(numOfBits <= 64 && numOfBits >= 33) m_Data = new CData<unsigned long int>;
        newByteOrder = byteOrder;
        break;
    case 1:
        if(numOfBits <= 8 && numOfBits >= 1) m_Data = new CData<char>;
        else if(numOfBits <= 16 && numOfBits >= 9) m_Data = new CData<short>;
        else if(numOfBits <= 32 && numOfBits >= 17) m_Data = new CData<int>;
        else if(numOfBits <= 64 && numOfBits >= 33) m_Data = new CData<long int>;
        newByteOrder = byteOrder;
        break;
    case 2:
        m_Data = new CData<float>;
        break;
    case 3:
        m_Data = new CData<double>;
        break;
    case 7:
        m_Data = new CData<char>;
        break;
    case 8:
        m_Data = new CData<char>;
        break;
    case 9:
        if(numOfBits <= 8 && numOfBits >= 1) m_Data = new CData<unsigned char>;
        else if(numOfBits <= 16 && numOfBits >= 9) m_Data = new CData<unsigned short>;
        else if(numOfBits <= 32 && numOfBits >= 17) m_Data = new CData<unsigned int>;
        else if(numOfBits <= 64 && numOfBits >= 33) m_Data = new CData<unsigned long int>;
        newByteOrder = 1;
        break;
    case 10:
        if(numOfBits <= 8 && numOfBits >= 1) m_Data = new CData<char>;
        else if(numOfBits <= 16 && numOfBits >=9 ) m_Data = new CData<short>;
        else if(numOfBits <= 32 && numOfBits >=17 ) m_Data = new CData<int>;
        else if(numOfBits <= 64 && numOfBits >=33 ) m_Data = new CData<long int>;
        newByteOrder = 1;
        break;
    case 13:
        if(numOfBits <= 8 && numOfBits >= 1) m_Data = new CData<unsigned char>;
        else if(numOfBits <= 16 && numOfBits >= 9) m_Data = new CData<unsigned short>;
        else if(numOfBits <= 32 && numOfBits >= 17) m_Data = new CData<unsigned int>;
        else if(numOfBits <= 64 && numOfBits >= 33) m_Data = new CData<unsigned long int>;
        newByteOrder = 0;
        break;
    case 14:
        if(numOfBits <= 8 && numOfBits >= 1) m_Data = new CData<char>;
        else if(numOfBits <= 16 && numOfBits >=9 ) m_Data = new CData<short>;
        else if(numOfBits <= 32 && numOfBits >=17 ) m_Data = new CData<int>;
        else if(numOfBits <= 64 && numOfBits >=33 ) m_Data = new CData<long int>;
        newByteOrder = 0;
        break;
    default:
        break;
    }
    
    CreateConversions(pCC + 46, byteOrder, pDataRecord, numOfRec, sizeOfDataRec, firstBitPos, numOfBits, newByteOrder);
}


void MDFlib::MDFCC::CreateConversions(unsigned long pCCL, unsigned short byteOrder, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short firstBitPos, unsigned short numOfBits, unsigned short newByteOrder)
{
    switch(m_conversion)
    {
        case 0:
        {
            m_Data->myConv = new MDFCCLinear(myMDFFile, pCCL, byteOrder);
            m_Data->readDataFromFile(myMDFFile, pDataRecord, numOfRec, sizeOfDataRec, firstBitPos, numOfBits, newByteOrder);
            break;
        }
        case 11:
        {
            m_Data->myConv = new MDFCCTextTable(myMDFFile, pCCL, m_sizeInfo, byteOrder);
            break;
        }
        default:
        {
        }
    }
}

QString *MDFlib::MDFCC::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFCC::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFCC::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFCC::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

unsigned short MDFlib::MDFCC::getPhysValueRange()
{
    return m_physValueRange;
}

void MDFlib::MDFCC::setPhysValueRange(unsigned short value)
{
    m_physValueRange = value;
}

double MDFlib::MDFCC::getPhysMin()
{
    return m_physMin;
}

void MDFlib::MDFCC::setPhysMin(double value)
{
    m_physMin = value;
}

double MDFlib::MDFCC::getPhysMax()
{
    return m_physMax;
}

void MDFlib::MDFCC::setPhysMax(double value)
{
    m_physMax = value;
}

QString *MDFlib::MDFCC::getPhysUnit()
{
    return m_physUnit;
}

void MDFlib::MDFCC::setPhysUnit(QString *value)
{
    m_physUnit = new QString(*value);
}

unsigned short MDFlib::MDFCC::getConversion()
{
    return m_conversion;
}

void MDFlib::MDFCC::setConversion(unsigned short value)
{
    m_conversion = value;
}

unsigned short MDFlib::MDFCC::getSizeInfo()
{
    return m_sizeInfo;
}

void MDFlib::MDFCC::setSizeInfo(unsigned short value)
{
    m_sizeInfo = value;
}

QList<double> *MDFlib::MDFCC::getData()
{
    return m_Data->getDataList();
}
