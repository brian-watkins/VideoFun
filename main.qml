import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.11
import com.fun.VideoFrameProvider 1.0
import com.fun.VideoFrameSource 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "red"

        VideoFrameProvider{
            objectName: "provider"
            id: provider
        }

        VideoFrameSource {
            id: source
            objectName: "source"
        }

        VideoOutput {
            id: display
            objectName: "display"
            width: 640
            height: 320
            anchors.centerIn: parent
            source: provider

            MouseArea {
                anchors.fill: parent
                onClicked: source.showMovie = "true"
            }
        }

}
