#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <xmleditor.h>
#include <treemodel.h>
#include <treenode.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<XmlEditor>("XmlEditor", 1, 1, "XmlEditor");
    qmlRegisterType<TreeModel>("TreeModel", 1, 1, "TreeModel");
    qmlRegisterType<TreeNode>("TreeModel", 1, 1, "TreeNode");
    engine.load(url);

    return app.exec();
}
