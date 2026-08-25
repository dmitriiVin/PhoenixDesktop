#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "Application.hpp"
#include "DesktopItem.hpp"
#include "DesktopManager.hpp"
#include "IconThemeManager.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<DesktopManager>("Phoenix", 1, 0, "DesktopManager");
    qmlRegisterUncreatableType<DesktopItem>("Phoenix", 1, 0, "DesktopItem", "DesktopItem is created by DesktopManager");
    qmlRegisterType<IconThemeManager>("Phoenix", 1, 0, "IconThemeManager");

    QQmlApplicationEngine engine;

    engine.loadFromModule("Phoenix", "Main");

    return app.exec();
}
