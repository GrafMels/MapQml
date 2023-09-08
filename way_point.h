#ifndef WAY_POINT_H
#define WAY_POINT_H

#include <QObject>
#include <QLineF>



class WayPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(READ point NOTIFY pointsReady FINAL)
public:
    explicit WayPoint(QObject *parent = nullptr);

private:
    QPointF _pointStart;
    QPointF _pointEnd;
    double x;
    double y;
    bool isStart = false;
    bool isEnd = false;
    bool isChange = false;

public slots:
    const double pointXStart();
    const double pointYStart();
    const double pointXEnd();
    const double pointYEnd();
    void pointStartChanged(const double pointX, const double pointY);
    void pointEndChanged(const double pointX, const double pointY);
    void pointsReady();


signals:
    void lineReady(QLineF line);

};


#endif // WAY_POINT_H
