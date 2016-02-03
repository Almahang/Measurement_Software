#ifndef MDFCCLINEAR_H
#define MDFCCLINEAR_H

#include <QtCore>

#include "MDFConversion.h"

namespace MDFlib {
    class MDFCCLinear : public MDFConversion
	{
	public:
        MDFCCLinear(QFile* file, unsigned long pCCL, unsigned long byteOrder);
        ~MDFCCLinear(void);
        virtual double Convert(double value);
        virtual QString* StringVal(double value);

//P1
        double getP1();
        void setP1(double value);
//P2
        double getP2();
        void setP2(double value);

    private:
        QFile* myMDFFile;
		double P1;
		double P2;
	};
}

#endif // MDFCCLINEAR_H
