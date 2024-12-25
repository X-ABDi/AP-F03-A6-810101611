#include "global.hpp"
#include <regex>
#include "reserve.hpp"

struct table{
    int table_id;
    bool reserved;
};

class resturan{
    std::string name;
    std::map<std::string, int> menu;
    std::string restrict;
    std::vector<rest_reserve*> reserves;
    std::pair<int, int> working_time;
    std::vector<table*> tables;

    public:
    ~resturan();
    void set_menu (std::string);
    void set_tables (std::string);

    friend class software;
};