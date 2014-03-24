#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QTcpSocket>

class processor
{
public:
    static processor Self()
    {
        static processor instance;
        return instance;
    }

    void ProcessAction(QTcpSocket* pSock);

private:
    processor();
    processor&operator =(processor&);
};

#endif // PROCESSOR_H
