#ifndef RESTARTWINDOW_H
#define RESTARTWINDOW_H

#include "ui_restartwindow.h"
#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class RestartWindow;
}

class RestartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RestartWindow(QWidget *parent = nullptr);
    Ui::RestartWindow& getUi() const;
    void showMessage(const QString &text);
    ~RestartWindow();

private:
    Ui::RestartWindow *ui;
    QGraphicsScene _scene;
};

#endif // RESTARTWINDOW_H
