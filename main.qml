import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {
	id: mainView
    visible: true
    width: 1080
    height: 480

	property QtObject assignmentItemList: null

	Rectangle {
		id: contentRec
		anchors.fill: parent

		color: "transparent"
		MouseArea {
			id: contentMouseArea

			anchors.fill: parent

			cursorShape: Qt.ArrowCursor

			Item {
				id: rowItem
				anchors {
					verticalCenter: parent.verticalCenter
					left: parent.left
					leftMargin: 15
					right: parent.right
					rightMargin: 15
				}

				width: parent.width
				height: 110
				clip: true

				Rectangle {
					anchors.fill: parent
					border.color: "red"
				}

				AssignmentItemRow {
					id: assignmentItemRow

					anchors.fill: parent

					contentModel: assignmentItemList
					visible: true
					onPressedAndHold: {
						console.log("AssignmentItemRow onPressAndHold");
						contentMouseArea.cursorShape = Qt.ClosedHandCursor
					}

					onReleased: {
						console.log("AssignmentItemRow onReleased");
						contentMouseArea.cursorShape = Qt.ArrowCursor
					}
				}
			}
		}
	}
}

