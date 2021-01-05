import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import org.kde.mauikit 1.0 as Maui
import org.kde.kirigami 2.7 as Kirigami
import org.maui.index 1.0 as Index

Maui.Page
{
    id: control
    headBar.visible: false
    footBar.visible: true
    footerBackground.color: "transparent"
    footBar.rightContent: Button
    {
        text: i18n("Extract")
        onClicked:
        {
            dialogLoader.sourceComponent= _extractDialogComponent
            dialog.open()
            _compressedFile.extract(browser.currentPath, dialogLoader.textEntry.text)
        }
    }

    Component.onCompleted:
    {
        _compressedFile.url = currentUrl
    }

    Maui.ListBrowser
    {
        id: _listView
        anchors.fill: parent
        model: Maui.BaseModel
        {
            list: _compressedFile.model
        }

        margins: Maui.Style.space.medium

        delegate: Maui.ItemDelegate
        {
            height: Maui.Style.rowHeight* 1.5
            width: ListView.view.width

            Maui.ListItemTemplate
            {
                anchors.fill: parent
                iconSource: model.icon
                iconSizeHint: Maui.Style.iconSizes.medium
                label1.text: model.label
                label2.text: model.date
            }
        }
    }
}
