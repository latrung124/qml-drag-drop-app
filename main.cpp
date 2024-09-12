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

    // Create some images with image provider
    QImage tempImg = imageProvider->drawImageWithText("Temp", QSize(216, 48));
    imageProvider->saveImage(tempImg, "tempSensorImage", "BMP");
    QImage measureTempImg = imageProvider->drawImageWithText("°C", QSize(216, 48));
    imageProvider->saveImage(measureTempImg, "measureTempImage", "BMP");
    QImage sensorValueImg = imageProvider->drawImageWithText("56", QSize(216, 72));
    imageProvider->saveImage(sensorValueImg, "sensorValueImage", "BMP");

    std::unique_ptr<AssignmentItemList> assignmentItemList = std::make_unique<AssignmentItemList>(imageProvider);
    //init test data assignment item
    assignmentItemList->exampleInitialize();

    view1.setSource(QUrl(QStringLiteral("qrc:/HMI/main.qml")));

    if (view1.rootObject())
        view1.rootObject()->setProperty("assignmentItemList", QVariant::fromValue(assignmentItemList.get()));

    view1.show();

    return app.exec();
}
