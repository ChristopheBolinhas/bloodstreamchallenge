#include "option.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>

#include <QDebug>

Option::Option()
{
    loadOption();
}

bool Option::loadOption()
{
    QJsonDocument jsonDocument;

    qDebug() << jsonFilename;
    fileOption = new QFile(this->jsonFilename);
    if(fileOption->open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(fileOption);
        QString dataFromJson = fileStream.readAll();
        jsonDocument = QJsonDocument::fromJson(dataFromJson.toUtf8());
        qDebug() << jsonDocument.toJson();

        QJsonObject jobjOption = jsonDocument.object();

        if(jobjOption.value("language").toString() == "french")
            this->language = Option::french;
        else if(jobjOption.value("language").toString() == "english")
            this->language = Option::english;
        else
        {
            qDebug() << "Unsupported language, English has been set";
            this->language = Option::english;
        }

        this->volume = jobjOption.value("volume").toDouble(-1);
        this->mute = jobjOption.value("mute").toBool(false);

        fileOption->close();
        return true;
    }
    else
    {
        fileOption->close();
        qDebug() << "Error: cannot load options !";
        return false;
    }

}

bool Option::saveOption()
{
    QJsonDocument jsonDocument;

    QJsonObject jsonSingleValue;
    jsonSingleValue.insert("fullscreen",QJsonValue(this->isFullscreen()));
    jsonSingleValue.insert("volume",QJsonValue(this->getVolume()));
    jsonSingleValue.insert("mute",QJsonValue(this->isMute()));

    if(this->language==Option::french)
        jsonSingleValue.insert("language",QJsonValue(QString("french")));
    else if(this->getLanguage()==Option::english)
        jsonSingleValue.insert("language",QJsonValue(QString("english")));
    else
        jsonSingleValue.insert("language",QJsonValue(QString("english")));


    jsonDocument.setObject(jsonSingleValue);

    fileOption = new QFile(this->jsonFilename);
    if(fileOption->open(QIODevice::WriteOnly)) // TODO: Ajouter le flag pour dire que l'on efface le fichier avant d'y écrire
    {
        QTextStream fileStream(fileOption);
        fileStream << jsonDocument.toJson();

        fileOption->close();
        return true;
    }
    else
    {
        fileOption->close();
        qDebug() << "Error: cannot save options !";
        return false;
    }
}

bool Option::isFullscreen() const
{
    return fullscreen;
}

void Option::setFullscreen(bool value)
{
    fullscreen = value;
}
bool Option::isMute() const
{
    return mute;
}

void Option::setMute(bool value)
{
    mute = value;
}
int Option::getVolume() const
{
    return volume;
}

bool Option::setVolume(int value)
{
    if(value >= 0 && value <= 100)
    {
        volume = value;
        return true;
    }
    else
        return false;
}
Option::Language Option::getLanguage() const
{
    return language;
}

void Option::setLanguage(const Language &value)
{
    this->language = value;
}
