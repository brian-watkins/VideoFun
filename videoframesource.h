#ifndef VIDEOFRAMESOURCE_H
#define VIDEOFRAMESOURCE_H

#include <QObject>
#include <QVideoFrame>

class VideoFrameSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString showMovie READ showMovie WRITE setShowMovie)

public:
    explicit VideoFrameSource(QObject *parent = nullptr);
    int width;
    int height;
    QString showMovie();
    void setShowMovie(const QString &flag);

private:
    QString m_showMovie;
    void doStuff();


signals:
    void newFrameAvailable(const QVideoFrame &frame);

public slots:
};

#endif // VIDEOFRAMESOURCE_H
