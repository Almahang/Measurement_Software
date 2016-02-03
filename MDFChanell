#ifndef MDFCHANNEL_H
#define MDFCHANNEL_H

#include <QtCore>

#include "MDFCC.h"
#include "MDFTX.h"

namespace MDFlib {
    class MDFChannel
	{
	public:
		MDFChannel(void);
        virtual ~MDFChannel(void);
        virtual QString* ToString(void);

        MDFChannel(QFile* file, unsigned long pCN, unsigned long pFileData, unsigned long elements, unsigned long blockSize, unsigned short byteOrder);


//TimeChannel
        MDFChannel* getTimeChannel();
        void setTimeChannel(MDFChannel* value);
//Comment
        QString *getComment();
        void setComment(QString* value);
//ASAM_MCDName
        QString *getASAM_MCDName();
        void setASAM_MCDName(QString* value);
//DisplayID
        QString *getDisplayID();
        void setDisplayID(QString* value);
//Data
        QList<double>* getData();
//Conversion
        MDFCC *getConversion();
//Load the data
        void LoadData();

//BlockType
        QString* getBlockType();
        void setBlockType(QString* value);
//BlockSize
        unsigned short getBlockSize();
        void setBlockSize(unsigned short value);
//NextChannelPTR
        unsigned long getNextChannelPTR();
        void setNextChannelPTR(unsigned long value);
//CCBlockPTR
        unsigned long getCCBlockPTR();
        void setCCBlockPTR(unsigned long value);
//CEBlockPTR
        unsigned long getCEBlockPTR();
        void setCEBlockPTR(unsigned long value);
//CDBlockPTR
        unsigned long getCDBlockPTR();
        void setCDBlockPTR(unsigned long value);
//CommentPTR
        unsigned long getCommentPTR();
        void setCommentPTR(unsigned long value);
//ChannelType
        unsigned short getChannelType();
        void setChannelType(unsigned short value);
//NameOfSignal
        QString* getNameOfSignal();
        void setNameOfSignal(QString* value);
//DescriptionOfSignal
        QString* getDescriptionOfSignal();
        void setDescriptionOfSignal(QString* value);
//FirstBitPos
        unsigned short getFirstBitPos();
        void setFirstBitPos(unsigned short value);
//NumOfBits
        unsigned short getNumOfBits();
        void setNumOfBits(unsigned short value);
//DataType
        unsigned short getDataType();
        void setDataType(unsigned short value);
//ValueRange
        unsigned short getValueRange();
        void setValueRange(unsigned short value);
//Minimum
        double getMinimum();
        void setMinimum(double value);
//Maximum
        double getMaximum();
        void setMaximum(double value);
//SampleRate
        double getSampleRate();
        void setSampleRate(double value);
//ASAM_MCDPTR
        unsigned long getASAM_MCDPTR();
        void setASAM_MCDPTR(unsigned long value);
//DisplayIDPTR
        unsigned long getDisplayIDPTR();
        void setDisplayIDPTR(unsigned long value);
//ByteOffset
        unsigned short getByteOffset();
        void setByteOffset(unsigned short value);

//Units
        QString* getUnits();
        void setUnits(QString* value);
//NumPoints
        unsigned long getNumPoints();
        void setNumPoints(unsigned long value);

    private:
        QFile*			myMDFFile;
        MDFChannel*     m_timeChannel;
        MDFTX*          m_comment;
        MDFTX*          m_ASAM_MCD;
        MDFTX*          m_displayID;
        MDFCC*          m_conversion;

        QString*        m_blockType;
        unsigned short  m_blockSize;
        unsigned long   m_pNextChannel;
        unsigned long   m_pCCBlock;
        unsigned long   m_pCEBlock;
        unsigned long   m_pCDBlock;
        unsigned long   m_pTXBlock1;
        unsigned short  m_channelType;
        QString*		m_nameOfSignal;
        QString*		m_descriptionOfSignal;
        unsigned short	m_firstBitPos;
        unsigned short	m_numOfBits;
        unsigned short	m_dataType;
        unsigned short	m_valueRange;
        double			m_min;
        double			m_max;
        double			m_sampleRate;
        unsigned long   m_pTXBlock2;
        unsigned long   m_pTXBlock3;
        unsigned short	m_byteOffset;               //additional

        unsigned long   m_numPoints;
        bool            m_loaded;

        unsigned long   m_pDataRecord;
        unsigned long   m_numOfRec;
        unsigned long   m_sizeOfDataRec;
        unsigned short  m_byteOrder;
	};
}

#endif // MDFCHANNEL_H
