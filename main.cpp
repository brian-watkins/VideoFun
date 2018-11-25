#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "videoframeprovider.h"
#include "videoframesource.h"
#include "opencvvideoframesource.h"
#include <QTDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<VideoFrameProvider>("com.fun.VideoFrameProvider", 1, 0, "VideoFrameProvider");
//    qmlRegisterType<VideoFrameSource>("com.fun.VideoFrameSource", 1, 0, "VideoFrameSource");
    qmlRegisterType<OpenCVVideoFrameSource>("com.fun.VideoFrameSource", 1, 0, "VideoFrameSource");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // find your custom control
    QObject *rootObject = engine.rootObjects().first();
    QObject *display = rootObject->findChild<QObject *>("display");
    auto provider = qvariant_cast<VideoFrameProvider *>(display->property("source"));

    // create your custom frame source. This source is expected to have the following public fields and signals:
    // - int width
    // - int height
    // - int format (following QVideoFrame::PixelFormat)
    // - signals: void newFrameAvailable(const QVideoFrame &frame);
    //        VideoFrameSource source;
//    VideoFrameSource *source = rootObject->findChild<VideoFrameSource *>("source");
    OpenCVVideoFrameSource *source = rootObject->findChild<OpenCVVideoFrameSource *>("source");

    // Set the correct format for the video surface (Make sure your selected format is supported by the surface)
    provider->setFormat(640, 480);

    // Connect your frame source with the provider
    QObject::connect(source, SIGNAL(newFrameAvailable(const QVideoFrame &)), provider, SLOT(onNewVideoContentReceived(const QVideoFrame &)));


    qDebug() << "before exec";

    return app.exec();
}
