#pragma once

#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "game/game.hpp"
#include "maploader.hpp"
#include "serializer.hpp"
#include "sprite.hpp"

class GameScene : public QGraphicsScene {
    Q_OBJECT

   public:
    GameScene(MapInfo& map);
    void start();
    void updatePositions();
    void setDirection(QPoint direction);
    ~GameScene();

    Game* game;
    Serializer serializer;

   private slots:
    void tick();

   private:
    int m_rows;
    int m_cols;
    Sprite* m_player;
    QList<Sprite*> m_ghosts;
    QList<Sprite*> m_keys;
    QList<Sprite*> m_objects;
};
