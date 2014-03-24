#ifndef WIDGETDATAMODEL_H
#define WIDGETDATAMODEL_H

#include <QObject>
#include <QMap>
#include <QFileInfo>
#include <QMapIterator>

class widgetdatamodel : public QObject
{
    Q_OBJECT
public:
    typedef QMapIterator<QString, QFileInfo> widgetDataModelIter;

    static widgetdatamodel& Self()
    {
        static widgetdatamodel instanse;
        return instanse;
    }

    widgetDataModelIter iterator();
    QMap<QString, QFileInfo> data();
    int size()const;
    bool empty()const;
    void remove(int row);

private:
    widgetdatamodel();
    void operator =(widgetdatamodel&);
    QMap<QString, QFileInfo> mData;

public slots:
    void AddItem(const QFileInfo& newItem);
};

#endif // WIDGETDATAMODEL_H
