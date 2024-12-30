#include "global.hpp"
#include "error.hpp"

class district
{
    std::map<std::string, std::vector<std::string>*> district_neighbors;
    std::map<std::string, std::vector<std::string>*> district_resturans;
    public:
        district();
        void set_neighbors (std::vector<std::string> properties);
        void set_resturans (std::string district, std::string resturan);
        std::string get_district(std::string district_name);
        std::string get_all_districts();
        friend class software;
};