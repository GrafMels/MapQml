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

void RestrictedArea::receiveArea(QPointF restArea, int radius){
    this->_restArea = restArea;
    this->radius = radius;
}


