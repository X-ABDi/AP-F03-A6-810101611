#include "global.hpp"
#include "reserve.hpp"

struct table{
    int table_id;
    bool reserved;
};

class resturan{
    std::map<std::string, int> menu;
    std::string restrict;
    std::vector<rest_reserve*> reserves;
    std::pair<int, int> working_time;
    std::vector<table*> tables;

    public:

};