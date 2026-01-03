#include "opts.hpp"

#include "gui/qt/gui.hpp"

#include "db/sqlite3/op.hpp"
#include "db/sqlite3/db.hpp"

int main(int argc, char *argv[])
{
    static constexpr std::string DB_FILE_NAME{"/vet.db"};

    static constexpr std::string DB_IMAGE_PATH{"/images"};
    static constexpr std::string DB_IMAGE_STAFF_PATH{DB_IMAGE_PATH + "/staff"};


    const auto opts(vetassistant::Opts::Parse(argc, argv));
    
    const std::string images_path =  opts.db + DB_IMAGE_STAFF_PATH;
    const gui::qt::UserInterface user_interface(opts.qml_file, images_path);

    const std::string db_file = opts.db + DB_FILE_NAME;
    db::sqlite3::DbR db(db_file);
    db.Connect();

    constexpr db::sqlite3::OpR op;
    constexpr auto request = op.Read(iso::string::string<"staff">, 
                                                iso::string::string<"image">,
                                                iso::string::string<"name_first">,
                                                iso::string::string<"name_last">,
                                                iso::string::string<"role">,
                                                iso::string::string<"description">);
    const auto staff = db.Read(request);

    user_interface.Initialize(staff);

    return 0;
}