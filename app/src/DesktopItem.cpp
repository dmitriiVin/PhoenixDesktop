#include "DesktopItem.hpp"

DesktopItem::DesktopItem(const QString &name, const QString &path, int x, int y, QObject *parent) : QObject(parent), m_name(name), m_path(path), m_x(x), m_y(y) {
}

QString DesktopItem::name() const {
    return m_name;
}

QString DesktopItem::path() const {
    return m_path;
}

int DesktopItem::x() const {
    return m_x;
}

int DesktopItem::y() const {
    return m_y;
}

void DesktopItem::setX(int x) {
    if (m_x == x)
        return;

    m_x = x;
    emit positionChanged();
}

void DesktopItem::setY(int y) {
    if (m_y == y)
        return;

    m_y = y;
    emit positionChanged();
}