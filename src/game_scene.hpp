#pragma once

#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "maploader.hpp"
#include "sprite.hpp"
#include "ui_mainwindow.h"

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
    Sprite* m_player;
    QList<Sprite*> m_objects;
    QPoint m_direction;
};
