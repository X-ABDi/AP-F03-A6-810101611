#include "global.hpp"
#include "resturan.hpp"
#include "user.hpp"
#include "restrict.hpp"

class software
{
    std::map<std::string, user*> all_users;
    std::map<std::string, resturan*> all_resturans;
    restrict restricts;
    user* current_user;
    public:

};