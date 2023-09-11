#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QQmlContext>
#include <QtWidgets>
#include <QLineF>
#include <iostream>

#include "line_f_list.h"

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = nullptr);
    void buildARoute();
    void heapify(QList<QLineF> line, int n, int i);
    void sort(QList<QLineF> line);
    bool circle(QRectF rect, QPointF pt1, QPointF pt2);
    const double calcRadius(const QPointF restArea, const QPointF radiusX, const QPointF radiusY, const double angle);

public slots:
    void addBaseLine(QLineF line);
    void addRestrictedArea(QPointF point, QPointF radiusX, QPointF radiusY);

signals:
    void getMapLine(double x1, double y1, double x2, double y2);
    void printPoint(double x, double y);

private:
    LineFList baseLine;
    LineFList mainLines;
    QList<QPointF> restrictedList;
    QList<QPointF> radiusListX;
    QList<QPointF> radiusListY;
};

#endif // LOGIC_H
