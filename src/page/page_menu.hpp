/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_menu.hpp
 * @brief MenuPage header
 */

#pragma once

#include <QWidget>

class MenuPage : public QWidget {
    Q_OBJECT

   public:
    MenuPage(QWidget* parent = nullptr);
    ~MenuPage();
};
