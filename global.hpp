#ifndef __GLOBAL__
#define __GLOBAL__

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

#define OK "OK"

namespace error_message{
    const std::string EMPTY = "Empty";
    const std::string NOT_FOUND = "Not Found";
    const std::string BAD_REQUEST = "Bad Request";
    const std::string PERMISSION_DENIED = "Permission Denied";
    const std::string STRING_CORRUPTED = "String Corrupted";
}

namespace main_command{
    const std::string GET = "GET";
    const std::string PUT = "PUT";
    const std::string POST = "POST";
    const std::string DELETE = "DELETE";
}

namespace sub_command_post{
    const std::string SIGNUP = "signup";
    const std::string USERNAME = "username";
    const std::string PASSWORD = "password";
    const std::string LOGIN = "login";
    const std::string LOGOUT = "logout";
    const std::string RESERVE = "reserve";
    const std::string RESTAURANT_NAME = "restaurant_name";
    const std::string TABLE_ID = "table_id";
    const std::string START_TIME = "start_time";
    const std::string END_TIME = "end_time";
    const std::string FOODS = "foods";
    const std::string RESERVE_ID = "reserve_id";
}

namespace sub_command_get{
    const std::string DISTRICTS = "districts";
    const std::string DISTRICT = "district";
    const std::string RESTAURANTS = "restaurants";
    const std::string FOOD_NAME = "food_name";
    const std::string RESTAURANT_DETAIL = "restaurant_detail";
    const std::string RESTAURANT_NAME = "restaurant_name";
    const std::string RESERVES = "reserves";
    const std::string RESERVE_ID = "reserve_id";
}

namespace sub_command_put{
    const std::string MY_DISTRICT = "my_district";
    const std::string DISTRICT = "district";
}

namespace sub_command_delete{
    const std::string RESERVE = "reserve";
    const std::string RESTAURANT_NAME = "restaurant_name";
    const std::string RESERVE_ID = "reserve_id";
}

#endif