#include "restricted_area_list.h"
#include "restricted_area.h"
#include <iostream>

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

void RestrictedAreaList::addNewResArea(QPointF point, int radius){
    RestrictedArea *newRestrictedArea = new RestrictedArea;
    newRestrictedArea->receiveArea(point, radius);
    this->_resAreaList.append(newRestrictedArea);

    emit newResArea(point, radius);
}
