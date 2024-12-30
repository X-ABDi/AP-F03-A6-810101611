#include "global.hpp"
#include "resturan.hpp"
#include "user.hpp"
#include "district.hpp"
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
    std::string get_district(std::string);
    std::string get_all_districts();
    std::string get_resturans(std::string food_name);
    void resturan_init (std::vector<std::string> rest_prop);
    void district_init (std::vector<std::string> rest_prop);
    friend class process;
};