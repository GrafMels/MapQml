#ifndef RESTRICTED_AREA_H
#define RESTRICTED_AREA_H

#include <QObject>

class RestrictedArea : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF restArea READ restArea WRITE setRestArea FINAL)
public:
    explicit RestrictedArea(QObject *parent = nullptr);
    QPointF restArea();
    Q_INVOKABLE void setRestArea(QPointF &restArea);

public slots:
    void receiveArea(QPointF restArea, int radius);

private:
    QPointF _restArea;
    int radius;
    int id;
};

#endif // RESTRICTED_AREA_H
