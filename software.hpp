#include "global.hpp"
#include <algorithm>
#include "resturan.hpp"
#include "user.hpp"
#include "district.hpp"
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
    std::vector<std::pair<std::string,rest_reserve*>> sort_reserves_by_times(resturan*, std::pair<std::string, table *>);
    std::string resturan_detail_tables(std::string resturan_name);
    std::string get_district(std::string);
    std::string get_all_districts();
    std::string get_resturans(std::string food_name);
    std::string get_resturan_detail(std::string);
    void resturan_init (std::vector<std::string> rest_prop);
    void district_init (std::vector<std::string> rest_prop);
    friend class process;
};