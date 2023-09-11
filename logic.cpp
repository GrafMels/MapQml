#include "logic.h"
#include <iostream>
#include <math.h>
#include <QLineF>

Logic::Logic(QObject *parent)
    : QObject{parent}
{
}

void Logic::buildARoute(){
    restrictedList.append(restrictedList.at(restrictedList.length()-1));
    mainLines.addNewLine(baseLine.getFirstLineList());
    QList<QPointF> tempRestList = QList<QPointF>(restrictedList);
        bool isOpen = true;
        while (isOpen) {
            double mainAngle = 0;
            QLineF smallest = QLineF(tempRestList.at(0), mainLines.getLastLineList()->p1());
            double radius = 0.0;
            double radiusX = 0.0;
            double radiusY = 0.0;
            int count = 0;
            QLineF lenghtLine;

            mainAngle = mainLines.getLastLineList()->angle();

            for(int j = 0; j < tempRestList.length(); j++){//нахождение наименьшего элемента пузырьком
                lenghtLine = QLineF(tempRestList.at(j), mainLines.getLastLineList()->p1());
                if(smallest.length() > lenghtLine.length()){
                    smallest = lenghtLine;
                    count = j;
                }
            }

            double closestPointAngle = (QLineF(tempRestList.at(count), mainLines.getLastLineList()->p2())).angle();//определение ближайщей точки на элепсе к начальной точки пути
            radius = calcRadius(tempRestList.at(count), tempRestList.at(count), radiusListY.at(count), closestPointAngle);
            radiusX = abs(tempRestList.at(count).x() - radiusListX.at(count).x());
            QLineF tempClosestLine = QLineF();
            tempClosestLine.setP1(tempRestList.at(count));
            tempClosestLine.setLength(radiusX);
            tempClosestLine.setAngle(closestPointAngle);

            double newPerpendicular1 = 0;
            double newPerpendicular2 = 0;
            if(mainAngle<90){
                newPerpendicular1 = mainAngle + 90;
                newPerpendicular2 = mainAngle + 270;
            }else if(mainAngle>=270){
                newPerpendicular1 = mainAngle - 90;
                newPerpendicular2 = mainAngle - 270;
            }else{
                newPerpendicular1 = mainAngle + 90;
                newPerpendicular2 = mainAngle - 90;
            }

            radius = calcRadius(tempRestList.at(count), radiusListX.at(count), radiusListY.at(count), newPerpendicular1);
            radiusX = abs(tempRestList.at(count).x() - radiusListX.at(count).x());
            radiusY = abs(tempRestList.at(count).y() - radiusListY.at(count).y());

            QLineF line1 = QLineF();
            QLineF line2 = QLineF();

            line1.setP1(tempRestList.at(count));
            line2.setP1(tempRestList.at(count));
            line1.setLength(radius + radius*0.4);
            line2.setLength(radius + radius*0.4);
            line1.setAngle(newPerpendicular1);
            line2.setAngle(newPerpendicular2);

            QPointF pointEnd;
            if(QLineF(mainLines.getLastLineList()->p1(), line1.p2()).length() < QLineF(mainLines.getLastLineList()->p1(), line2.p2()).length()){
                pointEnd = line1.p2();
            }else{
                pointEnd = line2.p2();
            }

            QPointF leftTopPoint = QPointF(tempRestList.at(count).x() + radiusX, tempRestList.at(count).y() - radiusY);//определение прямоугольника элипса для функции circle
            QPointF bottomRightPoint = QPointF(tempRestList.at(count).x() - radiusX, tempRestList.at(count).y() + radiusY);

            if(circle(QRectF(leftTopPoint, bottomRightPoint), mainLines.getLastLineList()->p1(), mainLines.getLastLineList()->p2())){//Добавление линии в список линий
                if(mainLines.lineList().length() == 1){
                    mainLines.addNewLine(mainLines.getLastLineList()->p1(), pointEnd);
                }else{
                    mainLines.addNewLine(mainLines.getLastLineList()->p2(), pointEnd);
                }

            }

            if(tempRestList.length() != 1){
                tempRestList.removeAt(count);
            }else{
                isOpen = false;
            }
        }
        mainLines.addNewLine(mainLines.getLastLineList()->p2(), mainLines.getFirstLineList()->p2());
        for (int i = 1; i < mainLines.lineList().length()-2; i++) {
            emit getMapLine(mainLines.lineList().at(i)->x1(), mainLines.lineList().at(i)->y1(), mainLines.lineList().at(i)->x2(), mainLines.lineList().at(i)->y2());
        }
}


bool Logic::circle(QRectF rect, QPointF pt1, QPointF pt2){ // Логика для вычисления пересечения с элипсом
    double _a = rect.width() / 2.0;
    double _b = rect.height() / 2.0;
    double x0 = rect.x() + rect.width() /2.0;
    double y0 = rect.y() + rect.height() /2.0;

    double k = (pt2.y() - pt1.y()) / (double)(pt2.x() - pt1.x());
    double b = pt1.y() - k * pt1.x();

    double v = (_a*_a)*(_b*_b);
    double s = b - y0;

    double A = -1;
    double B = -1;
    double C = -1;
    if(pt2.x() - pt1.x() != 0) {
        A = (_b * _b) + (_a * _a) * (k * k);
        B = 2 * ((_a * _a) * k * s - (_b * _b) * x0);
        C = (_b * _b) * (x0 * x0) + (_a * _a) * (s * s) - v;
    }else{
        double w = (1 - (((pt1.x() - x0, 2)*(pt1.x() - x0), 2) / (_a*_a))) * (_b*_b);
        A = 1;
        B = -2 * y0;
        C = (y0 * y0) - w;
    }
    double D = (B * B) - 4*A*C;
    if(pt2.x() - pt1.x() != 0) {
        if (D < 0) {
            return false;
        } else if (D == 0) {
            return false;
        } else {
            return true;
        }
    }else{
        if (D < 0) {
            return false;
        } else if (D == 0) {
            return false;
        } else {
            return true;
        }
    }
}

const double Logic::calcRadius(const QPointF restArea, const QPointF radiusXX, const QPointF radiusYY, double angle){
    double diffX = 0;
    double diffY = 0;
    double angleX = 0;
    double angleY = 0;
    double radiusInPoint = 0;
    diffX = abs(restArea.x() - radiusXX.x());
    diffY = abs(restArea.y() - radiusYY.y());
    if(angle < 90){
        angleX = angle/90;
        angleY = (90 - angle)/90;
        radiusInPoint = diffX*angleY + diffY*angleX;

    }else if(angle < 180){
        angle -= 90;
        angleY = angle/90;
        angleX = (90 - angle)/90;
        radiusInPoint = diffX*angleY + diffY*angleX;
    }else if(angle < 270){
        angle -= 180;
        angleX = angle/90;
        angleY = (90 - angle)/90;
        radiusInPoint = diffX*angleY + diffY*angleX;
    }else{
        angle -= 270;
        angleY = angle/90;
        angleX = (90 - angle)/90;
        radiusInPoint = diffX*angleY + diffY*angleX;
    }

    return radiusInPoint;
}

void Logic::addBaseLine(QLineF line){
    baseLine.addNewLine(&line);
    buildARoute();
}

void Logic::addRestrictedArea(QPointF point, QPointF radiusX, QPointF radiusY){
    restrictedList.append(point);
    radiusListX.append(radiusX);
    radiusListY.append(radiusY);
}
