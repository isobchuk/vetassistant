import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 1024
    height: 600
    title: "Tierarzthelfer"
    color: "white"

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: initialPage
    }

    Component {
        id: initialPage

        Item {
            Text {
                text: "Tierarzthelfer"
                anchors.centerIn: parent
                font.capitalization: Font.AllUppercase
                font.bold: true
                font.pixelSize: 72
                wrapMode: Text.Wrap
                color: "#003366"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    stack.push(mainPage)
                }
            }
        }
    }

    Component {
        id: mainPage

         Item {
            anchors.fill: parent

            ListModel {
                id: menuModel
                ListElement { text: "Fragen" }
                ListElement { text: "Zeitplan" }
                ListElement { text: "Leistungen" }
                ListElement { text: "Unsereteam" }
                ListElement { text: "Zurück" }
            }

            ListView {
                //anchors.centerIn: parent
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 50      // ← space from the top
                anchors.bottomMargin: 50      // ← space from the top
                width: 800
                height: 600
                model: menuModel
                layoutDirection: Qt.LeftToRight  // default
                spacing: 20
                delegate: Button {
                    width: 800
                    height: 200
                    text: model.text
                    font.pixelSize: 48
                    font.bold: true
                    palette.buttonText: "white" 
                    
                    background: Rectangle {
                        color: "#003366"
                        radius: 12
                    }

                    onClicked: {
                        if (text === "Fragen") stack.push(fragenPage)
                        else if (text === "Zeitplan") stack.push(zeitplanPage)
                        else if (text === "Zurück") stack.pop()
                    }
                }
            }
        }       
    }

    ListModel {
        id: faqModel

        ListElement { question: "Was sind Ihre Öffnungszeiten?"; answer: "Wir haben von Montag bis Freitag von 8:00 bis 18:00 Uhr geöffnet." }
        ListElement { question: "Bieten Sie Notdienste an?"; answer: "Ja, wir bieten einen 24/7-Notdienst an." }
        ListElement { question: "Wo befindet sich die Klinik?"; answer: "Unsere Adresse ist Hauptstraße 123, Stadtname." }
        ListElement { question: "Muss ich einen Termin vereinbaren?"; answer: "Wir empfehlen, einen Termin zu vereinbaren, aber für Notfälle sind wir auch ohne Termin da." }
        ListElement { question: "Welche Leistungen bieten Sie an?"; answer: "Wir bieten Vorsorgeuntersuchungen, Impfungen, Operationen und Beratung an." }
        ListElement { question: "Akzeptieren Sie neue Patienten?"; answer: "Ja, wir nehmen jederzeit neue Patienten auf." }
        ListElement { question: "Wie kann ich einen Termin buchen?"; answer: "Sie können telefonisch, per E-Mail oder über unsere Website einen Termin buchen." }
        ListElement { question: "Welche Zahlungsmethoden werden akzeptiert?"; answer: "Wir akzeptieren Barzahlung, EC- und Kreditkarten." }
        ListElement { question: "Gibt es Parkmöglichkeiten vor der Klinik?"; answer: "Ja, es gibt kostenfreie Parkplätze direkt vor der Klinik." }
        ListElement { question: "Kann ich Medikamente für mein Haustier bei Ihnen abholen?"; answer: "Ja, wir haben eine kleine Apotheke vor Ort." }
        ListElement { question: "Bieten Sie Hausbesuche an?"; answer: "Hausbesuche sind nach Absprache möglich, insbesondere für ältere oder kranke Tiere." }
        ListElement { question: "Wie kann ich Sie in einem Notfall erreichen?"; answer: "Rufen Sie unsere Notfallnummer an: 0123-456789, wir sind jederzeit erreichbar." }
    }

    Component {
        id: fragenPage

        Item {
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                color: "white"
            }

            Flickable {
                anchors.fill: parent
                contentHeight: column.implicitHeight
                clip: true

                Column {
                    id: column
                    width: parent.width
                    spacing: 20
                    padding: 50

                    Repeater {
                        model: faqModel
                        delegate: Item {
                            width: parent.width - 100
                            property bool expanded: false

                            Column {
                                id: contentColumn
                                width: parent.width
                                spacing: 10

                                // Question area
                                Rectangle {
                                    width: parent.width
                                    color: "transparent"
                                    height: questionText.implicitHeight


                                    Text {
                                        id: questionText
                                        text: model.question
                                        font.pixelSize: 32
                                        font.bold: true
                                        color: "#003366"
                                        width: parent.width - 20
                                        wrapMode: Text.Wrap
                                    }
                                }

                                // Answer area
                                Text {
                                    id: answerText
                                    text: model.answer
                                    font.pixelSize: 32
                                    width: parent.width - 20
                                    color: "#003366"
                                    wrapMode: Text.Wrap
                                    visible: expanded
                                }
                            }

                            // Rectangle background
                            Rectangle {
                                anchors.fill: contentColumn
                                color: "#f5f5f5"
                                radius: 12
                                border.color: "#cccccc"
                                border.width: 1
                                z: -1


                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        expanded = !expanded
                                    }
                                }
                            }

                            // Bind height of delegate to content
                            height: contentColumn.implicitHeight + 20
                        }
                    }
                }
            }

            Button {
                text: "Zurück"
                width: 200
                height: 60
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 20
                font.pixelSize: 20
                
                palette.button: "#003366"       // background color
                palette.buttonText: "white"     // text color
                font.bold: true
                opacity: 0.8

                onClicked: stack.pop()
            }
        }
    }



    Component {
        id: zeitplanPage
        
        Item {

            Button {
                text: "Zurück"
                width: 200
                height: 60
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 20
                font.pixelSize: 20
                
                palette.button: "#003366"       // background color
                palette.buttonText: "white"     // text color
                font.bold: true
                opacity: 0.8

                onClicked: stack.pop()
            }
        }
    }

    
}