/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_end.hpp
 * @brief EndPage header
 */

#pragma once

#include <QLabel>
#include <QWidget>

/**
 * @brief End page
 */
class EndPage : public QWidget {
    Q_OBJECT

   public:
    /**
     * @brief End page constructor
    */
    EndPage(QWidget* parent = nullptr);
    ~EndPage();

    /**
     * @brief Initialize end page
    */
    void showEvent(QShowEvent* event) override;

   private:
    /// Win / lose text
    QLabel* resultText;
    /// Key text
    QLabel* keyText;
    /// Step text
    QLabel* stepText;
};
