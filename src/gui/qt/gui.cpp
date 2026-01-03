#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "gui/qt/gui.hpp"
#include "gui/qt/model.hpp"

namespace gui::qt 
{

UserInterface::UserInterface(const ::std::string &fl, const ::std::string &s_p)
: qml_file(fl), image_staff_path(s_p)    
{
    
}

bool UserInterface::Initialize(const std::vector<std::vector<std::string>> &staff) const
{
    int argc = 0;
    QGuiApplication app(argc, nullptr);
    QQmlApplicationEngine engine;

    static gui::qt::staff::Model staffModel;

    for (const auto& person : staff)
    {
        assert(5 == person.size());
        const std::string full_image_path = "file:///" + image_staff_path + "/" + person[0].c_str();
        staffModel.AddPerson({full_image_path.c_str(), 
                                person[1].c_str(), person[2].c_str(), person[3].c_str(), person[4].c_str()});
    }

    engine.rootContext()->setContextProperty("staffModel", &staffModel);

    const QUrl url(QString(qml_file.c_str()));

    engine.load(url);
    if (engine.rootObjects().isEmpty())
        return -1;

    app.exec();

    return true;
}

bool UserInterface::Start() const
{
    return true;
}

bool UserInterface::Stop() const
{
    return true;
}

bool UserInterface::Update() const
{
    return true;
}

}