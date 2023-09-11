#include "restricted_area.h"

QPointF _restArea;

RestrictedArea::RestrictedArea(QObject *parent)
    : QObject{parent}
{
}

QPointF RestrictedArea::restArea(){
    return this->_restArea;
}

void RestrictedArea::setRestArea(QPointF &restArea){
    this->_restArea = restArea;
}

void RestrictedArea::receiveArea(QPointF restArea, QPointF radiusX, QPointF radiusY){
    this->_restArea = restArea;
    this->radiusX = radiusX;
    this->radiusY = radiusY;
}


