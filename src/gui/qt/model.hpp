#pragma once

#include <type_traits>

#include <QString>
#include <QAbstractListModel>

namespace gui::qt 
{

namespace staff {
    
    struct Data
    {
        const QString imagePath;
        const QString firstName;
        const QString lastName;
        const QString role;
        const QString description;
    };

    class Model : public QAbstractListModel 
    {
        Q_OBJECT

        public:

            enum class Roles : std::underlying_type_t<Qt::ItemDataRole> 
            {
                IMAGE = Qt::UserRole + 1,
                FIRST_NAME,
                LAST_NAME,
                ROLE,
                DESCRIPTION,

                NUM
            };
            Q_ENUM(Roles)

            Model(QObject *parent = nullptr);

            virtual ~Model() = default;

            void AddPerson(const Data &data);

            int rowCount(const QModelIndex &parent = QModelIndex()) const;

            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        protected:
            QHash<int, QByteArray> roleNames() const;
        private:
            QList<Data> staff;
    };
}

}