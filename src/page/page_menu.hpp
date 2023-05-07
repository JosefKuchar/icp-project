/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_menu.hpp
 * @brief MenuPage header
 */

#pragma once

#include <QWidget>

/**
 * @brief Menu page
 */
class MenuPage : public QWidget {
    Q_OBJECT

   public:
    /**
     * @brief Menu page constructor
     * @param parent Parent widget
     */
    MenuPage(QWidget* parent = nullptr);
    ~MenuPage();
};
