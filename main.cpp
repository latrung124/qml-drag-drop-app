#include <QCoreApplication>
#include <QGuiApplication>
#include <QString>
#include <QUrl>
#include <QtQuick>

#include "backend_component/ImageProvider.h"
#include "backend_component/AssignmentItemList.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view1;

    std::shared_ptr<ImageProvider> imageProvider = std::make_shared<ImageProvider>();

    if (auto engine = view1.engine(); engine) {
        engine->addImageProvider(QLatin1String("screen_module"), imageProvider.get());
    }

    std::unique_ptr<AssignmentItemList> assignmentItemList = std::make_unique<AssignmentItemList>(imageProvider);
    //init test data assignment item
    assignmentItemList->exampleInitialize();

    view1.setSource(QUrl(QStringLiteral("qrc:/HMI/main.qml")));

    if (view1.rootObject())
        view1.rootObject()->setProperty("assignmentItemList", QVariant::fromValue(assignmentItemList.get()));

    view1.show();

    return app.exec();
}
