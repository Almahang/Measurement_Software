#include "MDFChannel.h"

MDFlib::MDFChannel::MDFChannel(void)
{
}

MDFlib::MDFChannel::~MDFChannel(void)
{
}

QString* MDFlib::MDFChannel::ToString(void)
{
    QString *str = new QString(*m_nameOfSignal + "  sampleRate=" + QString::number(m_sampleRate));

    return str;
}

MDFlib::MDFChannel::MDFChannel(QFile* file, unsigned long pCN, unsigned long pDataRecord, unsigned long numOfRec, unsigned long sizeOfDataRec, unsigned short byteOrder)
{
    m_loaded = false;
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString blockType;
    unsigned short blockSize;
    quint32 pNextChannel;                //qint32 helyett long is lehetne
    quint32 pCCBlock;
    quint32 pCEBlock;
    quint32 pCDBlock;
    quint32 pTXBlock1;
    unsigned short channelType;
    QString nameOfSignal;
    QString descriptionOfSignal;
    unsigned short firstBitPos;
    unsigned short numOfBits;
    unsigned short dataType;
    unsigned short valueRange;
    double min;
    double max;
    double sampleRate;
    quint32 pTXBlock2;
    quint32 pTXBlock3;
    unsigned short byteOffset;

    myMDFFile->seek(pCN);
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

    myMDFFile->seek(pCN + 2);
    instream >> blockSize;
    myMDFFile->seek(pCN + 4);
    instream >> pNextChannel;
    myMDFFile->seek(pCN + 8);
    instream >> pCCBlock;
    myMDFFile->seek(pCN + 12);
    instream >> pCEBlock;
    myMDFFile->seek(pCN + 16);
    instream >> pCDBlock;
    myMDFFile->seek(pCN + 20);
    instream >> pTXBlock1;
    myMDFFile->seek(pCN + 24);
    instream >> channelType;

    myMDFFile->seek(pCN + 26);
    byteArray = myMDFFile->read(32);
    nameOfSignal.append(byteArray.data());
    byteArray = myMDFFile->read(128);
    descriptionOfSignal.append(byteArray.data());

    myMDFFile->seek(pCN + 186);
    instream >> firstBitPos;
    myMDFFile->seek(pCN + 188);
    instream >> numOfBits;
    myMDFFile->seek(pCN + 190);
    instream >> dataType;
    myMDFFile->seek(pCN + 192);
    instream >> valueRange;
    myMDFFile->seek(pCN + 194);
    instream >> min;
    myMDFFile->seek(pCN + 202);
    instream >> max;
    myMDFFile->seek(pCN + 210);
    instream >> sampleRate;
    myMDFFile->seek(pCN + 218);
    instream >> pTXBlock2;
    myMDFFile->seek(pCN + 222);
    instream >> pTXBlock3;
    myMDFFile->seek(pCN + 226);
    instream >> byteOffset;

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setNextChannelPTR(pNextChannel);
    setCCBlockPTR(pCCBlock);
    setCEBlockPTR(pCEBlock);
    setCDBlockPTR(pCDBlock);
    setCommentPTR(pTXBlock1);
    setChannelType(channelType);
    setNameOfSignal(&nameOfSignal);
    setDescriptionOfSignal(&descriptionOfSignal);
    setFirstBitPos(firstBitPos);
    setNumOfBits(numOfBits);
    setDataType(dataType);
    setValueRange(valueRange);
    setMinimum(min);
    setMaximum(max);
    setSampleRate(sampleRate);
    setASAM_MCDPTR(pTXBlock2);
    setDisplayIDPTR(pTXBlock3);
    setByteOffset(byteOffset);

    m_pDataRecord = pDataRecord;
    m_numOfRec = numOfRec;
    m_sizeOfDataRec = sizeOfDataRec;
    m_byteOrder = byteOrder;

    m_comment = new MDFTX(myMDFFile, m_pTXBlock1, byteOrder);
    m_ASAM_MCD = new MDFTX(myMDFFile, m_pTXBlock2, byteOrder);
    m_displayID = new MDFTX(myMDFFile, m_pTXBlock3, byteOrder);
}

MDFlib::MDFChannel* MDFlib::MDFChannel::getTimeChannel()
{
    return m_timeChannel;
}

void MDFlib::MDFChannel::setTimeChannel(MDFlib::MDFChannel* value)
{
    m_timeChannel = value;
}

QString* MDFlib::MDFChannel::getComment()
{
    return m_comment->getText();
}

void MDFlib::MDFChannel::setComment(QString *value)
{
    m_comment->setText(new QString(*value));
}

QString *MDFlib::MDFChannel::getASAM_MCDName()
{
    return m_ASAM_MCD->getText();
}

void MDFlib::MDFChannel::setASAM_MCDName(QString *value)
{
    m_ASAM_MCD->setText(new QString(*value));
}

QString *MDFlib::MDFChannel::getDisplayID()
{
    return m_displayID->getText();
}

void MDFlib::MDFChannel::setDisplayID(QString *value)
{
    m_displayID->setText(new QString(*value));
}

QList<double> *MDFlib::MDFChannel::getData()
{
    return m_conversion->getData();
}

MDFlib::MDFCC *MDFlib::MDFChannel::getConversion()
{
    return m_conversion;
}

void MDFlib::MDFChannel::LoadData()
{
    if(!m_loaded){
        m_conversion = new MDFCC(myMDFFile, m_pCCBlock, m_dataType, m_pDataRecord, m_numOfRec, m_sizeOfDataRec, m_firstBitPos, m_numOfBits, m_byteOrder);
        m_loaded = true;
    }
}

QString *MDFlib::MDFChannel::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFChannel::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFChannel::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFChannel::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

unsigned long MDFlib::MDFChannel::getNextChannelPTR()
{
    return m_pNextChannel;
}

void MDFlib::MDFChannel::setNextChannelPTR(unsigned long value)
{
    m_pNextChannel = value;
}

unsigned long MDFlib::MDFChannel::getCCBlockPTR()
{
    return m_pCCBlock;
}

void MDFlib::MDFChannel::setCCBlockPTR(unsigned long value)
{
    m_pCCBlock = value;
}

unsigned long MDFlib::MDFChannel::getCEBlockPTR()
{
    return m_pCEBlock;
}

void MDFlib::MDFChannel::setCEBlockPTR(unsigned long value)
{
    m_pCEBlock = value;
}

unsigned long MDFlib::MDFChannel::getCDBlockPTR()
{
    return m_pCDBlock;
}

void MDFlib::MDFChannel::setCDBlockPTR(unsigned long value)
{
    m_pCDBlock = value;
}

unsigned long MDFlib::MDFChannel::getCommentPTR()
{
    return m_pTXBlock1;
}

void MDFlib::MDFChannel::setCommentPTR(unsigned long value)
{
    m_pTXBlock1 = value;
}

unsigned short MDFlib::MDFChannel::getChannelType()
{
    return m_channelType;
}

void MDFlib::MDFChannel::setChannelType(unsigned short value)
{
    m_channelType = value;
}

QString* MDFlib::MDFChannel::getNameOfSignal()
{
    return m_nameOfSignal;
}

void MDFlib::MDFChannel::setNameOfSignal(QString* value)
{
    m_nameOfSignal = new QString(*value);
}

QString* MDFlib::MDFChannel::getDescriptionOfSignal()
{
    return m_descriptionOfSignal;
}

void MDFlib::MDFChannel::setDescriptionOfSignal(QString* value)
{
    m_descriptionOfSignal = new QString(*value);
}

unsigned short MDFlib::MDFChannel::getFirstBitPos()
{
    return m_firstBitPos;
}

void MDFlib::MDFChannel::setFirstBitPos(unsigned short value)
{
    m_firstBitPos = value;
}

unsigned short MDFlib::MDFChannel::getNumOfBits()
{
    return m_numOfBits;
}

void MDFlib::MDFChannel::setNumOfBits(unsigned short value)
{
    m_numOfBits = value;
}

unsigned short MDFlib::MDFChannel::getDataType()
{
    return m_dataType;
}

void MDFlib::MDFChannel::setDataType(unsigned short value)
{
    m_dataType = value;
}

unsigned short MDFlib::MDFChannel::getValueRange()
{
    return m_valueRange;
}

void MDFlib::MDFChannel::setValueRange(unsigned short value)
{
    m_valueRange = value;
}

double MDFlib::MDFChannel::getMinimum()
{
    return m_min;
}

void MDFlib::MDFChannel::setMinimum(double value)
{
    m_min = value;
}

double MDFlib::MDFChannel::getMaximum()
{
    return m_max;
}

void MDFlib::MDFChannel::setMaximum(double value)
{
    m_max = value;
}

double MDFlib::MDFChannel::getSampleRate()
{
    return m_sampleRate;
}

void MDFlib::MDFChannel::setSampleRate(double value)
{
    m_sampleRate = value;
}

unsigned long MDFlib::MDFChannel::getASAM_MCDPTR()
{
    return m_pTXBlock2;
}

void MDFlib::MDFChannel::setASAM_MCDPTR(unsigned long value)
{
    m_pTXBlock2 = value;
}

unsigned long MDFlib::MDFChannel::getDisplayIDPTR()
{
    return m_pTXBlock3;
}

void MDFlib::MDFChannel::setDisplayIDPTR(unsigned long value)
{
    m_pTXBlock3 = value;
}

unsigned short MDFlib::MDFChannel::getByteOffset()
{
    return m_byteOffset;
}

void MDFlib::MDFChannel::setByteOffset(unsigned short value)
{
    m_byteOffset = value;
}


//CCBlock
QString* MDFlib::MDFChannel::getUnits()
{
    return m_conversion->getPhysUnit();
}

void MDFlib::MDFChannel::setUnits(QString* value)
{
    m_conversion->setPhysUnit(value);
}

unsigned long MDFlib::MDFChannel::getNumPoints()
{
    return m_numPoints;
}

void MDFlib::MDFChannel::setNumPoints(unsigned long value)
{
    m_numPoints = value;
}
