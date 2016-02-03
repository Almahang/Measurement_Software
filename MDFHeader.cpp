#include "MDFHeader.h"

MDFlib::MDFHeader::MDFHeader(QFile* file, unsigned short byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString blockType;
    unsigned short blockSize;
    quint32 pDGBlock;
    quint32 pTXBlock;
    quint32 pPRBlock;
    unsigned short numOfDG;
    QString date;
    QString time;
    QString author;
    QString organization;
    QString project;
    QString vehicleID;

    myMDFFile->seek(64);
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

    myMDFFile->seek(66);
    instream >> blockSize;
    myMDFFile->seek(68);
    instream >> pDGBlock;
    myMDFFile->seek(72);
    instream >> pTXBlock;
    myMDFFile->seek(76);
    instream >> pPRBlock;
    myMDFFile->seek(80);
    instream >> numOfDG;

    myMDFFile->seek(82);

    byteArray = myMDFFile->read(10);
    date.append(byteArray.data());
    byteArray = myMDFFile->read(8);
    time.append(byteArray.data());
    byteArray = myMDFFile->read(32);
    author.append(byteArray.data());
    byteArray = myMDFFile->read(32);
    organization.append(byteArray.data());
    byteArray = myMDFFile->read(32);
    project.append(byteArray.data());
    byteArray = myMDFFile->read(32);
    vehicleID.append(byteArray.data());

    setBlockType(&blockType);
    setBlockSize(blockSize);
    setDGBlockPTR(pDGBlock);
    setTXBlockPTR(pTXBlock);
    setPRBlockPTR(pPRBlock);
    setNumOfDG(numOfDG);
    setDate(&date);
    setTime(&time);
    setAuthor(&author);
    setOrganization(&organization);
    setProject(&project);
    setVehicleID(&vehicleID);

    GetDataBlocks(byteOrder);
    GetTextBlock(byteOrder);
    GetProgramBlock(byteOrder);
}

MDFlib::MDFHeader::~MDFHeader(void)
{
}

void MDFlib::MDFHeader::GetDataBlocks(unsigned short byteOrder)
{
    unsigned long newDGBlock = getDGBlockPTR();
    m_mdfDG = new QList< MDFDG* >;

    while(newDGBlock !=0)
    {
        MDFDG* newMDFDG = new MDFDG(myMDFFile,newDGBlock,byteOrder);
        m_mdfDG->append(newMDFDG);
        newDGBlock = newMDFDG->getNextDGBlockPTR();
    }
}

void MDFlib::MDFHeader::GetTextBlock(unsigned short byteOrder)
{
    m_comment = new MDFTX(myMDFFile, m_pTXBlock, byteOrder);
}

void MDFlib::MDFHeader::GetProgramBlock(unsigned short byteOrder)
{
    m_PRBlock = new MDFPR(myMDFFile, m_pPRBlock, byteOrder);
}

QList< MDFlib::MDFDG* >* MDFlib::MDFHeader::getDataGroups()
{
    return m_mdfDG;
}

void MDFlib::MDFHeader::setDataGroups(QList< MDFlib::MDFDG* >* value)
{
    m_mdfDG = value;
}

QString *MDFlib::MDFHeader::getComment()
{
    qDebug() << *(m_comment->getText())->toUtf8();
    return m_comment->getText();
}

void MDFlib::MDFHeader::setComment(QString *value)
{
    m_comment->setText(new QString(*value));
}

QString *MDFlib::MDFHeader::getPRBlock()
{
    return m_PRBlock->getData();
}

void MDFlib::MDFHeader::setPRBlock(QString *value)
{
    m_PRBlock->setData(new QString(*value));
}

QString *MDFlib::MDFHeader::getBlockType()
{
    return m_blockType;
}

void MDFlib::MDFHeader::setBlockType(QString *value)
{
    m_blockType = new QString(*value);
}

unsigned short MDFlib::MDFHeader::getBlockSize()
{
    return m_blockSize;
}

void MDFlib::MDFHeader::setBlockSize(unsigned short value)
{
    m_blockSize = value;
}

unsigned long MDFlib::MDFHeader::getDGBlockPTR()
{
    return m_pDGBlock;
}

void MDFlib::MDFHeader::setDGBlockPTR(unsigned long value)
{
    m_pDGBlock = value;
}

unsigned long MDFlib::MDFHeader::getTXBlockPTR()
{
    return m_pTXBlock;
}

void MDFlib::MDFHeader::setTXBlockPTR(unsigned long value)
{
    m_pTXBlock = value;
}

unsigned long MDFlib::MDFHeader::getPRBlockPTR()
{
    return m_pPRBlock;
}

void MDFlib::MDFHeader::setPRBlockPTR(unsigned long value)
{
    m_pPRBlock = value;
}

unsigned short MDFlib::MDFHeader::getNumOfDG()
{
    return m_numOfDG;
}

void MDFlib::MDFHeader::setNumOfDG(unsigned short value)
{
    m_numOfDG = value;
}

QString* MDFlib::MDFHeader::getDate()
{
    return m_date;
}

void MDFlib::MDFHeader::setDate(QString* value)
{
    m_date = new QString(*value);
}

QString* MDFlib::MDFHeader::getTime()
{
    return m_time;
}

void MDFlib::MDFHeader::setTime(QString* value)
{
    m_time = new QString(*value);
}

QString* MDFlib::MDFHeader::getAuthor()
{
    return m_author;
}

void MDFlib::MDFHeader::setAuthor(QString* value)
{
    m_author = new QString(*value);
}

QString* MDFlib::MDFHeader::getOrganization()
{
    return m_organiz;
}

void MDFlib::MDFHeader::setOrganization(QString* value)
{
    m_organiz = new QString(*value);
}

QString* MDFlib::MDFHeader::getProject()
{
    return m_project;
}

void MDFlib::MDFHeader::setProject(QString* value)
{
    m_project = new QString(*value);
}

QString* MDFlib::MDFHeader::getVehicleID()
{
    return m_vehicleID;
}

void MDFlib::MDFHeader::setVehicleID(QString* value)
{
    m_vehicleID = new QString(*value);
}
