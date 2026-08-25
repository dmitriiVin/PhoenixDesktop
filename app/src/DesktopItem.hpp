#pragma once

#include <QObject>
#include <QString>

class DesktopItem : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString path READ path CONSTANT)
    Q_PROPERTY(int x READ x NOTIFY positionChanged)
    Q_PROPERTY(int y READ y NOTIFY positionChanged)

public:
    static constexpr int Width = 90;
    static constexpr int Height = 110;

    explicit DesktopItem(const QString &name, const QString &path, int x, int y, QObject *parent = nullptr);

    QString name() const;
    QString path() const;

    int x() const;
    int y() const;

    void setX(int x);
    void setY(int y);

signals:
    void positionChanged();

private:
    QString m_name;
    QString m_path;

    int m_x;
    int m_y;
};