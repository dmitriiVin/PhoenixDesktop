#pragma once

#include <QFileSystemWatcher>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QPoint>
#include <QVariantList>

class DesktopItem;

class DesktopManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString desktopPath READ desktopPath CONSTANT)
    Q_PROPERTY(QVariantList files READ files NOTIFY filesChanged)

public:
    explicit DesktopManager(QObject *parent = nullptr);

    QString desktopPath() const;
    QVariantList files() const;

    Q_INVOKABLE void setItemPosition(const QString &path, int x, int y);
    Q_INVOKABLE void setDesktopSize(int width, int height);

signals:
    void filesChanged();

private slots:
    void refresh();

private:
    void loadPositions();
    void savePositions();

    DesktopItem *findItem(const QString &path) const;
    QPoint findFreePosition() const;
    QPoint clampPosition(const QPoint &position) const;

    QString m_desktopPath;

    QList<DesktopItem *> m_items;

    QFileSystemWatcher m_watcher;

    QJsonObject m_positions;

    int m_desktopWidth = 0;
    int m_desktopHeight = 0;
};