#ifndef MDFLIB_H
#define MDFLIB_H

#include <QtCore>

#include "MDFID.h"
#include "MDFHeader.h"
#include "MDFDG.h"

namespace MDFlib {
    class MDF
	{
	public:
        MDF(void);
        virtual ~MDF(void);
        int Open(QString* fileName);
        void Close();

//FileID
        MDFID* getFileID();
        void setFileID( MDFID* value);
//FileHeader
        MDFHeader* getFileHeader();
        void setFileHeader( MDFHeader* value);
//DataGroups
        QList<MDFDG*>* getDataGroups();
        void setDataGroups( QList< MDFDG* >* value);

	private:
        QFile*          myMDFFile;
		int				GetIDBlock();
        int				GetHeaderBlock();
        MDFID*          myMDFID;
        MDFHeader*      myMDFHeader;
	};
}

#endif // MDFLIB_H
