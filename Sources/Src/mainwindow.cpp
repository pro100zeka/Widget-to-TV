#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgetdatamodel.h"
#include "widgetnetwork.h"

#include <QFileDialog>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addWidgetButton_clicked()
{
    if(AddWidgetToModel())
    {
        EnableButtons();
        UpdateListListWidget();
    }
}


void MainWindow::on_startServerButton_clicked()
{
    if(!widgetnetwork::Self().isStarted())
    {
        if(widgetnetwork::Self().listen(1080))
        {
            ui->startServerButton->setEnabled(false);
        }
    }
}

void MainWindow::EnableButtons()
{
    if(!widgetdatamodel::Self().empty())
    {
        ui->startServerButton->setEnabled(true);
        ui->delWidgetButton->setEnabled(true);
    }
}

void MainWindow::DisableButton()
{
    ui->startServerButton->setEnabled(false);
    ui->delWidgetButton->setEnabled(false);
}

bool MainWindow::AddWidgetToModel()
{
    static QString sWidgetFolderPath = "/home";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), sWidgetFolderPath, tr("Zip (*.zip)"));
    if(fileName.isEmpty())
    {
        return false;
    }

    QFileInfo NewWidget(fileName);
    sWidgetFolderPath = NewWidget.absolutePath();

    widgetdatamodel::Self().AddItem(NewWidget);

    if(widgetnetwork::Self().isPaused())
    {
        widgetnetwork::Self().resume();
    }

    return true;
}

void MainWindow::UpdateListListWidget()
{
    ui->listWidget->clear();

    widgetdatamodel::widgetDataModelIter i = widgetdatamodel::Self().iterator();
    if(!i.hasNext())
    {
        return;
    }

    while (i.hasNext())
    {
        i.next();

        QFileInfo fInfo = i.value();
        QListWidgetItem *Item = new QListWidgetItem();
        Item->setText(fInfo.fileName());
        Item->setIcon(QIcon("../icon/ico.png"));

        ui->listWidget->addItem(Item);
    }
}

void MainWindow::on_delWidgetButton_clicked()
{
    if(ui->listWidget->currentItem()->isSelected())
    {
        widgetdatamodel::Self().remove(ui->listWidget->row(ui->listWidget->currentItem()));
        UpdateListListWidget();
    }

    if(widgetdatamodel::Self().empty())
    {
        DisableButton();
        widgetnetwork::Self().pause();
    }

}

