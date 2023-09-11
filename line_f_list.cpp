#include "line_f_list.h"

LineFList::LineFList(QObject *parent)
    : QObject{parent}
{

}

QList<QLineF*> LineFList::lineList(){
    return this->_lineList;
}

void LineFList::setLineList(const QList<QLineF*> lineList){
    this->_lineList = lineList;

}

QLineF* LineFList::getLastLineList(){
    return this->_lineList.at(_lineList.length()-1);
}

QLineF* LineFList::getFirstLineList(){
    return this->_lineList[0];
}

void LineFList::addNewLine(QPointF pointStart, QPointF pointEnd){
    QLineF* newLine = new QLineF(pointStart, pointEnd);
    this->_lineList.append(newLine);
}

void LineFList::addNewLine(QLineF* line){
    QLineF* newLine = new QLineF(line->p1(), line->p2());
    this->_lineList.append(newLine);
}

QLineF* LineFList::addNewLine(){
    return 0;
}

void LineFList::clearList(){
    _lineList.clear();
}

