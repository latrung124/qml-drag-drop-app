#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QPixmap>
#include <QFile>
#include <QImage>
#include <QQuickImageProvider>
#include <QPainter>

namespace ImageProviderConstants
{
    static const std::string IMAGE_PROVIDER_PATH = "image://screen_module/screenmode-";
}

class ImageProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    ImageProvider();
    ~ImageProvider() override;

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

    QPixmap drawASensorPixmap(QString name, QString number, QString measurement);

    void getImages(QVector<QPixmap> &images) const;

    QImage drawImageWithText(const QString &text, const QSize &size);
    bool saveImage(const QImage &image, const QString &fileName, const QString &format);

public slots:
    void appendImage(const QPixmap &_image);
    void removeImage();

private:
    QVector<QPixmap> m_pixmaps;

};
#endif // IMAGEPROVIDER_H
