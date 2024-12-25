#include "global.hpp"

class restrict
{
    std::map<std::string, std::vector<std::string>*> restrict_neighbors;
    std::map<std::string, std::vector<std::string>*> restrict_resturans;
    public:
        restrict();
        void set_neighbors (std::vector<std::string> properties);
        void set_resturans (std::string restrict, std::string resturan);
};