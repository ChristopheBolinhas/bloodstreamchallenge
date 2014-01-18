/**
  Utilisation:
  - charger les niveaux: Level::loadLevels(); --> List<Level>
  - Pour connaitre la correspondance des flèches dans le
    tableau int du layer obstacles et de road, il y a
    les int FLECHE_ROAD_X et FLECHE_OBSTACLE_X où X est une valeur
    de 1 à 9 correspondant au cadran de déaplacement.
  */

#ifndef LEVEL_H
#define LEVEL_H

#include <QApplication>

class Level
{
public:
    Level(QString name, int score, QString pathJson, int ordre, int unite, QString levelsPath);

    QString getName() const;
    void setName(const QString &value);
    int getScore() const;
    void setScore(int value);
    bool isLocked() const;

    QString getPath() const;
    void setPathJson(const QString &value);
    int getOrder() const;
    void setOrder(int value);
    QString getPathTileSet() const;
    int getNbUnite() const;
    void setNbUnite(int value);
    void setPathTileSet(const QString &value);

    int *getMapBackground() const;
    int *getMapForeground() const;
    int *getMapRoad() const;
    int *getMapObstacle() const;
    int *getMapDecors() const;
    int *getMapAnimation() const;
    int getTileSetWidth() const;
    int getTileSetHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;
    int getMapWidth() const;
    int getMapHeight() const;

    static QList<Level *> loadLevels();
	static bool saveLevels(QList<Level *> listLevels);


private:
    //Attributs pour la liste des  niveaux
    QString name;
    int score;
	QString path;
    QString pathJson;
    int order;
    bool locked;
	int nbUnite;
    QString pathTileSet;

    //Attributs pour le json généré par Tiled
    int *mapBackground;
    int *mapForeground;
    int *mapRoad;
    int *mapObstacle;
    int *mapDecors;
    int *mapAnimation;

    int mapWidth;
    int mapHeight;

    int tileSetWidth;
    int tileSetHeight;
    int tileWidth;
    int tileHeight;

    // Fonctions à usage interne
	QString getPathJson() const;
    bool parseJsonLevel();
    int *parseJsonLayer(QString layerName, const QJsonDocument &jsonDocument);
    void parseJsonTileSet(QJsonDocument jsonDocument);
    void parseFleches();
};

#endif // LEVEL_H
