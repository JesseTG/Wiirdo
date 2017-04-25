import QtQuick 2.4

import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import wii 1.0

Item {

    Wii {
        id: wii
    }

    id: item1
    width: 400
    height: 400

    TabView {
        height: 400
        width: 603
        Tab {
            id: tab
            source: "WindowsMenu.qml"
            title: "Windows"
        }
        Tab {
            source: "MediaPlayer.qml"
            title: "Media Player"
        }
    }
}
