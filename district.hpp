#ifndef __DISTRICT__
#define __DISTRICT__

#include "global.hpp"
#include "error.hpp"
#include "resturan.hpp"
#include "queue"

class district
{
    std::map<std::string, std::vector<std::string>*> district_neighbors;
    std::map<std::string, std::vector<resturan*>*> district_resturans;
    public:
        district();
        ~district();
        void set_neighbors (std::vector<std::string> properties);
        void set_resturans (std::string district, resturan* new_resturan);
        bool user_district_check (std::string);
        void get_district(std::string_view district_name, std::string &respond);
        void get_all_districts(std::string &respond);
        void split_resturan_request(std::string &food_name, std::queue<std::pair<std::string,std::vector<std::string>*>> &my_q,
                                                std::map<std::string, bool> &checked);
        void get_all_resturans(std::string &respond, std::pair<std::string, std::vector<std::string>*> &dis_pair);
        void get_resturans_by_food(std::string &respond, std::pair<std::string, std::vector<std::string>*> &dis_pair, std::string &food_name);
        void get_resturans(std::string_view user_district, std::string &food_name, std::string &respond);
        friend class software;
};

#endif