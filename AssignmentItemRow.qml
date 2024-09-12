import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import "./" as Example

ListView {
	id: root

	enum ViewMode {
		Unknown,
		Row,
		Column,
		Grid
	}

	property int itemWidth: 90
	property int itemHeight: 90

	property QtObject contentModel: null

	signal moveItem(int from, int to)
	signal pressedAndHold
	signal released

	implicitWidth: 368
	implicitHeight: 110
	orientation: ListView.Horizontal
	layoutDirection: Qt.LeftToRight
	spacing: 6

	displaced: Transition {
		NumberAnimation {
			properties: "x"
			easing.type: Easing.OutQuad
		}
	}

	ScrollBar.horizontal: ScrollBar {
		policy: ScrollBar.AsNeeded
	}

	model: DelegateModel {
		id: delegateModel

		model: root.contentModel

		delegate: DropArea {
			id: dropDelegate

			width: root.itemWidth
			height: root.itemHeight

			property int modelIndex

			onEntered: function (drag) {
				var from = (drag.source as AssignmentMode).visualIndex;
				var to = mode.visualIndex;
				delegateModel.items.move(from, to);
			}

			onDropped: function (drag) {
				var from = modelIndex
				var to = (drag.source as AssignmentMode).visualIndex
				root.contentModel.moveAssignmentItem(from, to);
			}

			property int visualIndex: DelegateModel.itemsIndex

			AssignmentMode {
				id: mode

				dragParent: root
				visualIndex: dropDelegate.visualIndex
				imageSource: model.source

				onPressedAndHold: {
					dropDelegate.modelIndex = visualIndex;
					root.pressedAndHold()
				}
				onReleased: {
					root.released()
				}
			}
		}
	}
}
