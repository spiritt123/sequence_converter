//#pragma once

#ifndef LOAD_STYLE 
#define LOAD_STYLE 

#include <QString>
#include <QString>
#include <QFile>
#include <QTextStream>

inline QString loadStyle(QString path)
{
    QString data;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        data += line + "\n";
    }
    file.close();
    return data;
}

#endif //LOAD_STYLE
