#pragma once

#include "db/op.hpp"

namespace db::sqlite3
{

//TODO: OpW and OpRW

/**
 * @brief Read operation for sqllite3
 * 
 */
class OpR
{
    public:
        consteval OpR() {}

        template<iso::string::const_string Table, iso::string::const_string First, iso::string::const_string ...Rest>
        consteval iso::string::const_string auto Read(const Table table, const First first, const Rest ...rest) const 
                                            -> decltype(iso::string::string<"SELECT"> + iso::string::string<" "> 
                                                        + (first + ((iso::string::string<", "> + rest) + ...) + iso::string::string<" ">) 
                                                        + iso::string::string<"FROM"> + iso::string::string<" "> 
                                                        + table + iso::string::string<";">)
        {
            return {};
        }

    private:
        static_assert(db::OpR<OpR>, "The OpR class should implement a whole concept interface!");
};

}