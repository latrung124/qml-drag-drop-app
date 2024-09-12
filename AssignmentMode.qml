import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
	id: root

	required property Item dragParent

	property alias imageSource: modeImage.source

	signal pressed
	signal released
	signal clicked
	signal pressedAndHold

	property int visualIndex: 0

	anchors {
		horizontalCenter: parent.horizontalCenter
		verticalCenter: parent.verticalCenter
	}

	radius: 4

	implicitWidth: 90
	implicitHeight: 90
	color: "transparent"

	MouseArea {
		id: mouseArea

		anchors.fill: parent
		drag.target: undefined
		drag.axis: Drag.XAxis
		drag.minimumX: visualIndex * (-width)
		hoverEnabled: true
		cursorShape: Qt.ArrowCursor

		property bool isHeld: false

		onReleased: function() {
			isHeld = false;
			mouseArea.drag.target = undefined;
			parent.Drag.drop();
			root.released();
			cursorShape = Qt.ArrowCursor;
		}

		onPressed: function() {
			root.pressed();
		}

		onPressAndHold: function() {
			cursorShape = Qt.ClosedHandCursor;
			mouseArea.drag.target = root;
			root.pressedAndHold();
			isHeld = true;
		}

		Rectangle {
			id: selectRec

			anchors.fill: parent

			radius: 4
			color: "white"
			visible: false
		}

		Rectangle {
			id: background

			implicitHeight: 86
			implicitWidth: 86

			anchors {
				verticalCenter: parent.verticalCenter
				horizontalCenter: parent.horizontalCenter
			}

			radius: 4
			color: "black"
		}

		Image {
			id: modeImage

			anchors {
				verticalCenter: parent.verticalCenter
				horizontalCenter: parent.horizontalCenter
			}

			sourceSize {
				width: 80
				height: 80
			}

			layer.enabled: true
			layer.effect: OpacityMask {
				maskSource: Item {
					width: modeImage.width
					height: modeImage.height

					Rectangle {
						anchors.centerIn: parent
						width: modeImage.width
						height: modeImage.height
						radius: internal.screenRadius
					}
				}
			}
		}
	}

	Drag.active: mouseArea.drag.active
	Drag.source: root
	Drag.hotSpot.x: root.width / 2

	states: [
		State {
			when: mouseArea.isHeld
			ParentChange {
				target: root
				parent: root.dragParent
			}

			StateChangeScript{
				script: {
					x += internal.dragHoldSpacing;
					y += internal.dragHoldSpacing;
				}
			}

			AnchorChanges {
				target: root
				anchors.horizontalCenter: undefined
				anchors.verticalCenter: undefined
			}
		}
	]

	QtObject {
		id: internal

		property int screenRadius: 4
		property int dragHoldSpacing: 15
	}
}
