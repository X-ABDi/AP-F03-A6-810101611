#ifndef __SOFTWARE__
#define __SOFTWARE__

#include "global.hpp"
#include <algorithm>
#include "resturan.hpp"
#include "user.hpp"
#include "district.hpp"
#include "discount.hpp"
#include "reserve.hpp"
#include "error.hpp"

class software
{
    std::shared_ptr<std::map<std::string, std::shared_ptr<user>>> all_users;
    std::shared_ptr<std::map<std::string, resturan*>> all_resturans;
    district districts;
    std::shared_ptr<user> current_user;
    public:
    software();
    software(std::shared_ptr<software> soft_obj);
    ~software();
    bool logged_in ();
    void set_district (std::string);
    void delete_reserve (std::vector<std::string> &command_entered);
    void sort_reserves_by_times(resturan*, std::pair<std::string, table *>&, std::vector<std::pair<std::string,rest_reserve*>>&);
    void get_budget(std::string &respond);
    void resturan_detail_tables(std::string resturan_name, std::string &respond);
    void resturan_detail_discounts(std::string resturan_name, std::string &respond);
    void get_district(std::string_view, std::string &respond);
    void get_all_districts(std::string &respond);
    void get_resturans(std::string food_name, std::string &respond);
    void get_resturan_detail(std::string, std::string &respond);
    void get_reserves(std::vector<std::string> &command_entered, std::string &respond);
    void get_all_reserves(std::string &respond);
    void get_resturan_reserves(std::vector<std::string> &command_entered, std::string &respond);
    void get_resturan_one_reserve(std::vector<std::string> &command_entered, std::string &respond);
    void signup(std::vector<std::string> &command_entered);
    void login(std::vector<std::string> &command_entered);
    void logout();
    void reserve(std::vector<std::string> &command_entered, std::string &respond);
    void set_reserve(std::vector<std::string> &command_entered,std::map<std::string, std::pair<float, int>> &foods, std::map<std::string, resturan*>::iterator &map_it, std::string &respond);
    std::string calculate_specific_discounts (std::map<std::string, std::pair<float, int>> &foods, std::map<std::string, resturan*>::iterator &map_it);
    std::string calculate_first_discount (std::string price, std::map<std::string, resturan*>::iterator &map_it);
    std::string calculate_order_discount (std::string price, std::map<std::string, resturan*>::iterator &map_it);
    void increase_budget(std::vector<std::string> &command_entered, std::string &respond);
    void resturan_init (std::vector<std::string>&);
    void district_init (std::vector<std::string>&);
    void discount_init (std::vector<std::string>&);


    friend class process;
};

#endif