#include "defaultnames.h"
#include <QCoreApplication>


namespace DB {

const QString DefaulTableNames::MARKER = QString("mark");
const QString DefaulTableNames::MARKER_POINTS = QString("mark_points");
const QString DefaulTableNames::DIAGNOSIS = QString("diagnosis");
const QString DefaulTableNames::LOW_DICTIONARY = QString("mark_name");
const QString DefaulTableNames::ENTRIES = QString("entry");
const QString DefaulTableNames::MORPHOLOGY = QString("morph_tthing");

#ifdef Q_OS_MAC
const QString DefaultDbSettings::DB_FILENAME = QString("%1/../../../db/ExpSysDb.mwb").arg(QCoreApplication::applicationDirPath());
#else
const QString DefaultDbSettings::DB_FILENAME = QString("%1/../db/ExpSysDb.mwb").arg(QCoreApplication::applicationDirPath());
#endif
const QString DefaultDbSettings::HOST = QString("127.0.0.1");
const QString DefaultDbSettings::USER = QString("user");
const QString DefaultDbSettings::PASS = QString("pass");

}
