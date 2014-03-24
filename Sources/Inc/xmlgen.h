#ifndef XMLGEN_H
#define XMLGEN_H

#include <QString>

class xmlgen
{
public:
    static xmlgen Self()
    {
        static xmlgen inst;
        return inst;
    }

    QString getWidgetListXml();

private:
    xmlgen(){}
    xmlgen operator= (xmlgen&);

};

#endif // XMLGEN_H
