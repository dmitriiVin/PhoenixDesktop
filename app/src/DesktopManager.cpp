#include "DesktopManager.hpp"

#include "DesktopItem.hpp"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

DesktopManager::DesktopManager(QObject *parent) : QObject(parent) {
    m_desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    m_watcher.addPath(m_desktopPath);

    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &DesktopManager::refresh);

    loadPositions();
}

QString DesktopManager::desktopPath() const {
    return m_desktopPath;
}

QVariantList DesktopManager::files() const {
    QVariantList result;

    for (DesktopItem *item : m_items) {
        result.append(QVariant::fromValue(item));
    }

    return result;
}

void DesktopManager::setDesktopSize(int width, int height) {
    if (m_desktopWidth == width && m_desktopHeight == height) {
        return;
    }

    m_desktopWidth = width;
    m_desktopHeight = height;

    refresh();
}

void DesktopManager::refresh() {
    QDir dir(m_desktopPath);

    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    /*
     * Удаляем DesktopItem,
     * если файла больше нет.
     */
    for (int i = m_items.size() - 1; i >= 0; --i) {
        DesktopItem *item = m_items.at(i);

        if (!QFileInfo::exists(item->path())) {
            m_items.removeAt(i);
            item->deleteLater();
        }
    }

    /*
     * Добавляем новые файлы.
     */
    for (const QFileInfo &file : files) {
        const QString path = file.absoluteFilePath();

        if (findItem(path))
            continue;

        /*
         * Сначала пытаемся найти
         * сохранённую позицию.
         */
        QPoint position;

        if (m_positions.contains(path)) {
            const QJsonObject saved = m_positions[path].toObject();

            position = QPoint(saved["x"].toInt(), saved["y"].toInt());
        }
        else {
            position = findFreePosition();
        }

        /*
         * Если позиции нет,
         * ищем свободное место.
         */
        if (position.x() < 0 || position.y() < 0) {

            position = findFreePosition();
        }

        auto *item = new DesktopItem(file.fileName(), path, position.x(), position.y(), this);

        m_items.append(item);
    }

    emit filesChanged();

    savePositions();
}

DesktopItem *DesktopManager::findItem(const QString &path) const {
    for (DesktopItem *item : m_items) {
        if (item->path() == path)
            return item;
    }

    return nullptr;
}

QPoint DesktopManager::findFreePosition() const {
    constexpr int startX = 50;
    constexpr int startY = 90;

    constexpr int stepX = 120;
    constexpr int stepY = 120;

    /*
     * Если QML ещё не сообщил
     * размер рабочего стола.
     */
    if (m_desktopWidth <= 0 || m_desktopHeight <= 0) {

        return QPoint(startX, startY);
    }

    for (int y = startY; y + DesktopItem::Height <= m_desktopHeight; y += stepY) {

        for (int x = startX; x + DesktopItem::Width <= m_desktopWidth; x += stepX) {

            bool occupied = false;

            for (DesktopItem *item : m_items) {
                const int left = item->x();

                const int top = item->y();

                const int right = left + DesktopItem::Width;

                const int bottom = top + DesktopItem::Height;

                const bool intersects = x < right && x + DesktopItem::Width > left && y < bottom && y + DesktopItem::Height > top;

                if (intersects) {
                    occupied = true;
                    break;
                }
            }

            if (!occupied)
                return QPoint(x, y);
        }
    }

    /*
     * Если свободного места нет,
     * пока возвращаем начальную позицию.
     *
     * Позже здесь сделаем нормальную
     * обработку переполнения.
     */
    return QPoint(startX, startY);
}

QPoint DesktopManager::clampPosition(const QPoint &position) const {
    if (m_desktopWidth <= 0 || m_desktopHeight <= 0)
        return position;

    const int maxX = qMax(0, m_desktopWidth - DesktopItem::Width);
    const int maxY = qMax(0, m_desktopHeight - DesktopItem::Height);

    return QPoint(qBound(0, position.x(), maxX), qBound(0, position.y(), maxY));
}

void DesktopManager::setItemPosition(const QString &path, int x, int y) {
    DesktopItem *item = findItem(path);

    if (!item)
        return;

    const QPoint position = clampPosition(QPoint(x, y));

    item->setX(position.x());
    item->setY(position.y());

    savePositions();
}

void DesktopManager::loadPositions() {
    const QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    QDir().mkpath(configPath);

    const QString filePath = configPath + "/desktop.json";

    QFile file(filePath);

    if (!file.exists())
        return;

    if (!file.open(QIODevice::ReadOnly))
        return;

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    file.close();

    if (!document.isObject())
        return;

    m_positions = document.object();
}

void DesktopManager::savePositions() {
    const QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    QDir().mkpath(configPath);

    const QString filePath = configPath + "/desktop.json";

    QJsonObject positions;

    for (DesktopItem *item : m_items) {
        QJsonObject position;

        position["x"] = item->x();
        position["y"] = item->y();

        positions[item->path()] = position;
    }

    const QJsonDocument document(positions);

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        return;
    }

    file.write(document.toJson(QJsonDocument::Indented));

    file.close();

    m_positions = positions;
}
