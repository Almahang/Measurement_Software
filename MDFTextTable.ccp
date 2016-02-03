#include "MDFCCTextTable.h"

MDFlib::MDFCCTextTable::MDFCCTextTable(QFile *file, unsigned long pCCT, unsigned short sizeInfo, unsigned long byteOrder)
{
    myMDFFile = file;
    pairList = new QList<Pair>;

    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    QString str;
    double dbl;

    if(byteOrder == 0)
    {
        instream.setByteOrder(QDataStream::LittleEndian);
    }
    else
    {
        instream.setByteOrder(QDataStream::BigEndian);
    }

    for(int i = 0; i < sizeInfo; i++){
        myMDFFile->seek(pCCT);
        instream >> dbl;

        myMDFFile->seek(pCCT + 8);
        byteArray = myMDFFile->read(32);
        str.append(byteArray.data());
        Pair* newPair = new Pair(dbl, &str);
        pairList->append(*newPair);
    }
}

MDFlib::MDFCCTextTable::~MDFCCTextTable()
{
}

double MDFlib::MDFCCTextTable::Convert(double)
{
    return 0.0;
}

QString *MDFlib::MDFCCTextTable::StringVal(double)
{
    return new QString();
}







MDFlib::Pair::Pair(double value, QString *text)
{
    this->value = value;
    this->text = new QString(*text);
}

MDFlib::Pair::~Pair()
{
}
