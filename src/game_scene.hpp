#pragma once

#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "mainwindow.hpp"
#include "maploader.hpp"
#include "ui_mainwindow.h"

class Sprite : public QGraphicsPixmapItem {
   public:
    Sprite(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap) {}
};

class Grid : public QGraphicsScene {
   public:
    Grid(MapInfo& map);
    void updatePositions();

   private:
    int m_rows;
    int m_cols;
    QPixmap m_spritePixmap;
    QList<Sprite*> m_sprites;
};
