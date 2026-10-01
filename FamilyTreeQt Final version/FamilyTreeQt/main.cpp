#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QUrl>
#include <QQuickStyle>

int main(int argc, char* argv[])
{
    // Force the Basic style explicitly. Without this, Qt Quick
    // Controls picks a platform-dependent default style, which we
    // don't want here: this app defines its own visual language
    // (Theme.qml, PersonCard, NavButton) and needs standard controls
    // (TextField, Button, RadioButton) to behave predictably across
    // every machine it runs on, rather than silently varying with
    // whatever style the host platform happens to prefer.
    QQuickStyle::setStyle("Basic");

    QGuiApplication app(argc, argv);
    app.setApplicationName("Family Tree Management System");
    app.setOrganizationName("COMSATS University Islamabad");

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(QUrl(QStringLiteral("qrc:/FamilyTreeQt/qml/main.qml")));

    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
