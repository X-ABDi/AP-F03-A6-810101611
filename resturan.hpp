#include "global.hpp"
#include <regex>
#include "reserve.hpp"

struct table{
    std::string table_id;
    std::vector<std::string> reseve_ids;
    bool reserved;
};

class resturan{
    std::string name;
    std::map<std::string, std::string> menu;
    std::string district;
    std::map<std::string,rest_reserve*> reserves;
    std::pair<std::string, std::string> working_time;
    std::map<std::string,table*> tables;
    std::string last_reserve_id;

    public:
    ~resturan();
    void set_menu (std::string);
    void set_tables (std::string);

    friend class software;
    friend class district;
};