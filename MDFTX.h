#ifndef MDFTX_H
#define MDFTX_H

#include <QtCore>
#include <QDebug>

namespace MDFlib {
    class MDFTX
    {
    public:
        MDFTX(QFile* file, long pTX, unsigned short byteOrder);
        ~MDFTX(void);

//BlockType
        QString* getBlockType();
        void setBlockType(QString* value);
//BlockSize
        unsigned short getBlockSize();
        void setBlockSize(unsigned short value);
//Text
        QString* getText();
        void setText(QString* value);

    private:
        QFile*              myMDFFile;
        QString*            m_blockType;
        unsigned short      m_blockSize;
        QString*            m_text;
    };
}

#endif // MDFTX_H
