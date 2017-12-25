#include <QTextEdit>

#include "file.h"

UnknownFile::UnknownFile(QString name, AbstractFile *p_parent)
:AbstractFile(false, name, p_parent, NULL)
{
}
