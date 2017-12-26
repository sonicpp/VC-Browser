#include <QTextEdit>

#include "file.h"

UnknownFile::UnknownFile(QString name, AbstractFile *p_parent)
:AbstractFile(false, name, p_parent, NULL)
{
}

bool UnknownFile::setData(std::ifstream *p_file, QProgressDialog *p_progress)
{

}

bool UnknownFile::setData(uint8_t *data, size_t size, QProgressDialog *p_progress)
{

}
