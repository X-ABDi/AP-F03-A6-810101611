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
    std::map<std::string, user*>* all_users;
    std::map<std::string, resturan*>* all_resturans;
    district districts;
    user* current_user;
    public:
    software();
    ~software();
    bool logged_in ();
    void set_district (std::string);
    void delete_reserve (std::vector<std::string> &command_entered);
    std::vector<std::pair<std::string,rest_reserve*>> sort_reserves_by_times(resturan*, std::pair<std::string, table *>);
    std::string resturan_detail_tables(std::string resturan_name);
    std::string get_district(std::string);
    std::string get_all_districts();
    std::string get_resturans(std::string food_name);
    std::string get_resturan_detail(std::string);
    std::string get_reserves(std::vector<std::string> &command_entered);
    std::string get_all_reserves();
    std::string get_resturan_reserves(std::vector<std::string> &command_entered);
    std::string get_resturan_one_reserve(std::vector<std::string> &command_entered);
    void signup(std::vector<std::string> &command_entered);
    void login(std::vector<std::string> &command_entered);
    void logout();
    std::string reserve(std::vector<std::string> &command_entered);
    std::string set_reserve(std::vector<std::string> &command_entered,std::map<std::string, std::pair<int, int>> &foods, std::map<std::string, resturan*>::iterator &map_it);
    std::string increase_budget(std::vector<std::string> &command_entered);
    void resturan_init (std::vector<std::string>);
    void district_init (std::vector<std::string>);
    void discount_init (std::vector<std::string>);


    friend class process;
};

#endif