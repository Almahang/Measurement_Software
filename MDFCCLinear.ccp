#include "MDFCCLinear.h"

MDFlib::MDFCCLinear::MDFCCLinear(QFile* file, unsigned long pCCL, unsigned long byteOrder)
{
    myMDFFile = file;
    QByteArray byteArray;
    QDataStream instream(myMDFFile);

    double p1;
    double p2;

    myMDFFile->seek(pCCL);
    if(byteOrder == 0)
    {
        instream.setByteOrder(QDataStream::LittleEndian);
    }
    else
    {
        instream.setByteOrder(QDataStream::BigEndian);
    }

    myMDFFile->seek(pCCL);
    instream >> p1;
    myMDFFile->seek(pCCL + 8);
    instream >> p2;

    setP1(p1);
    setP2(p2);
}

MDFlib::MDFCCLinear::~MDFCCLinear(void)
{
}

double MDFlib::MDFCCLinear::Convert(double value)
{
    return (value * P2 + P1);
}

QString* MDFlib::MDFCCLinear::StringVal(double value)
{
    QString* str = new QString;
    *str = "{" + QString::number(value) + "}";
    return str;
}

double MDFlib::MDFCCLinear::getP1()
{
    return P1;
}

void MDFlib::MDFCCLinear::setP1(double value)
{
    P1 = value;
}

double MDFlib::MDFCCLinear::getP2()
{
    return P2;
}

void MDFlib::MDFCCLinear::setP2(double value)
{
    P2 = value;
}
