#ifndef MDFCCTEXTTABLE_H
#define MDFCCTEXTTABLE_H

#include "MDFConversion.h"

namespace MDFlib {
    class Pair
    {
    public:
        Pair(double value, QString* text);
        ~Pair();

//Text
        QString* getText();
        void setText(QString* value);
//Value
        double getValue();
        void setValue(double value);

    private:
        QString* text;
        double value;
    };



    class MDFCCTextTable : public MDFConversion
    {
    public:
        MDFCCTextTable(QFile* file, unsigned long pCCT, unsigned short sizeInfo, unsigned long byteOrder);
        ~MDFCCTextTable();
        virtual double Convert(double value);
        virtual QString* StringVal(double value);

    private:
        QFile* myMDFFile;
        QList<Pair>* pairList;
    };
}

#endif // MDFCCTEXTTABLE_H
