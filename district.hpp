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
        std::string get_district(std::string district_name);
        std::string get_all_districts();
        std::string district::split_resturan_request(std::string food_name, std::queue<std::pair<std::string,std::vector<std::string>*>> &my_q,
                                                std::map<std::string, bool> &checked);
        std::string get_all_resturans(std::string &respond, std::pair<std::string, std::vector<std::string>*> dis_pair);
        std::string get_resturans_by_food(std::string &respond, std::pair<std::string, std::vector<std::string>*> dis_pair, std::string food_name);
        std::string get_resturans(std::string user_district, std::string food_name);
        friend class software;
};