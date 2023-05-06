/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_basegame.hpp
 * @brief BaseGamePage header
 */

#pragma once

#include <QWidget>
#include <QtWidgets>
#include "sprite.hpp"

class BaseGamePage : public QWidget {
    Q_OBJECT

   public:
    BaseGamePage(QWidget* parent = nullptr);
    ~BaseGamePage();
    void resizeEvent(QResizeEvent* event) override;
    void clear();
    void draw(GameInfo info);
    void drawMap(MapInfo map);

   protected slots:
    virtual void tick();

   protected:
    QTimer* timer;
    Game* game;
    QGraphicsScene* m_gameScene;
    QGraphicsView* view;
    QVBoxLayout* layout;
    int m_rows;
    int m_cols;
    Sprite* m_player;
    QList<Sprite*> m_ghosts;
    QList<Sprite*> m_keys;
    QList<Sprite*> m_objects;
};
