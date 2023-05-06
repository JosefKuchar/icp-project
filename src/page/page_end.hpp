/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_end.hpp
 * @brief EndPage header
 */

#pragma once

#include <QLabel>
#include <QWidget>

class EndPage : public QWidget {
    Q_OBJECT

   public:
    EndPage(QWidget* parent = nullptr);
    ~EndPage();
    void showEvent(QShowEvent* event) override;

   private:
    QLabel* resultText;
    QLabel* keyText;
    QLabel* stepText;
};
