#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <sqlite3.h>

#include "db/db.hpp"
#include "db/sqlite3/op.hpp"

namespace db::sqlite3
{

class DbR
{
    public:
        using Cell  =  std::string;
        using Row   =  std::vector<Cell>;
        using Table =  std::vector<Row>;
        

        DbR(const ::std::string& fl) : db_file(fl), db(nullptr)
        {

        }

        bool Connect() 
        {
            int rc = sqlite3_open(db_file.c_str(), &db);
            if (rc) 
            {
                std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            }
            return !rc;
        }

        template<iso::string::const_string Query>
        Table Read(const Query query) const
        {
            Table table;
            sqlite3_stmt* stmt;

            if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) 
            {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
                return table;
            }

            while (sqlite3_step(stmt) == SQLITE_ROW) 
            {
                int cols = sqlite3_column_count(stmt);
                Row row;
                for (int i = 0; i < cols; i++) 
                {
                    const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                    row.push_back(val ? val : "");
                }
                table.push_back(row);
            }

            sqlite3_finalize(stmt);

            return table;
        }
    
    private:
        static_assert(db::DbR<DbR>, "The DbR class should implement a whole concept interface!");

        const ::std::string &db_file;
        ::sqlite3* db;
};

} 