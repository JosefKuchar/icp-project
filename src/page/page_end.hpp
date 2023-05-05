/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_end.hpp
 * @brief EndPage header
 */

#pragma once

#include <QWidget>

class EndPage : public QWidget {
    Q_OBJECT

   public:
    EndPage(QWidget* parent = nullptr);
    ~EndPage();
};
