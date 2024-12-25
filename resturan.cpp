#include "resturan.hpp"

resturan::~resturan()
{
    for (auto i : reserves)
    {
        delete i;
    } 
    for (auto i : tables)
    {
        delete i;
    }
}

void resturan::set_menu (std::string raw_menu)
{
    std::regex re(";"); 
    std::sregex_token_iterator it(raw_menu.begin(), raw_menu.end(), re, -1);
    std::sregex_token_iterator end;
    
    std::vector<std::string> tokens;
    for (; it != end; ++it) {
        tokens.push_back(it->str());
    }
    for (auto i : tokens)
    {
        size_t pos = i.find(":");
        menu[i.substr(0, pos)] = stoi(i.substr(pos+1));
    }
}

void resturan::set_tables (std::string table_number)
{
    for (int i=0; i<stoi(table_number); i++)
    {
        table* new_table = new table;
        new_table->table_id = i+1;
        new_table->reserved = false;
    }
}
