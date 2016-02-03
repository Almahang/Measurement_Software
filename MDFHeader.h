#ifndef MDFHEADER_H
#define MDFHEADER_H

#include <QtCore>
#include <QDebug>

#include "MDFDG.h"
#include "MDFTX.h"
#include "MDFPR.h"

namespace MDFlib {
    class MDFHeader
    {
    public:
        MDFHeader(QFile* file, unsigned short byteOrder);
        virtual ~MDFHeader(void);

//DataGroups
            QList< MDFlib::MDFDG* >* getDataGroups();
            void setDataGroups(QList< MDFlib::MDFDG* >* value);
//Comment
            QString* getComment();
            void setComment(QString* value);
//PRBlock
            QString* getPRBlock();
            void setPRBlock(QString* value);

//BlockType
            QString* getBlockType();
            void setBlockType(QString* value);
//BlockSize
            unsigned short getBlockSize();
            void setBlockSize(unsigned short value);
//DGBlockPTR
            unsigned long getDGBlockPTR();
            void setDGBlockPTR(unsigned long value);
//TXBlockPTR
            unsigned long getTXBlockPTR();
            void setTXBlockPTR(unsigned long value);
//PRBlockPTR
            unsigned long getPRBlockPTR();
            void setPRBlockPTR(unsigned long value);
//NumOfDG
            unsigned short getNumOfDG();
            void setNumOfDG(unsigned short value);
//Date
            QString* getDate();
            void setDate(QString* value);
//Time
            QString* getTime();
            void setTime(QString* value);
//Author
            QString* getAuthor();
            void setAuthor(QString* value);
//Organization
            QString* getOrganization();
            void setOrganization(QString* value);
//Project
            QString* getProject();
            void setProject(QString* value);
//VehicleID
            QString* getVehicleID();
            void setVehicleID(QString* value);

    private:
            QFile* myMDFFile;
            MDFTX* m_comment;
            MDFPR* m_PRBlock;
            QList<MDFDG*>*  m_mdfDG;                        //Stores pointers to Data Group Blocks
            void GetDataBlocks(unsigned short byteOrder);
            void GetTextBlock(unsigned short byteOrder);
            void GetProgramBlock(unsigned short byteOrder);

            QString*            m_blockType;
            unsigned short      m_blockSize;
            unsigned long       m_pDGBlock;					//Pointer to the first Data Group Block
            unsigned long       m_pTXBlock;                 //Pointer to the comment of Header Block
            unsigned long       m_pPRBlock;                 //Pointer to the Program Block
            unsigned short		m_numOfDG;					//Number of Data Group Blocks
            QString*			m_date;						//Date the file was created
            QString*			m_time;						//Time the file was created
            QString*			m_author;					//Author's name
            QString*			m_organiz;					//Name of organization or department
            QString*			m_project;					//Project name
            QString*			m_vehicleID;                //Measurement object eg. the vehicle identification
    };
}

#endif // MDFHEADER_H
