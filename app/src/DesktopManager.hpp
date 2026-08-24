#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

class DesktopManager : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString desktopPath READ desktopPath CONSTANT)

  Q_PROPERTY(QVariantList files READ files NOTIFY filesChanged)

public:
  explicit DesktopManager(QObject *parent = nullptr);

  QString desktopPath() const;

  QVariantList files() const;

signals:

  void filesChanged();

private:
  QString m_desktopPath;

  QVariantList m_files;

  void loadFiles();
};