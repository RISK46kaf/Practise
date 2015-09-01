#ifndef DEFAULTNAMES_H
#define DEFAULTNAMES_H

#include <QString>

namespace DB {

struct DefaulTableNames{
    const static QString MARKER;
    const static QString DIAGNOSIS;
    const static QString LOW_DICTIONARY;
    const static QString ENTRIES;
    const static QString MORPHOLOGY;
};

struct DefaultDbSettings{
    const static QString HOST;
    const static QString USER;
    const static QString PASS;
    const static QString DB_FILENAME;
};

}


#endif // DEFAULTNAMES_H
