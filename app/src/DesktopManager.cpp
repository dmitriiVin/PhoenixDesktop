#include "DesktopManager.hpp"

#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

DesktopManager::DesktopManager(QObject *parent) : QObject(parent) {

  m_desktopPath =
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

  loadFiles();
}

QString DesktopManager::desktopPath() const { return m_desktopPath; }

QVariantList DesktopManager::files() const { return m_files; }

void DesktopManager::loadFiles() {

  QDir dir(m_desktopPath);

  QFileInfoList list =
      dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

  for (const QFileInfo &file : list) {

    QVariantMap item;

    item["name"] = file.fileName();

    item["path"] = file.absoluteFilePath();

    item["folder"] = file.isDir();

    m_files.append(item);
  }

  emit filesChanged();
}