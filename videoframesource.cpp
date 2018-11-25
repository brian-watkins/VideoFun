#include "videoframesource.h"
#include <QtDebug>
#include <QThread>
#include <QCoreApplication>

VideoFrameSource::VideoFrameSource(QObject *parent) : QObject(parent)
{

}

#define W 640
#define H 360

unsigned char frameHolder[H][W][4] = {0};


void VideoFrameSource::doStuff() {
    int x, y, count;

    FILE *pipein = popen("/usr/local/bin/ffmpeg -i /Users/bwatkins/work/cstuff/frameProvider/FrameProvider/test.mov -f image2pipe -vcodec rawvideo -pix_fmt rgb32 -", "r");

    // Process video frames
    while(true)
    {
        // Read a frame from the input pipe into the buffer
        count = fread(frameHolder, 1, H*W*4, pipein);

        // If we didn't get a frame of video, we're probably at the end
        if (count != H*W*4) break;

        // Process this frame
        for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x)
        {
            // Invert each colour component in every pixel
            frameHolder[y][x][0] = 255 - frameHolder[y][x][0]; // red
            frameHolder[y][x][1] = 255 - frameHolder[y][x][1]; // green
            frameHolder[y][x][2] = 255 - frameHolder[y][x][2]; // blue
            frameHolder[y][x][3] = 75;
        }


        QImage frameImage((unsigned char *)frameHolder, W, H, QImage::Format_ARGB32);

        QVideoFrame frame(frameImage);

        emit newFrameAvailable(frame);

        QCoreApplication::processEvents();



        QThread::msleep(40);
    }



    fflush(pipein);
    pclose(pipein);
}

QString VideoFrameSource::showMovie() {
    return m_showMovie;
}

void VideoFrameSource::setShowMovie(const QString &showMovie) {
    m_showMovie = showMovie;
    qDebug() << "Should show movie";
    doStuff();
}
