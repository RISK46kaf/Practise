#include "defaultnames.h"
#include <QCoreApplication>


namespace Tables {

QString DefaulNames::DB_FILENAME = QString("%1/../db/ExpSysDb.mwb").arg(QCoreApplication::applicationDirPath());
QString DefaulNames::MARKER = QString("mark");
QString DefaulNames::DIAGNOSIS = QString("diagnosis");
QString DefaulNames::LOW_DICTIONARY = QString("mark_name");
QString DefaulNames::ENTRIES = QString("entry");
QString DefaulNames::MORPHOLOGY = QString("morph_tthing");

}
