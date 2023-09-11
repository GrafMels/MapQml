#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWidgets>
#include <QLineF>
#include <iostream>

#include "restricted_area_list.h"
#include "way_point.h"
#include "logic.h"
#include "line_f_list.h"



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    RestrictedAreaList restrictedAreaList;
    WayPoint wayPoint;
    LineFList baseLine;
    LineFList mainLines;
    LineFList mainWayTemp;
    LineFList tempLines;
    Logic logic;


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QObject::connect(&wayPoint, SIGNAL(lineReady(QLineF)), &logic, SLOT(addBaseLine(QLineF)));
    QObject::connect(&restrictedAreaList, SIGNAL(newResArea(QPointF, QPointF, QPointF)), &logic, SLOT(addRestrictedArea(QPointF, QPointF, QPointF)));

    engine.rootContext()->setContextProperty("logic", &logic);
    engine.rootContext()->setContextProperty("wayPoint", &wayPoint);
    engine.rootContext()->setContextProperty("restrictedAreaList", &restrictedAreaList);
    engine.load(url);
    return app.exec();
}
