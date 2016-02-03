#include "MDFCG.h"


MDFlib::MDFCG::MDFCG(void)
{
}

MDFlib::MDFCG::MDFCG(QFile* file, unsigned long pCG, unsigned long pDataRecord, unsigned short byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString blockType;
    unsigned short blockSize;
    quint32 pNextCGBlock;            //qint32 helyett long is lehetne
    quint32 pCNBlock;
    quint32 pTXBlock;
    unsigned short recordID;
    unsigned short numOfCN;
    unsigned short sizeOfDataRec;
    quint32 numOfRec;               //quint32 helyett unsigned long is lehetne


    myMDFFile->seek(pCG);
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

    myMDFFile->seek(pCG + 2);
    instream >> blockSize;
    myMDFFile->seek(pCG + 4);
    instream >> pNextCGBlock;
    myMDFFile->seek(pCG + 8);
    instream >> pCNBlock;
    myMDFFile->seek(pCG + 12);
    instream >> pTXBlock;
    myMDFFile->seek(pCG + 16);
    instream >> recordID;
    myMDFFile->seek(pCG + 18);
    instream >> numOfCN;
    myMDFFile->seek(pCG + 20);
    instream >> sizeOfDataRec;
    myMDFFile->seek(pCG + 22);
    instream >> numOfRec;

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setNextCGBlockPTR(pNextCGBlock);
    setFirstChannelPTR(pCNBlock);
    setCommentPTR(pTXBlock);
    setRecordID(recordID);
    setNumOfChannels(numOfCN);
    setDataRecordSize(sizeOfDataRec);
    setNumOfRecords(numOfRec);
    m_pDataRecord = pDataRecord;

    GetCommentBlock(byteOrder);
    GetChannelBlocks(byteOrder);
}



int MDFlib::MDFCG::GetChannelBlocks(unsigned short byteOrder)
{
    unsigned long ptrNextChannel = m_pCNBlock;
    m_mdfChan =new QList< MDFChannel* >;
    MDFChannel* time;
	int i=0;

    while(ptrNextChannel !=0)
    {
        MDFChannel* newMDFChannel = new MDFChannel(myMDFFile, ptrNextChannel, m_pDataRecord, m_numOfRec, m_sizeOfDataRec, byteOrder);
        newMDFChannel->setNumPoints(m_numOfRec);
        if(i==0) time = newMDFChannel;
        newMDFChannel->setTimeChannel(time);
        m_mdfChan->append(newMDFChannel);
        ptrNextChannel = newMDFChannel->getNextChannelPTR();
        i++;
    }

    return 0;
}

int MDFlib::MDFCG::GetCommentBlock(unsigned short byteOrder)
{
    m_comment = new MDFTX(myMDFFile, m_pTXBlock, byteOrder);
    return 0;
}

MDFlib::MDFCG::~MDFCG(void)
{
}

QList< MDFlib::MDFChannel* >* MDFlib::MDFCG::getChannels()
{
    return m_mdfChan;
}

void MDFlib::MDFCG::setChannels(QList< MDFlib::MDFChannel* >* value)
{
    m_mdfChan = value;
}

QString* MDFlib::MDFCG::getComment()
{
    return m_comment->getText();
}
void MDFlib::MDFCG::setComment(QString* value)
{
    m_comment->setText(new QString(*value));
}

QString *MDFlib::MDFCG::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFCG::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFCG::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFCG::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

unsigned long MDFlib::MDFCG::getNextCGBlockPTR()
{
    return m_pNextCGBlock;
}

void MDFlib::MDFCG::setNextCGBlockPTR(unsigned long value)
{
    m_pNextCGBlock = value;
}

unsigned long MDFlib::MDFCG::getFirstChannelPTR()
{
    return m_pCNBlock;
}

void MDFlib::MDFCG::setFirstChannelPTR(unsigned long value)
{
    m_pCNBlock = value;
}

unsigned long MDFlib::MDFCG::getCommentPTR()
{
    return m_pTXBlock;
}

void MDFlib::MDFCG::setCommentPTR(unsigned long value)
{
    m_pTXBlock = value;
}

unsigned short MDFlib::MDFCG::getRecordID()
{
    return m_recordID;
}

void MDFlib::MDFCG::setRecordID(unsigned short value)
{
    m_recordID = value;
}

unsigned short MDFlib::MDFCG::getNumOfChannels()
{
    return m_numOfCN;
}

void MDFlib::MDFCG::setNumOfChannels(unsigned short value)
{
    m_numOfCN = value;
}

unsigned short MDFlib::MDFCG::getDataRecordSize()
{
    return m_sizeOfDataRec;
}

void MDFlib::MDFCG::setDataRecordSize(unsigned short value)
{
    m_sizeOfDataRec = value;
}

unsigned long MDFlib::MDFCG::getNumOfRecords()
{
    return m_numOfRec;
}

void MDFlib::MDFCG::setNumOfRecords(unsigned long value)
{
    m_numOfRec = value;
}
