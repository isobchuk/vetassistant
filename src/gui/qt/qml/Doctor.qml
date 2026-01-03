import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    SwipeView {
        id: view
        anchors.fill: parent
        focus: true

        Repeater{
            model: staffModel
            Item {
                implicitWidth: view.width
                implicitHeight: view.height

                Image {
                    id: doctorPic
                    width: 0.48 * parent.width
                    height: 0.92 * parent.height
                    anchors.leftMargin: 0.02 * parent.width
                    anchors.topMargin: 0.04 * parent.height
                    anchors.left: parent.left
                    anchors.top: parent.top
                    source: imagePath
                }

                Text {
                    id: nameStaff
                    text: firstName + " " + lastName
                    font.capitalization: Font.AllUppercase
                    font.bold: true
                    font.pixelSize: 0.10 * parent.height
                    wrapMode: Text.Wrap
                    color: "#003366"
                    anchors {
                        left: doctorPic.right
                        right: parent.right 
                        leftMargin: 0.05 * parent.width
                        topMargin: 0.04 * parent.width
                        top: parent.top
                    }
                }

                Text {
                    id: roleStaff
                    text: role
                    font.bold: true
                    font.pixelSize: 0.05 * parent.height
                    wrapMode: Text.Wrap
                    color: '#003366'
                    anchors {
                        left: doctorPic.right
                        right: parent.right 
                        leftMargin: 0.05 * parent.width
                        topMargin: 0.04 * parent.width
                        top: nameStaff.bottom
                    }
                }

                Text {
                    text: description
                    font.pixelSize: 0.05 * parent.height
                    wrapMode: Text.Wrap
                    color: '#003366'
                    anchors {
                        left: doctorPic.right
                        right: parent.right 
                        leftMargin: 0.05 * parent.width
                        topMargin: 0.04 * parent.width
                        top: roleStaff.bottom
                    }
                }
            }
        }
    }

    Button {
        text: "Zurück"
        width: 0.3 * view.width
        height: 0.16 * view.height
        font.pixelSize: 0.08 * view.height


        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 0.02 * parent.width
            bottomMargin: 0.04 * parent.height
        }
        
        palette.button: "#003366"
        palette.buttonText: "white"
        font.bold: true
        opacity: 0.8

        onClicked: stack.pop()
    }

    PageIndicator {
        id: indicator
 
        count: view.count
        currentIndex: view.currentIndex
 
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

}