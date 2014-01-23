#include "level.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>

Level::Level(QString name, int score, QString path, int ordre, int unite, QString levelsPath)
{
    this->setName(name);
    this->setScore(score);
    this->nbUnite = unite;
    this->path = path;
    this->pathJson = QApplication::applicationDirPath()+"/"+levelsPath+path+"/level.json";
    this->setPathTileSet(QApplication::applicationDirPath()+"/"+levelsPath+path+"/tileset.png");
    this->setOrder(ordre);

    // détermine si le niveau est bloqué ou pas
    this->getScore()== 0 ? this->locked=true : this->locked=false;
    this->parseJsonLevel();
}

QList<Level*>* Level::loadLevels()
{
    QList<Level*> *listLevels = new QList<Level*>();

    const QString LEVELS_FILENAME = QApplication::applicationDirPath() + "/ressources/levels.json";

    QJsonDocument jsonLevels;

    //Lecture du fichier levels.json
    QFile *fileLevel = new QFile(LEVELS_FILENAME);
    if(fileLevel->open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(fileLevel);
        QString dataFromJson = fileStream.readAll();
        jsonLevels = QJsonDocument::fromJson(dataFromJson.toUtf8());
        fileLevel->close();
    }
    else
    {
        fileLevel->close();
    }

    QJsonObject jObject = jsonLevels.object();
    QString levelsPath =  jObject.value("levelspath").toString();
    QJsonArray jArrayLevels = jObject.value("levels").toArray();
    int numberOfLevels = jArrayLevels.size();
    for(int i = 0; i < numberOfLevels; i++)
    {
        QJsonObject jLevel = jArrayLevels.at(i).toObject();
        Level *lvl = new Level(jLevel.value("name").toString(), jLevel.value("score").toDouble(),jLevel.value("path").toString(),(int)jLevel.value("order").toDouble(), (int)jLevel.value("unite").toDouble() ,levelsPath);
        listLevels->append(lvl);
    }
    return listLevels;
}

bool Level::saveLevels(QList<Level *> listLevels)
{
    const QString LEVELS_FILENAME = QApplication::applicationDirPath() + "/ressources/levels.json";


    QJsonDocument jsonLevels;
    QJsonObject jObj;
    jObj.insert("levelspath", QJsonValue(QString("/ressources/levels/")));

    jsonLevels.setObject(jObj);

    QJsonArray jArr;
    foreach (Level *lvl, listLevels) {
        QJsonObject jObjInArray;
        jObjInArray.insert("name", QJsonValue(QString(lvl->getName())));
        jObjInArray.insert("score", QJsonValue(lvl->getScore()));
        jObjInArray.insert("path", QJsonValue(QString(lvl->getPath())));
        jObjInArray.insert("order", QJsonValue(lvl->getOrder()));
        jObjInArray.insert("unite", QJsonValue(lvl->getNbUnite()));

        jArr.append(jObjInArray);
        jObj.insert("levels", QJsonValue(jArr));
    }
    jsonLevels.setObject(jObj);

    //Lecture du fichier levels.json
    QFile *fileLevel = new QFile(LEVELS_FILENAME);
    if(fileLevel->open(QIODevice::WriteOnly))
    {QTextStream fileStream(fileLevel);
        fileStream << jsonLevels.toJson();
        fileLevel->close();
        return true;
    }
    else
    {
        fileLevel->close();
        return false;
    }
}

bool Level::parseJsonLevel()
{
    //Lecture du fichier JSON généré par Tiled
    QJsonDocument jsonLevelTiled;

    QFile *fileLevel = new QFile(this->pathJson);
    if(fileLevel->open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(fileLevel);
        QString dataFromJson;
        while(!fileStream.atEnd())
        {
            dataFromJson.append(fileStream.readLine());
        }
        jsonLevelTiled = QJsonDocument::fromJson(dataFromJson.toUtf8());
        fileLevel->close();
    }
    else
    {
        return false;
    }

    // Affectation des propriétés du niveau à l'instance Level
    mapBackground = parseJsonLayer("Background", jsonLevelTiled);
    mapForeground = parseJsonLayer("Foreground", jsonLevelTiled);
    mapRoad = parseJsonLayer("Road", jsonLevelTiled);
    mapObstacle = parseJsonLayer("Obstacle", jsonLevelTiled);
    mapDecors = parseJsonLayer("Decor",jsonLevelTiled);
    mapAnimation = parseJsonLayer("Animation",jsonLevelTiled);
    this->mapWidth = jsonLevelTiled.object().value("width").toDouble();
    this->mapHeight = jsonLevelTiled.object().value("height").toDouble();

    parseJsonTileSet(jsonLevelTiled);

    return true;
}

int* Level::parseJsonLayer(QString layerName, const QJsonDocument &jsonDocument)
{
    QJsonObject jObj = jsonDocument.object();
    QJsonArray jLayers = jObj.value("layers").toArray();

    int *data;

    int layerNumber = -1;
    for(int i=0; i < jLayers.size(); i++)
    {
        jObj = jLayers.at(i).toObject();
        if(jObj.value("name").toString() == layerName)
        {
            layerNumber = i;
            break;
        }
    }
    Q_ASSERT(layerNumber >= 0); // Le layer doit exister

    jObj = jLayers.at(layerNumber).toObject();
    QList<QVariant> list = jObj.value("data").toArray().toVariantList();

    QString tmpShowData;
    data = new int[list.size()];
    for(int i=0; i < list.size(); i++)
    {
        data[i] = list.at(i).toInt();
        tmpShowData.append(QString::number(data[i])+" ");
    }
    return data;

}

void Level::parseJsonTileSet(QJsonDocument jsonDocument)
{
    QJsonObject jObj = jsonDocument.object();
    QJsonObject jTileSet = jObj.value("tilesets").toArray().at(0).toObject();

    this->tileSetWidth = jTileSet.value("imagewidth").toDouble();
    this->tileSetHeight = jTileSet.value("imageheight").toDouble();
    this->tileWidth = jTileSet.value("tilewidth").toDouble();
    this->tileHeight = jTileSet.value("tileheight").toDouble();
}

/*
 * GETTERS AND SETTERS
 */
QString Level::getName() const
{
    return name;
}

void Level::setName(const QString &value)
{
    name = value;
}

int Level::getScore() const
{
    return score;
}

void Level::setScore(int value)
{
    score = value;
}

bool Level::isLocked() const
{
    return locked;
}

int *Level::getMapBackground() const
{
    return mapBackground;
}

int *Level::getMapForeground() const
{
    return mapForeground;
}

int *Level::getMapRoad() const
{
    return mapRoad;
}

int *Level::getMapObstacle() const
{
    return mapObstacle;
}

int *Level::getMapDecors() const
{
    return mapDecors;
}

int *Level::getMapAnimation() const
{
    return mapAnimation;
}

int Level::getTileSetWidth() const
{
    return tileSetWidth;
}

int Level::getTileSetHeight() const
{
    return tileSetHeight;
}

int Level::getTileWidth() const
{
    return tileWidth;
}

int Level::getTileHeight() const
{
    return tileHeight;
}

int Level::getMapWidth() const
{
    return mapWidth;
}

int Level::getMapHeight() const
{
    return mapHeight;
}

QString Level::getPathJson() const
{
    return pathTileSet;
}

void Level::setPathJson(const QString &value)
{
    pathTileSet = value;
}

int Level::getOrder() const
{
    return order;
}

void Level::setOrder(int value)
{
    order = value;
}

QString Level::getPathTileSet() const
{
    return pathTileSet;
}

void Level::setPathTileSet(const QString &value)
{
    pathTileSet = value;
}

QString Level::getPath() const
{
    return path;
}

int Level::getNbUnite() const
{
    return nbUnite;
}

void Level::setNbUnite(int value)
{
    nbUnite = value;
}
