#ifndef RESTRICTEDAREALIST_H
#define RESTRICTEDAREALIST_H

#include <QObject>

#include "restricted_area.h"

class RestrictedAreaList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<RestrictedArea*> resAreaList READ resAreaList WRITE setResAreaList FINAL)
public:
    explicit RestrictedAreaList(QObject *parent = nullptr);
    QList<RestrictedArea*> resAreaList();
    Q_INVOKABLE void setResAreaList(QList<RestrictedArea*> restArea);
    QPointF getLastResArea();


public slots:
    void addNewResArea(RestrictedArea* restrictedArea);
    void addNewResArea(QPointF point, QPointF radiusX, QPointF radiusY);

signals:
    void newResArea(QPointF point, QPointF radiusX, QPointF radiusY);

private:
    QList<RestrictedArea*> _resAreaList;
};

#endif // RESTRICTEDAREALIST_H


