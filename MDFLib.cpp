#include "MDFLib.h"

MDFlib::MDF::MDF(void)
{
    myMDFFile = new QFile();
}

MDFlib::MDF::~MDF(void)
{
    if (myMDFFile->isOpen())
    {
        myMDFFile->close();
	}
}

MDFlib::MDFID* MDFlib::MDF::getFileID()
{
    return myMDFID;
}

void MDFlib::MDF::setFileID(MDFlib::MDFID* value)
{
    myMDFID = value;
}

MDFlib::MDFHeader* MDFlib::MDF::getFileHeader()
{
    return myMDFHeader;
}

void MDFlib::MDF::setFileHeader(MDFlib::MDFHeader* value)
{
    myMDFHeader = value;
}

QList< MDFlib::MDFDG* >* MDFlib::MDF::getDataGroups()
{
    return myMDFHeader->getDataGroups();
}

void MDFlib::MDF::setDataGroups(QList< MDFlib::MDFDG* >* value)
{
    myMDFHeader->setDataGroups(value);
}

int	MDFlib::MDF::Open(QString* fileName)
{
    Close();
    myMDFFile->setFileName(*fileName);
    myMDFFile->open(QIODevice::ReadOnly);
    if(myMDFFile->isOpen() && myMDFFile->isReadable())
	{
        GetIDBlock();
        GetHeaderBlock();
    }
    else return 1;

	return 0;
}

void MDFlib::MDF::Close()
{
    if (myMDFFile->isOpen())
    {
        myMDFFile->close();
	}
	return;
}

int	MDFlib::MDF::GetIDBlock()
{
    myMDFID = new MDFID(myMDFFile);
	return 0;
}

int	MDFlib::MDF::GetHeaderBlock()
{
    myMDFHeader = new MDFHeader(myMDFFile, myMDFID->getByteOrder());
    return 0;
}



