#include "level.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>

Level::Level(QString name, int score, QString path, int ordre)
{
    this->setName(name);
    this->setScore(score);
    this->pathJson = path+"/level.json";
    qDebug() << path;
    this->setPathTileSet(path+"/tileset.png");
    this->setOrder(ordre);

    // détermine si le niveau est bloqué ou pas
    //TODO: faire une exception pour le niveau 1 (score a 0 mais pas locked)
    this->getScore()== 0 ? this->locked=true : this->locked=false;
    this->parseJsonLevel();
}

QList<Level> Level::loadLevels()
{
    QList<Level> listLevels;
    //TODO: changer le nom du chemin$

    const QString LEVELS_FILENAME = QApplication::applicationDirPath() + "/ressources/levels.json"; //TODO: trouver une solution pour récupérer ce nom en relatif
    QJsonDocument jsonLevels;

    //Lecture du fichier levels.json
    QFile *fileLevel = new QFile(LEVELS_FILENAME);
    if(fileLevel->open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(fileLevel);
        QString dataFromJson = fileStream.readAll();
        jsonLevels = QJsonDocument::fromJson(dataFromJson.toUtf8());
        qDebug() << jsonLevels.toJson();
        fileLevel->close();
    }
    else
    {
        fileLevel->close();
        qDebug() << "Error: cannot load options !" << LEVELS_FILENAME;
        //return NULL;
    }

    QJsonObject jObject = jsonLevels.object();
    QString levelsPath =  jObject.value("levelspath").toString();
    QJsonArray jArrayLevels = jObject.value("levels").toArray();
    int numberOfLevels = jArrayLevels.size();

    for(int i = 0; i < numberOfLevels; i++)
    {
        QJsonObject jLevel = jArrayLevels.at(i).toObject();
         qDebug() << jLevel.value("name").toString() <<  jLevel.value("score").toDouble() << QApplication::applicationDirPath()+"/"+levelsPath+jLevel.value("path").toString() << (int)jLevel.value("order").toDouble();
        Level lvl(jLevel.value("name").toString(), jLevel.value("score").toDouble(),QApplication::applicationDirPath()+"/"+levelsPath+jLevel.value("path").toString(),(int)jLevel.value("order").toDouble());
        listLevels.append(lvl);
    }

    return listLevels;
}

bool Level::parseJsonLevel()
{
    //Lecture du fichier JSON généré par Tiled
    QJsonDocument jsonLevelTiled;
    //QString levelNumber = this->getName().replace(0,7,"level"); // "Niveau 1" --> "level1"
    //QString levelFilename = QString(levelPath+levelNumber+"/level.json");
    //qDebug() << levelFilename;

    //QFile *fileLevel = new QFile(levelFilename);
    QFile *fileLevel = new QFile(this->pathJson);
    qDebug() << pathJson;
    if(fileLevel->open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(fileLevel);
        QString dataFromJson;
        while(!fileStream.atEnd())
        {
            dataFromJson.append(fileStream.readLine());
        }
        //qDebug() << dataFromJson;
        jsonLevelTiled = QJsonDocument::fromJson(dataFromJson.toUtf8());
        fileLevel->close();
    }
    else
    {
        fileLevel->close();
        qDebug() << "Error: cannot load level !";
        return false;
    }

    // Affectation des propriétés du niveau à l'instance Level
    mapBackground = parseJsonLayer("Background", jsonLevelTiled);
    mapForeground = parseJsonLayer("Foreground", jsonLevelTiled);
    //TODO: transformer les 384,381,... (numeros utilisés pour les flèches) en numero de déplacement [1-9]\5
    mapRoad = parseJsonLayer("Road", jsonLevelTiled);
    mapObstacle = parseJsonLayer("Obstacle", jsonLevelTiled);
    mapDecors = parseJsonLayer("Decor",jsonLevelTiled);
    mapAnimation = parseJsonLayer("Animation",jsonLevelTiled);
    this->mapWidth = jsonLevelTiled.object().value("width").toDouble();
    this->mapHeight = jsonLevelTiled.object().value("height").toDouble();
    //qDebug() << "map width: " << this->mapWidth << "map height: " << this->mapHeight;

    parseJsonTileSet(jsonLevelTiled);

    return true;
}

int* Level::parseJsonLayer(QString layerName, const QJsonDocument &jsonDocument)
{
    QJsonObject jObj = jsonDocument.object(); // jObj utilisé comme outil, son contenu n'est pas fiable
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
    //qDebug() << tmpShowData;
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

    //parseFleches(jTileSet);
    //qDebug() << "w: " << tileSetWidth << " h: " << tileSetHeight << "lala: " << tileWidth << "lolo: " << tileHeight;
}

void Level::parseFleches(/*QJsonObject jTileSet*/)
{
    /*
    QJsonObject jObj = jTileSet.value("tileproperties").Object;
    foreach (QString key, jObj.keys()) {
        jObj.value(keys);
    }
    */

    /* C'est pas la peine de les récupérer dynamiquement dans le JSON
     * et donc d'utiliser les propriétés dans Tiled. Par contre,
     * en cas de changement c'est la seule place où faut les changer et
     * c'est l'endroit le plus approprié, en tout cas plus que dans Render.
    */
    FLECHE_ROAD_1 = 385;
    FLECHE_ROAD_2 = 384;
    FLECHE_ROAD_3 = 386;
    FLECHE_ROAD_4 = 382;
    FLECHE_ROAD_6 = 381;
    FLECHE_ROAD_7 = 387;
    FLECHE_ROAD_8 = 383;
    FLECHE_ROAD_9 = 388;

    FLECHE_OBSTACLE_1 = 393;
    FLECHE_OBSTACLE_2 = 392;
    FLECHE_OBSTACLE_3 = 394;
    FLECHE_OBSTACLE_4 = 390;
    FLECHE_OBSTACLE_6 = 389;
    FLECHE_OBSTACLE_7 = 395;
    FLECHE_OBSTACLE_8 = 391;
    FLECHE_OBSTACLE_9 = 396;
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

QString Level::getPath() const
{
    return pathTileSet;
}

void Level::setPath(const QString &value)
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
