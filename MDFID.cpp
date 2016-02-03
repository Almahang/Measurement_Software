#include "MDFID.h"

MDFlib::MDFID::MDFID(QFile* file)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString fileID;
    QString fileVer;
    QString progID;
    unsigned short byteOrder;
    unsigned short floatingPointFormat;
    unsigned short fileVerInt;
    unsigned short reserved1;
    QString reserved2;
    QString reserved3;

    instream.setByteOrder(QDataStream::LittleEndian);
    myMDFFile->seek(0);

    byteArray = myMDFFile->read(8);
    fileID.append(byteArray.data());
    byteArray = myMDFFile->read(8);
    fileVer.append(byteArray.data());
    byteArray = myMDFFile->read(8);
    progID.append(byteArray.data());

    myMDFFile->seek(24);
    instream >> byteOrder;
    myMDFFile->seek(26);
    instream >> floatingPointFormat;
    myMDFFile->seek(28);
    instream >> fileVerInt;
    myMDFFile->seek(30);
    instream >> reserved1;

    myMDFFile->seek(32);
    byteArray = myMDFFile->read(2);
    reserved2.append(byteArray.data());
    byteArray = myMDFFile->read(30);
    reserved3.append(byteArray.data());

    setFileID(&fileID);
    setProgID(&progID);
    setFileVer(&fileVer);
    setByteOrder(byteOrder);
    setFloatingPointFormat(floatingPointFormat);
    setFileVerInt(fileVerInt);
    setReserved1(reserved1);
    setReserved2(&reserved2);
    setReserved3(&reserved3);
}

MDFlib::MDFID::~MDFID(void)
{
}

QString* MDFlib::MDFID::getFileID()
{
    return m_fileID;
}

void MDFlib::MDFID::setFileID(QString* value)
{
    m_fileID = new QString(*value);
}

QString* MDFlib::MDFID::getFileVer()
{
    return m_fileVer;
}

void MDFlib::MDFID::setFileVer(QString* value)
{
    m_fileVer = new QString(*value);
}

QString* MDFlib::MDFID::getProgID()
{
    return m_progID;
}

void MDFlib::MDFID::setProgID(QString* value)
{
    m_progID = new QString(*value);
}

unsigned short MDFlib::MDFID::getByteOrder()
{
    return m_byteOrder;
}

void MDFlib::MDFID::setByteOrder(unsigned short value)
{
    m_byteOrder = value;
}

unsigned short MDFlib::MDFID::getFloatingPointFormat()
{
    return m_floatingPointFormat;
}

void MDFlib::MDFID::setFloatingPointFormat(unsigned short value)
{
    m_floatingPointFormat = value;
}

unsigned short MDFlib::MDFID::getFileVerInt()
{
    return m_fileVerInt;
}

void MDFlib::MDFID::setFileVerInt(unsigned short value)
{
    m_fileVerInt = value;
}

unsigned short MDFlib::MDFID::getReserved1()
{
    return m_reserved1;
}

void MDFlib::MDFID::setReserved1(unsigned short value)
{
    m_reserved1 = value;
}

QString *MDFlib::MDFID::getReserved2()
{
    return m_reserved2;
}

void MDFlib::MDFID::setReserved2(QString *value)
{
    m_reserved2 = new QString(*value);
}

QString *MDFlib::MDFID::getReserved3()
{
    return m_reserved3;
}

void MDFlib::MDFID::setReserved3(QString *value)
{
    m_reserved3 = new QString(*value);
}
