/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_replay.hpp
 * @brief ReplayPage header
 */

#pragma once

#include <QWidget>
#include <QtWidgets>
#include "page_basegame.hpp"
#include "sprite.hpp"

enum class ReplayMode { Backwards, Stopped, Forwards };

class ReplayPage : public BaseGamePage {
    Q_OBJECT

   public:
    ReplayPage(QWidget* parent = nullptr);
    ~ReplayPage();
    void showEvent(QShowEvent* event) override;
    void getStepAndDraw();

   private slots:
    void tick() override;

   private:
    size_t frameIndex;
    ReplayMode replayMode;
};
