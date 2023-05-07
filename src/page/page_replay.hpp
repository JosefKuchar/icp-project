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

/**
 * @brief Replay mode
 */
enum class ReplayMode { Backwards, Stopped, Forwards };

/**
 * @brief Replay page
 */
class ReplayPage : public BaseGamePage {
    Q_OBJECT

   public:
    /**
     * @brief Replay page constructor
     * @param parent Parent widget
     */
    ReplayPage(QWidget* parent = nullptr);
    ~ReplayPage();

    /**
     * @brief Initialize replay page
     */
    void showEvent(QShowEvent* event) override;

    /**
     * @brief Fetch current step from serializer and draw it
     */
    void getStepAndDraw();

   private slots:
    void tick() override;

   private:
    /// Current frame index
    size_t frameIndex;
    /// Replay mode
    ReplayMode replayMode;
};
