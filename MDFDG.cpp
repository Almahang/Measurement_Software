#include "MDFDG.h"

MDFlib::MDFDG::MDFDG(void)
{
}

MDFlib::MDFDG::MDFDG(QFile* file, unsigned long pDG, unsigned short byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString blockType;
    unsigned short blockSize;
    quint32 pDGBlock;                    //qint32 helyett long is lehetne
    quint32 pCGBlock;
    quint32 reserved1;
    quint32 pDataRecord;
    unsigned short numOfCG;
    unsigned short numOfRecIDs;
    quint32 reserved2;

    myMDFFile->seek(pDG);
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

    myMDFFile->seek(pDG + 2);
    instream >> blockSize;
    myMDFFile->seek(pDG + 4);
    instream >> pDGBlock;
    myMDFFile->seek(pDG + 8);
    instream >> pCGBlock;
    myMDFFile->seek(pDG + 12);
    instream >> reserved1;
    myMDFFile->seek(pDG + 16);
    instream >> pDataRecord;
    myMDFFile->seek(pDG + 20);
    instream >> numOfCG;
    myMDFFile->seek(pDG + 22);
    instream >> numOfRecIDs;
    myMDFFile->seek(pDG + 24);
    instream >> reserved2;

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setNextDGBlockPTR(pDGBlock);
    setCGBlockPTR(pCGBlock);
    setReserved1(reserved1);
    setDataPTR(pDataRecord);
    setNumOfCG(numOfCG);
    setNumOfRecIDs(numOfRecIDs);
    setReserved2(reserved2);

    GetChanGroupBlocks(byteOrder);
}

MDFlib::MDFDG::~MDFDG(void)
{
}

int MDFlib::MDFDG::GetChanGroupBlocks(unsigned short byteOrder)
{
    unsigned long ptrNextCG = m_pCGBlock;
    m_mdfCG =new QList< MDFCG* >;
    while(ptrNextCG !=0)
    {
        MDFCG* newMDFCG = new MDFCG(myMDFFile,ptrNextCG, m_pDataRecord, byteOrder);
        m_mdfCG->append(newMDFCG);
        ptrNextCG = newMDFCG->getNextCGBlockPTR();
    }
	return 0;
}

QList< MDFlib::MDFCG* >* MDFlib::MDFDG::getChannelGroups()
{
    return m_mdfCG;
}

void MDFlib::MDFDG::setChannelGroups(QList< MDFlib::MDFCG* >* value)
{
    m_mdfCG = value;
}



QString *MDFlib::MDFDG::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFDG::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFDG::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFDG::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

unsigned long MDFlib::MDFDG::getNextDGBlockPTR()
{
    return m_pNextDGBlock;
}

void MDFlib::MDFDG::setNextDGBlockPTR(unsigned long value)
{
    m_pNextDGBlock = value;
}

unsigned long MDFlib::MDFDG::getCGBlockPTR()
{
    return m_pCGBlock;
}

void MDFlib::MDFDG::setCGBlockPTR(unsigned long value)
{
    m_pCGBlock = value;
}

unsigned long MDFlib::MDFDG::getReserved1()
{
    return m_reserved1;
}

void MDFlib::MDFDG::setReserved1(unsigned long value)
{
    m_reserved1 = value;
}

unsigned long MDFlib::MDFDG::getDataPTR()
{
    return m_pDataRecord;
}

void MDFlib::MDFDG::setDataPTR(unsigned long value)
{
    m_pDataRecord = value;
}

unsigned short MDFlib::MDFDG::getNumOfCG()
{
    return m_numOfCG;
}

void MDFlib::MDFDG::setNumOfCG(unsigned short value)
{
    m_numOfCG = value;
}

unsigned short MDFlib::MDFDG::getNumOfRecIDs()
{
    return m_numOfRecIDs;
}

void MDFlib::MDFDG::setNumOfRecIDs(unsigned short value)
{
    m_numOfRecIDs = value;
}

quint32 MDFlib::MDFDG::getReserved2()
{
    return m_reserved2;
}

void MDFlib::MDFDG::setReserved2(quint32 value)
{
    m_reserved2 = value;
}
