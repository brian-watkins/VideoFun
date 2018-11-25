#ifndef VIDEOFRAMEPROVIDER_H
#define VIDEOFRAMEPROVIDER_H

#include <QObject>
#include <iostream>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QTDebug>


class VideoFrameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)

public:
    explicit VideoFrameProvider(QObject *parent = nullptr);
    QAbstractVideoSurface* videoSurface() const { return m_surface; }

private:
    QAbstractVideoSurface *m_surface = NULL;
    QVideoSurfaceFormat m_format;

public:
    void setVideoSurface(QAbstractVideoSurface *surface)
        {
            qDebug() << "Set video surface" << surface->supportedPixelFormats();

            if (m_surface && m_surface != surface  && m_surface->isActive()) {
                m_surface->stop();
            }

            m_surface = surface;

            if (m_surface && m_format.isValid())
            {
                qDebug() << "YO valid starting";
                m_format = m_surface->nearestFormat(m_format);
                m_surface->start(m_format);

            } else {
                qDebug() << "Yo INVAILID";
            }
        }

        void setFormat(int width, int heigth)
        {
            QSize size(width, heigth);
            QVideoFrame::PixelFormat pixelFormat = QVideoFrame::Format_RGB32;
            QVideoSurfaceFormat format(size, pixelFormat);
            m_format = format;

            if (m_surface)
            {
                if (m_surface->isActive())
                {
                    m_surface->stop();
                }

                m_format = m_surface->nearestFormat(m_format);

                qDebug() << "Starting with format " << m_format;

                m_surface->start(m_format);
            }
        }

signals:

public slots:
        void onNewVideoContentReceived(const QVideoFrame &frame)
                {
                    qDebug() << "Got a frame!";

                    if (m_surface) {
                        bool result = m_surface->present(frame);
                        qDebug() << "Presented frame: " << result;
                    }
                }
};

#endif // VIDEOFRAMEPROVIDER_H
