#include "opencvvideoframesource.h"
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <QtDebug>
#include <QCoreApplication>
#include <QThread>

using namespace cv;

OpenCVVideoFrameSource::OpenCVVideoFrameSource(QObject *parent) : QObject(parent)
{

}

#define W 640
#define H 360


void OpenCVVideoFrameSource::doStuff() {
    VideoCapture cap("/Users/bwatkins/work/cstuff/frameProvider/FrameProvider/test.mov");

    if(!cap.isOpened())  // check if we succeeded
         qDebug() << "Error opening file!";

    Mat edges;
    for(;;)
    {
        Mat frame;

        if (!cap.read(frame)) {
            qDebug() << "Done with frames!";
            break;
        }

        cvtColor(frame, edges, COLOR_BGR2BGRA);
        medianBlur(edges, edges, 7);
//        GaussianBlur(edges, edges, Size(7,7), 3.5, 3.5);

        QImage frameImage(edges.data, W, H, QImage::Format_ARGB32);

        QVideoFrame videoFrame(frameImage);

        emit newFrameAvailable(videoFrame);

        QCoreApplication::processEvents();

        QThread::msleep(40);
    }
}

QString OpenCVVideoFrameSource::showMovie() {
    return m_showMovie;
}

void OpenCVVideoFrameSource::setShowMovie(const QString &showMovie) {
    m_showMovie = showMovie;
    qDebug() << "Should show open cv movie";
    doStuff();
}
