#include "widgetdatamodel.h"
#include <QtDebug>

widgetdatamodel::widgetDataModelIter widgetdatamodel::iterator()
{
    return widgetDataModelIter(mData);
}

QMap<QString, QFileInfo> widgetdatamodel::data()
{
    return mData;
}

int widgetdatamodel::size() const
{
    return mData.size();
}

bool widgetdatamodel::empty() const
{
    return mData.empty();
}

void widgetdatamodel::remove(int row)
{
    if(row > mData.size())
    {
        return;
    }

    QMap<QString, QFileInfo>::iterator iter = mData.begin();
    int nStart = 0;
    while (row > nStart)
    {
        ++iter;
        ++nStart;
    }
    mData.erase(iter);
}

widgetdatamodel::widgetdatamodel()
{
}

void widgetdatamodel::operator =(widgetdatamodel &)
{

}

void widgetdatamodel::AddItem(const QFileInfo &newItem)
{
    mData[newItem.baseName()] = newItem;
}
