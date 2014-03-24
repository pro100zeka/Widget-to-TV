#include "widgetnetwork.h"
#include "processor.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>

widgetnetwork::widgetnetwork()
{
    mpTcpServer = new QTcpServer(this);
    mbPaused = false;
}

widgetnetwork::~widgetnetwork()
{
    mpTcpServer->close();
    mpTcpServer->deleteLater();
}

bool widgetnetwork::listen(quint16 port)
{

    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if(interface.flags().testFlag(QNetworkInterface::IsRunning) &&
                !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            foreach (QNetworkAddressEntry entry, interface.addressEntries())
            {
                if ( interface.hardwareAddress() != "00:00:00:00:00:00" && entry.ip().toString().contains("."))
                {
                    QMessageBox msgBox;
                    if (!mpTcpServer->listen(entry.ip(), port))
                    {
                        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(mpTcpServer->errorString());
                        msgBox.setText("Unable to start the server");
                        msgBox.exec();
                    }
                    else
                    {
                        qDebug() << QString::fromUtf8("Сервер запущен!");
                        connect(mpTcpServer, SIGNAL(newConnection()), this, SLOT(newTVConnection()));
                        msgBox.setText(getIpString());
                        msgBox.exec();

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

QString widgetnetwork::getIpString()
{
    return mpTcpServer->serverAddress().toString();
}

bool widgetnetwork::isStarted()
{
    return mpTcpServer->isListening();
}

bool widgetnetwork::isPaused()
{
    return mbPaused;
}

void widgetnetwork::pause()
{
    mpTcpServer->pauseAccepting();
    mbPaused = true;
}

void widgetnetwork::resume()
{
    mpTcpServer->resumeAccepting();
    mbPaused = false;
}

void widgetnetwork::newTVConnection()
{
    if(mpTcpServer->isListening())
    {
        connect(mpTcpServer->nextPendingConnection(), SIGNAL(readyRead()), this, SLOT(incomingData()));
    }
}

void widgetnetwork::incomingData()
{
    processor::Self().ProcessAction((QTcpSocket*)sender());
}
