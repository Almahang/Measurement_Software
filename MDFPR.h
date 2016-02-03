#ifndef MDFPR_H
#define MDFPR_H

#include <QtCore>

namespace MDFlib{
    class MDFPR
    {
    public:
        MDFPR(QFile* file, long pTX, unsigned short byteOrder);
        ~MDFPR(void);

//BlockType
        QString* getBlockType();
        void setBlockType(QString* value);
//BlockSize
        unsigned short getBlockSize();
        void setBlockSize(unsigned short value);
//Data
        QString* getData();
        void setData(QString* value);

    private:
        QFile*              myMDFFile;
        QString*            m_blockType;
        unsigned short      m_blockSize;
        QString*            m_data;
    };
}

#endif // MDFPR_H
