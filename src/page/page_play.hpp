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

/**
 * @brief Play page
 */
class PlayPage : public BaseGamePage {
    Q_OBJECT

   private slots:
    void tick() override;

   private:
    void end();

   public:
    /**
     * @brief Play page constructor
     */
    PlayPage(QWidget* parent = nullptr);
    ~PlayPage();

    /**
     * @brief Handle key press event (WSAD and arrow keys)
     */
    void keyPressEvent(QKeyEvent* event) override;

    /**
     * @brief Initialize play page
     */
    void showEvent(QShowEvent* event) override;
};
