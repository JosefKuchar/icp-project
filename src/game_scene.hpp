#pragma once

#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "maploader.hpp"
#include "object.hpp"
#include "ui_mainwindow.h"

class Sprite : public QGraphicsPixmapItem {
   public:
    Sprite(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap) {}
};

class Grid : public QGraphicsScene {
    Q_OBJECT

   public:
    Grid(MapInfo& map);
    void start();
    void updatePositions();
    void setDirection(QPoint direction);
    ~Grid();

   private slots:
    void tick();

   private:
    int m_rows;
    int m_cols;
    Object* m_player;
    QList<Object*> m_objects;
    QPoint m_direction;
};
