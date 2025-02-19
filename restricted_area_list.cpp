#include "restricted_area_list.h"
#include "restricted_area.h"
#include <iostream>
#include <QPointF>

RestrictedAreaList::RestrictedAreaList(QObject *parent)
    : QObject{parent}
{

}



QList<RestrictedArea*> RestrictedAreaList::resAreaList(){
    return this->_resAreaList;
}

void RestrictedAreaList::setResAreaList(const QList<RestrictedArea*> restAreaList){
    this->_resAreaList = restAreaList;

}

QPointF RestrictedAreaList::getLastResArea(){
    return _resAreaList.takeLast()->restArea();
}

void RestrictedAreaList::addNewResArea(RestrictedArea* restrictedArea){
    this->_resAreaList.append(restrictedArea);
}

void RestrictedAreaList::addNewResArea(QPointF point, QPointF radiusX, QPointF radiusY){
    RestrictedArea *newRestrictedArea = new RestrictedArea;
    newRestrictedArea->receiveArea(point, radiusX, radiusY);
    this->_resAreaList.append(newRestrictedArea);

    emit newResArea(point, radiusX, radiusY);
}
