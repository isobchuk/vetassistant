#pragma once

#include <string>

namespace vetassistant
{

class Opts final 
{
    private:
        static constexpr std::string QML_FILE_DEFAULT{"ui.qml"};
        static constexpr std::string DB_DEFAULT{"./"}; 

        enum class Option
        {
            QML_FILE,
            DB,

            NUM
        };
        static constexpr std::string OPTIONS_LIST[] = { 
            "--qml-file",
            "--db"
        };
    
    public:
        const int argc;
        const char **argv;

        const std::string qml_file;
        const std::string db;

        constexpr Opts(const int _argc, char *_argv[], const std::string qml_fl, const std::string d_b) : 
            argc(_argc), 
            argv(const_cast<decltype(argv)>(_argv)), 
            qml_file(qml_fl), 
            db(d_b) 
        {

        }

        static void Usage()
        {

        } 

        [[nodiscard]] static Opts Parse(int argc, char *argv[]) 
        {
            std::string _qml_file;
            std::string _db;

            // Check that we have arguments
            constexpr decltype(argc) ARGC_MINIMAL = 1;
            if (argc <= 1)
            {
                return Opts(argc, argv, QML_FILE_DEFAULT, DB_DEFAULT);
            }
            
            // Parse
            for (decltype(argc) i = ARGC_MINIMAL; i < argc; i++)
            {
                using OptionUnderlying = std::underlying_type_t<Option>;
                if (OPTIONS_LIST[static_cast<OptionUnderlying>(Option::QML_FILE)] == argv[i - ARGC_MINIMAL])
                {
                    if (++i - ARGC_MINIMAL < argc)
                    {
                        _qml_file = argv[i - ARGC_MINIMAL];
                    }
                    else
                    {
                        Usage();
                    }
                }
                else if (OPTIONS_LIST[static_cast<OptionUnderlying>(Option::DB)] == argv[i - ARGC_MINIMAL])
                {
                    if (++i - ARGC_MINIMAL < argc)
                    {
                        _db = argv[i - ARGC_MINIMAL];
                    }
                    else
                    {
                        Usage();
                    }
                }
                else
                {
                    Usage();
                }
            }

            return Opts(argc, argv, _qml_file, _db);
        }
};    
}