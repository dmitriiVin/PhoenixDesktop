#include "IconThemeManager.hpp"

#include <QDir>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QUrl>

IconThemeManager::IconThemeManager(QObject *parent) : QObject(parent) {
    m_themePath = "/usr/share/icons/Papirus-Dark";
}

QString IconThemeManager::iconForFile(const QString &path) const {
    QFileInfo file(path);

    QString iconName;

    if (file.isDir()) {
        iconName = "folder";
    }
    else {
        QMimeDatabase database;
        QMimeType mime = database.mimeTypeForFile(file);

        iconName = mime.iconName();

        if (iconName.isEmpty())
            iconName = "text-x-generic";
    }

    return findIcon(iconName);
}

QString IconThemeManager::findIcon(const QString &iconName) const {
    const QStringList sizes = {"64x64", "48x48", "42x42", "32x32", "24x24", "22x22", "18x18", "16x16", "scalable"};

    const QStringList categories = {"places", "mimetypes", "actions", "apps"};

    for (const QString &category : categories) {
        for (const QString &size : sizes) {

            QString path = m_themePath + "/" + size + "/" + category + "/" + iconName + ".svg";

            if (QFileInfo::exists(path))
                return QUrl::fromLocalFile(path).toString();
        }
    }

    return {};
}
