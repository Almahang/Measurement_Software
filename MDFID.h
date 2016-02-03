#ifndef MDFID_H
#define MDFID_H

#include <QtCore>

namespace MDFlib {
    class MDFID
	{
	public:
        MDFID(QFile* file);
		virtual ~MDFID(void);

//FileID
        QString* getFileID();
        void setFileID(QString* value);
//FileVer
        QString* getFileVer();
        void setFileVer(QString* value);
//ProgID
        QString* getProgID();
        void setProgID(QString* value);
//ByteOrder
        unsigned short getByteOrder();
        void setByteOrder(unsigned short value);
//FloatingPointFormat
        unsigned short getFloatingPointFormat();
        void setFloatingPointFormat(unsigned short value);
//FileVerInt
        unsigned short getFileVerInt();
        void setFileVerInt(unsigned short value);
//Reserved1
        unsigned short getReserved1();
        void setReserved1(unsigned short value);
//Reserved2
        QString* getReserved2();
        void setReserved2(QString* value);
//Reserved3
        QString* getReserved3();
        void setReserved3(QString* value);

	private:
        QFile*               myMDFFile;

        QString*			m_fileID;					//File Identifier  (Always "MDF     ")
        QString*			m_fileVer;  				//Format Identifier "3.00    "
        QString*			m_progID;                   //Program which generated the MDF file
        unsigned short      m_floatingPointFormat;
        unsigned short		m_byteOrder;				//0=Little Endian, 1=Big Endian
        unsigned short		m_fileVerInt;				//Same as Format Indentifier except as a short (300)
        unsigned short      m_reserved1;
        QString*            m_reserved2;
        QString*            m_reserved3;
	};
}

#endif // MDFID_H
