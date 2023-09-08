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

public slots:
    void addBaseLine(QLineF line);
    void addRestrictedArea(QPointF point, const int radius);

signals:
    void getMapLine(double x1, double y1, double x2, double y2);

private:
    LineFList baseLine;
    LineFList mainLines;
    LineFList mainWayTemp;
    LineFList tempLines;
    QList<QPointF> restrictedList;
    QList<int> radiusList;
};

#endif // LOGIC_H
