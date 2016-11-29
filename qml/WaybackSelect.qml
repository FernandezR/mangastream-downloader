import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.0

ApplicationWindow {
    property var wayback
    property int marginSize
    property string url

    id: root

    width: 640
    minimumWidth: 640
    maximumWidth: 640

    height: 260
    minimumHeight: 260
    maximumHeight: 260

    title: qsTr("Select previous version")

    ListModel {
        id: lmodel
    }

    Label {
        id: chooselabel
        text: qsTr("Choose date to set:")
        x: marginSize
        y: marginSize
        font.pixelSize: 25
    }

    ComboBox {
        model: lmodel
        textRole: "date"
        x: chooselabel.x + chooselabel.width + marginSize
        y: marginSize + 5
        width: 250
        onCurrentIndexChanged: {
            url = lmodel.get(currentIndex).url;
        }
    }

    Button {
        id: confirmButton
        width: 120
        height: 60
        text: qsTr("Confirm")
        anchors.centerIn: parent
        onClicked: {
            root.visible = false;
            wayback.selectedUrl = url;
            root.close();
        }
    }

    Component.onCompleted: {
        var date;
        var url;
        lmodel.append({url: "", date: "---"});
        for(var i in wayback.listOfMementos) {
            if(i % 2 == 0) {
                date = wayback.listOfMementos[i];
            } else {
                url = wayback.listOfMementos[i];
                lmodel.append({url: url, date: date});
            }
        }
    }
}
