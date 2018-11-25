#ifndef OPENCVVIDEOFRAMESOURCE_H
#define OPENCVVIDEOFRAMESOURCE_H

#include <QObject>
#include <QVideoFrame>

class OpenCVVideoFrameSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString showMovie READ showMovie WRITE setShowMovie)

public:
    explicit OpenCVVideoFrameSource(QObject *parent = nullptr);
    QString showMovie();
    void setShowMovie(const QString &flag);

private:
    QString m_showMovie;
    void doStuff();

signals:
    void newFrameAvailable(const QVideoFrame &frame);


public slots:
};

#endif // OPENCVVIDEOFRAMESOURCE_H
