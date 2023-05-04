#pragma once

#include <QWidget>
#include "game_scene.hpp"

class PlayPage : public QWidget {
    Q_OBJECT

   public:
    void keyPressEvent(QKeyEvent* event) override;
    PlayPage(QWidget* parent = nullptr);
    ~PlayPage();

   private:
    GameScene* m_gameScene;
};
