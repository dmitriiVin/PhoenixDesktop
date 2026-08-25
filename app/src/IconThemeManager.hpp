#pragma once

#include <QObject>
#include <QString>

class IconThemeManager : public QObject {
    Q_OBJECT
public:
    explicit IconThemeManager(QObject *parent = nullptr);
    Q_INVOKABLE QString iconForFile(const QString &path) const;

private:
    QString findIcon(const QString &iconName) const;
    QString m_themePath;
};
