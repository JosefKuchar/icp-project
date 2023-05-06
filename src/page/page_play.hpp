/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_play.hpp
 * @brief PlayPage header
 */

#pragma once

#include <QWidget>
#include <QtWidgets>
#include "page_basegame.hpp"
#include "sprite.hpp"

class PlayPage : public BaseGamePage {
    Q_OBJECT

   private slots:
    void tick() override;

   public:
    void keyPressEvent(QKeyEvent* event) override;
    PlayPage(QWidget* parent = nullptr);
    ~PlayPage();
    void showEvent(QShowEvent* event) override;
    void end();
    void updatePositions();
    void setDirection(QPoint direction);
};
