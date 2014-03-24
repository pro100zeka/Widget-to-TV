#include "processor.h"
#include "xmlgen.h"
#include "widgetdatamodel.h"
#include <sstream>

processor::processor()
{
}

void processor::ProcessAction(QTcpSocket* pSock)
{

    QByteArray qBa = pSock->readAll();
    qDebug() << qBa;
    std::stringstream ss(qBa.data());
    std::string sLine;
    for (int nCount = 2; nCount > 0; --nCount)
    {
        ss >> sLine;
    }

    QTextStream os(pSock);
    os.setAutoDetectUnicode(true);

    if(sLine == "/widgetlist.xml")
    {
        os << "HTTP/1.0 200 Ok\r\n" <<
              "Content-Type: text/html; charset=\"utf-8\"\r\n" <<
              "\r\n" << xmlgen::Self().getWidgetListXml() << "\n\n";

        pSock->close();
        return;
    }
    else if(!sLine.empty())
    {
        QString FilePath = QFileInfo(QString::fromStdString(sLine)).baseName();
        if(!FilePath.isEmpty())
        {
            QFileInfo FileToSend = widgetdatamodel::Self().data()[FilePath];
            if(FileToSend.exists())
            {
                QFile file(FileToSend.absoluteFilePath());
                if(file.open(QIODevice::ReadOnly))
                {
                    std::stringstream HttpHeaders;
                    HttpHeaders << "HTTP/1.0 200 Ok\r\nContent-Length: " << FileToSend.size() <<
                                                "\r\nConnection: close\r\nServer: Apache/2\n\n";
                    qDebug() << HttpHeaders.str().c_str() ;
                    pSock->write(HttpHeaders.str().c_str());
                    pSock->write(file.readAll());
                    pSock->waitForBytesWritten();
                    pSock->close();
                    return;
                }
            }
        }
    }

    os << "HTTP/1.0 404 Ok\r\n" <<
          "Content-Type: text/html; charset=\"utf-8\"\r\n" <<
          "\r\nNot found\n\n";

    pSock->close();
}
