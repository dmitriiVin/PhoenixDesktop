#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "DesktopManager.hpp"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  qmlRegisterType<DesktopManager>("Phoenix", 1, 0, "DesktopManager");

  QQmlApplicationEngine engine;

  engine.loadFromModule("Phoenix", "Main");

  return app.exec();
}