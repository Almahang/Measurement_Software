#ifndef MDFCG_H
#define MDFCG_H

#include <QtCore>

#include "MDFChannel.h"
#include "MDFTX.h"

namespace MDFlib {
    class MDFCG
	{
	public:
		MDFCG(void);
		virtual ~MDFCG(void);
        MDFCG(QFile* file, unsigned long pCG, unsigned long pData, unsigned short byteOrder);

//BlockType
        QString* getBlockType();
        void setBlockType(QString* value);
//BlockSize
        unsigned short getBlockSize();
        void setBlockSize(unsigned short value);
//FirstChannelPTR
        unsigned long getFirstChannelPTR();
        void setFirstChannelPTR(unsigned long value);
//NextCGBlockPTR
        unsigned long getNextCGBlockPTR();
        void setNextCGBlockPTR(unsigned long value);
//CommentPTR
        unsigned long getCommentPTR();
        void setCommentPTR(unsigned long value);
//RecordID
        unsigned short getRecordID();
        void setRecordID(unsigned short value);
//NumOfChannels
        unsigned short getNumOfChannels();
        void setNumOfChannels(unsigned short value);
//DataRecordSize
        unsigned short getDataRecordSize();
        void setDataRecordSize(unsigned short value);
//NumOfRecords
        unsigned long getNumOfRecords();
        void setNumOfRecords(unsigned long value);


//Comment
        QString *getComment();
        void setComment(QString* value);
//Channels
        QList< MDFChannel* >* getChannels();
        void setChannels( QList< MDFChannel* >* value);

	private:
        int GetChannelBlocks(unsigned short byteOrder);
        int GetCommentBlock(unsigned short byteOrder);

        unsigned long           m_pDataRecord;                      //Pointer in the file to the data
        MDFTX*                  m_comment;
        MDFChannel*             timeChannel;						//The time channel
        QFile*                  myMDFFile;                      	//Pointer to the opened file
        QList < MDFChannel* >*  m_mdfChan;                          //Contains each of the channels in the Channel Group

        QString*                m_blockType;
        unsigned short          m_blockSize;
        unsigned long           m_pNextCGBlock;						//Pointer in the file to the next Channel Group
        unsigned long           m_pCNBlock;                         //Pointer in the file to the first Channel
        unsigned long           m_pTXBlock;                         //Pointer to a comment block (not implemented)
        unsigned short          m_recordID;							//
        unsigned short			m_numOfCN;                          //Total number of channels in this Channel Group
        unsigned short			m_sizeOfDataRec;                    //Number of bytes for a record containing one value from each Channel
        unsigned long			m_numOfRec;                         //Total number of records in the data set
	};
}

#endif // MDFCG_H
