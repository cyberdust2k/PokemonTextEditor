/*
 *      PokemonTextEditor (PTE)
 *      Éditeur de texte pour les jeux de Pokémon de génération III
 *      Copyright (C) 2016-2017 HopelessFrench
 *      License: General Public License 3.0
 */


/* Included headers */
#include <string.hpp>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QMap>


/* Variables */
QMap<uchar, QString> table;


void loadtable()
{
    QFile ftbl(QApplication::applicationDirPath() + "/ini/" + "Table.ini");
    ftbl.open(QIODevice::ReadOnly);
    QString ttbl(ftbl.readAll());
    QStringList tlines = ttbl.split('\n', QString::SkipEmptyParts);

    // loop each line and split pair
    foreach (QString s,tlines)
    {
        qint32 pos = s.indexOf('=');
        QString strnum = s.left(pos);
        QString strchr = s.mid(pos+1);

        // try convert string to number
        uchar num = (uchar)(strnum.toUInt(NULL, 16));
        table.insert(num, strchr);
    }


    ftbl.close();
}


const QString readpokestring(uchar *rom, uint offset, bool beg)
{
    // read until 0xFF encountered
    QString output;
    QByteArray bytes;
    uchar *start = rom + offset;

    if (!beg)
    {
        while (*start != 0xFF)
            bytes.append(*start++);
    }
    else
    {
        while (*start != 0xFF)
            start--;
        start++;

        while (*start != 0xFF)
            bytes.append(*start++);
    }


    // decode each char
    for (int i = 0; i < bytes.size(); /* we control increment ourselves */)
    {
        uchar character = bytes.at(i++);
        if (character == 0xF8 || character == 0xF9 || character == 0xFD)
        {
            QString toapp;
            uchar param = bytes.at(i++);

            auto find = table.find(character);
            if (find != table.end())
            {
                QString num = QString::number(param, 16);
                if (num.length() == 1)
                    num.insert(0, '0'); // align to 2 bytes

                toapp.append(find.value());
                toapp.append(QString("\\") + num);
            }
            else
            {
                toapp.append(QString("\\h") + QString::number(character, 16));
            }

            output.append(toapp);
        }
        else if (character == 0xFC)
        {
            QString toapp;
            uchar param = bytes.at(i++);

            auto find = table.find(character);
            if (find != table.end())
            {
                QString num = QString::number(param, 16);
                if (num.length() == 1)
                    num.insert(0, '0'); // align to 2 bytes

                toapp.append(find.value());
                toapp.append(QString("\\") + num);

                if (param > 0 && param < 7)
                {
                    uchar param2 = bytes.at(i++);
                    QString num2 = QString::number(param2, 16);
                    if (num2.length() == 1)
                        num2.insert(0, '0');

                    toapp.append(QString("\\") + num2);
                }
            }
            else
            {
                toapp.append(QString("\\h") + QString::number(character, 16));
            }

            output.append(toapp);
        }
        else
        {
            auto find = table.find(character);
            if (find != table.end())
                output.append(find.value());
            else
                output.append(QString("\\h") + QString::number(character, 16));
        }
    }

    return output;
}

QByteArray getstringbytes(const QString &str)
{
    QByteArray output;
    for (int i = 0; i < str.length();)
    {
        QString search;
        char chr = str.at(i++).toLatin1();
        if (chr == '\\')
        {
            search.push_back(chr);

            QChar nx = str.at(i++);
            if (!nx.isDigit())
            {
                search.push_back(nx.toLatin1());
                output.push_back(table.key(search));
            }
            else
            {
                QString num = str.mid(i-1, 2);
                quint32 conv;
                bool succ = false;
                conv = num.toUInt(&succ, 16);

                if (!succ)
                {
                    QMessageBox::warning(NULL, "String", QString("Error while converting string: Invalid byte specifier \\%0.").arg(num));
                    return QByteArray();
                }

                output.push_back((uchar)conv);
            }
        }
        else if (chr == '[')
        {
            // search end of brackets
            int index = str.indexOf(']', i);
            if (index == -1)
            {
                QMessageBox::warning(NULL, "String", QString("Error while converting string: Starting '[' has no ending ']'."));
                return QByteArray();
            }

            int length = index-i+2;
            int pos = i-1;
            i += length-1;

            search = str.mid(pos, length);
            output.push_back(table.key(search));
        }
        else
        {
            output.push_back(table.key(str.at(i-1)));
        }
    }

    return output;
}
