#include "global.hpp"
#include "resturan.hpp"
#include "user.hpp"
#include "restrict.hpp"
#include "error.hpp"

class software
{
    std::map<std::string, user*> all_users;
    std::map<std::string, resturan*> all_resturans;
    restrict restricts;
    user* current_user;
    public:
    software();
    ~software();
    void resturan_init (std::vector<std::string> rest_prop);
    void restrict_init (std::vector<std::string> rest_prop);
    friend class process;
};