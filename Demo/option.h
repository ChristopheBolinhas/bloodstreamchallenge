#ifndef OPTION_H
#define OPTION_H

#include <QApplication>

class QFile;
class Option
{
public:
    Option();
    bool loadOption();
    bool saveOption();

    bool isFullscreen() const;
    void setFullscreen(bool value);

    bool isMute() const;
    void setMute(bool value);

    int getVolume() const;
    bool setVolume(int value);

    enum Language {french, english};
    Language getLanguage() const;
    void setLanguage(const Language &value);

private:
    int volume;
    bool mute;
    bool fullscreen;
    QFile *fileOption;
    Language language;

    const QString jsonFilename = QApplication::applicationDirPath() + "/options.json";
};

#endif // OPTION_H
