#include "logic.h"
#include "PathController.cpp"
#include <iostream>

Logic::Logic(QObject *parent)
    : QObject{parent}
{
}

void Logic::buildARoute(){
    if(!restrictedList.isEmpty()){
        double xA;
        double xB;
        double xC;
        double yA;
        double yB;
        double yC;
        QList<QLineF> lineList1;
        QList<QLineF> lineList2;
        QList<QLineF> lineList3;
        QList<QLineF> lineList4;
        bool isIntersection = false;
        for(int i=0; i < restrictedList.length(); i++){
            QLineF *co_Directional =  new QLineF(baseLine.getLastLineList()->toLine());
            xA = co_Directional->x1();
            xB = co_Directional->x2();
            xC = restrictedList.at(i).x();
            yA = co_Directional->y1();
            yB = co_Directional->y2();
            yC = restrictedList.at(i).y();

            xA = xA + (xC - xB);
            yA = yA + (yC - yB);
            xB = xC;
            yB = yC;

            QLineF* line = new QLineF(xA, yA, xB, yB);
            QLineF vector1 = line->normalVector();
            QLineF vector2 = line->normalVector();
            vector1.setLength(radiusList.at(i) * 0.00004);
            vector2.setLength(radiusList.at(i) * 0.00004);
            vector2.setAngle(180);
            lineList1.append(vector1);
            lineList2.append(vector2);
            QPointF intersectionPoint;
            if (co_Directional->intersects(vector1, &intersectionPoint) != QLineF::NoIntersection){
                isIntersection = true;
            }
        }
        int count = lineList1.length();
        if(isIntersection){
            QPointF point1 = *new QPointF(baseLine.getLastLineList()->p1());
            for (int i = 0; i < count; ++i) {
                QLineF smallest = *new QLineF;
                int count = 0;
                for(int j = 0; j < count; j++){
                    QPointF point2 = *new QPointF(lineList1.at(j).p1());
                    QLineF lenghtLine = *new QLineF(point1, point2);
                    if(smallest.length() < lenghtLine.length()){
                        smallest = lenghtLine;
                        count = j;
                    }
                }
                lineList3.append(lineList1.at(count));
                lineList1.removeAt(count);
                lineList4.append(lineList2.at(count));
                lineList2.removeAt(count);
            }
        }
        QPointF point = baseLine.getLastLineList()->p1();
        QLineF endLine = *baseLine.getLastLineList();
        for(int i = 0; i < lineList4.length(); i++){
            QPointF *intersectionPoint = new QPointF;
            QPointF tempPoint;
            if(endLine.intersects(lineList4.at(i), intersectionPoint) == 2){
                tempPoint = lineList4.at(i).p2();
                mainLines.addNewLine(point, lineList4.at(i).p2());
            }else if(endLine.intersects(lineList3.at(i), intersectionPoint) == 2){
                tempPoint = lineList3.at(i).p2();
                mainLines.addNewLine(point, lineList3.at(i).p2());
            }else{

            }
            point = tempPoint;
            endLine.setP1(point);
        }

        for (int i = 0; i < mainLines.lineList().length(); i++) {
            std::cout << "MainLines: " << mainLines.lineList().at(i)->x1() << " " << mainLines.lineList().at(i)->y1() << " " << mainLines.lineList().at(i)->x2() << " " << mainLines.lineList().at(i)->y2() << " " <<std::endl;
            QPointF pointStart = mainLines.lineList().at(i)->p1();
            QPointF pointEnd = mainLines.lineList().at(i)->p2();

            emit getMapLine(pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y());
        }
        mainLines.clearList();
    };
}

void Logic::addBaseLine(QLineF line){
    baseLine.addNewLine(&line);
    buildARoute();
}

void Logic::addRestrictedArea(QPointF point, const int radius){
    std::cout << "RectArea" << point.x() << " : " << point.y() << std::endl;
    restrictedList.append(point);
    radiusList.append(radius);
}
