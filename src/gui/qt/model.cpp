#include "gui/qt/model.hpp"

using namespace gui::qt;

staff::Model::Model(QObject *parent) : QAbstractListModel(parent)
{

}

void staff::Model::AddPerson(const Data &data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    staff << data;
    endInsertRows();
}

int staff::Model::rowCount(const QModelIndex &) const 
{
    return staff.count();
}

QVariant staff::Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= staff.size())
    {
        return {};
    }

    const auto &p = staff.at(index.row());

    switch (auto r = static_cast<Roles>(role); r) 
    {
        case Roles::IMAGE: 
            return p.imagePath;
        case Roles::FIRST_NAME: 
            return p.firstName;
        case Roles::LAST_NAME: 
            return p.lastName;
        case Roles::ROLE:
            return p.role;
        case Roles::DESCRIPTION: 
            return p.description;
        default:
            break;
    }

    return {};
}

QHash<int, QByteArray> staff::Model::roleNames() const
{
    return {
        { static_cast<std::underlying_type_t<Roles>>(Roles::IMAGE), "imagePath" },
        { static_cast<std::underlying_type_t<Roles>>(Roles::FIRST_NAME), "firstName" },
        { static_cast<std::underlying_type_t<Roles>>(Roles::LAST_NAME), "lastName" },
        { static_cast<std::underlying_type_t<Roles>>(Roles::ROLE), "role" },
        { static_cast<std::underlying_type_t<Roles>>(Roles::DESCRIPTION), "description" }
    };
}