#ifndef WIDGETNETWORK_H
#define WIDGETNETWORK_H

#include <QTcpServer>

class widgetnetwork : public QObject
{
    Q_OBJECT
public:
    static widgetnetwork& Self()
    {
        static widgetnetwork inst;
        return inst;
    }

    virtual ~widgetnetwork();
    bool listen(quint16 port);
    QString getIpString();
    bool isStarted();
    bool isPaused();
    void pause();
    void resume();


private:
    widgetnetwork();
    void operator =(widgetnetwork&);

    QTcpServer *mpTcpServer;
    bool mbPaused;
public slots:
    void newTVConnection();
    void incomingData();
};

#endif // WIDGETNETWORK_H
