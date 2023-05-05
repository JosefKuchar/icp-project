/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_play.hpp
 * @brief PlayPage header
 */

#pragma once

#include <QWidget>
#include <QtWidgets>
#include "sprite.hpp"

class PlayPage : public QWidget {
    Q_OBJECT

   public:
    void keyPressEvent(QKeyEvent* event) override;
    PlayPage(QWidget* parent = nullptr);
    ~PlayPage();
    void showEvent(QShowEvent* event) override;
    void start();
    void end();
    void updatePositions();
    void setDirection(QPoint direction);

   private slots:
    void tick();

   private:
    QTimer* timer;
    Game* game;
    QGraphicsScene* m_gameScene;
    int m_rows;
    int m_cols;
    Sprite* m_player;
    QList<Sprite*> m_ghosts;
    QList<Sprite*> m_keys;
    QList<Sprite*> m_objects;
};
