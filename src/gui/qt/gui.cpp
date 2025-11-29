#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gui/qt/gui.hpp"

namespace gui::qt 
{

UserInterface::UserInterface(const ::std::string &fl)
: qml_file(fl)    
{
    
}

bool UserInterface::Initialize() const
{
    int argc = 0;
    QGuiApplication app(argc, nullptr);
    QQmlApplicationEngine engine;

    const QUrl url(QString(qml_file.c_str()));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    app.exec();

    return true;
}

bool UserInterface::Stop() const
{
    return true;
}

}