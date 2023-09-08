#include "way_point.h"
#include <iostream>

QPointF _point;

WayPoint::WayPoint(QObject *parent)
    : QObject{parent}
{
    connect(this, SIGNAL(pointStartExist()), this, SLOT(pointStartChanged()));
    connect(this, SIGNAL(pointEndExist()), this, SLOT(pointEndChanged()));
    connect(this, SIGNAL(pointChanged()), this, SLOT(pointStartChanged()));
    connect(this, SIGNAL(pointChanged()), this, SLOT(pointEndChanged()));
}

const double WayPoint::pointXStart(){;
    return this->_pointStart.x();
}

const double WayPoint::pointYStart(){
    return this->_pointStart.y();
}

const double WayPoint::pointXEnd(){;
    return this->_pointEnd.x();
}

const double WayPoint::pointYEnd(){
    return this->_pointEnd.y();
}


void WayPoint::pointStartChanged(const double pointX, const double pointY){
    this->_pointStart = *new QPointF(pointX, pointY);
    this->isStart = true;
    this->isChange = true;
}

void WayPoint::pointEndChanged(const double pointX, const double pointY){
    this->_pointEnd = *new QPointF(pointX, pointY);
    this->isEnd = true;
    this->isChange = true;
}

void WayPoint::pointsReady(){
    QLineF line = *new QLineF(_pointStart, _pointEnd);
    if(isStart && isEnd){
        emit lineReady(line);

    }
}

