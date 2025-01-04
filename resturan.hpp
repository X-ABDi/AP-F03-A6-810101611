#ifndef __RESTURAN__
#define __RESTURAN__

#include "global.hpp"
#include <sstream>
#include <regex>
#include "reserve.hpp"
#include "discount.hpp"

struct table{
    std::string table_id;
    std::vector<std::string> reseve_ids;
    bool reserved;
};

class resturan{
    std::string name;
    std::map<std::string, std::pair<float, specific_food_discount*>> menu;
    std::string district;
    bool food_discount;
    total_price_discount total_dis;
    first_order_discount first_dis;
    std::map<std::string,rest_reserve*> reserves;
    std::pair<std::string, std::string> working_time;
    std::map<std::string,table*> tables;
    int last_reserve_id;

    public:
    // ~resturan();
    void set_menu (std::string);
    void set_tables (std::string);
    void set_total_dis(std::string);
    void set_first_dis (std::string);
    void set_food_dis (std::string);
    void put_in_menu (specific_food_discount*);
    std::string get_discounts_detail();

    friend class software;
    friend class district;
};

#endif