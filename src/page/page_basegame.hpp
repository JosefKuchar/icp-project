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

/**
 * @brief Base game page
 */
class BaseGamePage : public QWidget {
    Q_OBJECT

   public:
    /**
     * @brief Base game page constructor
     * @param parent Parent widget
     */
    BaseGamePage(QWidget* parent = nullptr);
    ~BaseGamePage();

    /**
     * @brief Resizes game scene to fit the window
     */
    void resizeEvent(QResizeEvent* event) override;

    /**
     * @brief Clear all sprites from game scene
     */
    void clear();

    /**
     * @brief Draw game step
     */
    void draw(GameInfo info);

    /**
     * @brief Draw initial map
     */
    void drawMap(MapInfo map);

   protected slots:
    virtual void tick();

   protected:
    /// Game timer
    QTimer* timer;
    /// Game logic
    Game* game;
    /// Game scene
    QGraphicsScene* gameScene;
    /// Game view
    QGraphicsView* view;
    /// Main layout
    QVBoxLayout* layout;
    /// Rows count
    int rows;
    /// Columns count
    int cols;
    /// Player sprite
    Sprite* player;
    /// Ghosts sprites
    QList<Sprite*> ghosts;
    /// Keys sprites
    QList<Sprite*> keys;
    /// All sprites
    QList<Sprite*> objects;
    /// Text for displaying collected keys
    QLabel* keyText;
    /// Text for displaying current step
    QLabel* stepText;
};
