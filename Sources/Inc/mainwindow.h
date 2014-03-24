#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addWidgetButton_clicked();
    void on_startServerButton_clicked();
    void on_delWidgetButton_clicked();

private:
    Ui::MainWindow *ui;

    void EnableButtons();
    void DisableButton();
    bool AddWidgetToModel();
    void UpdateListListWidget();
};

#endif // MAINWINDOW_H
