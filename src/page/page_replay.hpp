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

enum class ReplayMode { Backwards, Stopped, Forwards };

class ReplayPage : public QWidget {
    Q_OBJECT

   public:
    ReplayPage(QWidget* parent = nullptr);
    ~ReplayPage();
    void showEvent(QShowEvent* event) override;
    void start();
    void end();
    void draw();
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
    size_t frameIndex;
    ReplayMode replayMode;
    Sprite* m_player;
    QList<Sprite*> m_ghosts;
    QList<Sprite*> m_keys;
    QList<Sprite*> m_objects;
};
