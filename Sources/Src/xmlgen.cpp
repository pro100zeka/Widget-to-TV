#include "xmlgen.h"
#include "widgetdatamodel.h"
#include <QMap>
#include <QXmlStreamWriter>
#include <QDebug>
#include "widgetnetwork.h"

QString xmlgen::getWidgetListXml()
{
    QString sWidgetListXmlRes;
    widgetdatamodel::widgetDataModelIter i = widgetdatamodel::Self().iterator();
    if(!i.hasNext())
    {
        return sWidgetListXmlRes;
    }

    QXmlStreamWriter* xmlWriter = new QXmlStreamWriter(&sWidgetListXmlRes);
    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartDocument();
    xmlWriter->writeStartElement("rsp");
    xmlWriter->writeAttribute("stat", "ok");
    xmlWriter->writeStartElement("list");


    while (i.hasNext())
    {
        i.next();

        xmlWriter->writeStartElement("widget");
        xmlWriter->writeAttribute("id", i.key());

            xmlWriter->writeStartElement("title");
                xmlWriter->writeCharacters (i.key());
            xmlWriter->writeEndElement();

            xmlWriter->writeStartElement("compression");
                xmlWriter->writeAttribute("size", QString::number(i.value().size()));
                xmlWriter->writeAttribute("type", "zip");
            xmlWriter->writeEndElement();

            xmlWriter->writeStartElement("description");
                xmlWriter->writeCharacters (i.value().fileName() + " (" + QString::number(i.value().size()) + ")");
            xmlWriter->writeEndElement();

            xmlWriter->writeStartElement("download");
                xmlWriter->writeCharacters("http://" +
                                           widgetnetwork::Self().getIpString() +
                                           "/" +
                                           i.value().fileName());
            xmlWriter->writeEndElement();

        xmlWriter->writeEndElement();
    }

    xmlWriter->writeEndElement();// list
    xmlWriter->writeEndElement(); // rsp
    xmlWriter->writeEndDocument();

    delete xmlWriter;

    qDebug() << sWidgetListXmlRes;

    return sWidgetListXmlRes;
}










