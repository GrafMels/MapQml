#ifndef LINEFLIST_H
#define LINEFLIST_H

#include <QObject>
#include <QLineF>

class LineFList : public QObject
{
    Q_OBJECT
public:
    explicit LineFList(QObject *parent = nullptr);
    QList<QLineF*> lineList();
    Q_INVOKABLE void setLineList(QList<QLineF*> restArea);
    QLineF* getLastLineList();
    QLineF* getFirstLineList();
    void clearList();


public slots:
    void addNewLine(QPointF pointStart, QPointF pointEnd);
    void addNewLine(QLineF* line);
    QLineF* addNewLine();

private:
    QList<QLineF*> _lineList;
    QLineF* _line;
};

#endif // LINEFLIST_H
