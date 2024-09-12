#include "ImageProvider.h"

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    // Generate a simple image (red square)
    m_pixmaps.append(drawASensorPixmap("Battery", "55", "%"));
    m_pixmaps.append(drawASensorPixmap("Load", "45", "%"));
    m_pixmaps.append(drawASensorPixmap("Package", "65", "°C"));
    m_pixmaps.append(drawASensorPixmap("RPM", "1000", "°C"));
    m_pixmaps.append(drawASensorPixmap("CPU", "30", "°C"));
    m_pixmaps.append(drawASensorPixmap("GPU", "5", "%"));
    m_pixmaps.append(drawASensorPixmap("Package", "40", "°C"));
}

ImageProvider::~ImageProvider()
{
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int hyphenIndex = id.indexOf('-');
    auto screenModeId = id.mid(hyphenIndex + 1);

    if (auto temp = screenModeId.toInt(); temp >= 0 && temp < m_pixmaps.size()) {
        return m_pixmaps.at(temp);
    }

    return QPixmap();
}

QPixmap ImageProvider::drawASensorPixmap( QString name, QString number, QString measurement)
{
    int width = 240;
    int height = 240;

    QPixmap pixmap(width, height);
    pixmap.fill(QColor("transparent").rgba());

    QPainter painter(&pixmap);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::transparent);

    // Draw the rounded rectangle
    QRect rect(0, 0, 240, 240);
    painter.drawRect(rect);

    // Set the font and alignment for the text
    QFont font("Open Sans");
    font.setPixelSize(36);
    painter.setFont(font);
    painter.setPen(Qt::white);

    // Calculate the rectangle for the text, with a 25px margin from the top
    QRect topTextRect(0, 36, 216, 48);

    // Draw the text centered within the rectangle
    painter.drawText(topTextRect, Qt::AlignCenter, name);


    // Calculate the rectangle for the measurement text, with a 25px margin from the top
    QRect meaTextRect(0, 168, 216, 48);

    // Draw the text centered within the rectangle
    painter.drawText(meaTextRect, Qt::AlignCenter, measurement);

    font.setPixelSize(72);
    font.setBold(true);
    painter.setFont(font);

    // Calculate the rectangle for the text, with a 25px margin from the top
    QRect centerTextRect(0, 96, 216, 72);

    // Draw the text centered within the rectangle
    painter.drawText(centerTextRect, Qt::AlignCenter, number);


    // End the painter (optional but good practice)
    painter.end();

    return pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QImage ImageProvider::drawImageWithText(const QString &text, const QSize &size)
{
    QPixmap pixmap(size);
    pixmap.fill(QColor("transparent").rgba());

    QPainter painter(&pixmap);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::transparent);

    // Draw the rounded rectangle
    QRect rect(0, 0, size.width(), size.height());
    painter.drawRect(rect);

    // Set the font and alignment for the text
    QFont font("Open Sans");
    font.setPixelSize(36);
    painter.setFont(font);
    painter.setPen(Qt::white);

    // Calculate the rectangle for the text, with a 25px margin from the top
    QRect textRect(0, 0, size.width(), size.height());

    // Draw the text centered within the rectangle
    painter.drawText(textRect, Qt::AlignCenter, text);

    // End the painter (optional but good practice)
    painter.end();

    return pixmap.toImage().convertToFormat(QImage::Format_RGB16);
}

bool ImageProvider::saveImage(const QImage &image, const QString &fileName, const QString &format)
{
    QString filePath = fileName + "." + format;
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    return image.save(&file, format.toStdString().c_str());
}

void ImageProvider::getImages(QVector<QPixmap> &images) const
{
    images = m_pixmaps;
}

void ImageProvider::appendImage(const QPixmap& _image)
{
    m_pixmaps.append(_image);
}

void ImageProvider::removeImage()
{
}
