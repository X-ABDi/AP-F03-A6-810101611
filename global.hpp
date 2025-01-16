#ifndef __GLOBAL__
#define __GLOBAL__

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <span>

#define OK "OK"
#define NONE "none"
#define ZERO 0
#define ZERO_STR "0"
#define EMPTY_STRING ""
#define DOUBLE_QUOTE '\"'
#define QUESTION_MARK "?"
#define SEMI_COLON ';'
#define COLON_CHAR ':'

const std::string_view OK_VIEW = OK;
const std::string_view NONE_VIEW = NONE;
const std::string_view EMPTY_STRING_VIEW = EMPTY_STRING;
const std::string_view QUESTION_MARK_VIEW = QUESTION_MARK;
// const std::string_view SEMI_COLON_VIEW = SEMI_COLON;
// const std::span<std::char> DOUBLE_QUOTE_VIEW (&DOUBLE_QUOTE, 1);

namespace error_message{
    const std::string_view EMPTY = "Empty";
    const std::string_view NOT_FOUND = "Not Found";
    const std::string_view BAD_REQUEST = "Bad Request";
    const std::string_view PERMISSION_DENIED = "Permission Denied";
    const std::string_view STRING_CORRUPTED = "String Corrupted";
}

namespace main_command{
    const std::string_view GET = "GET";
    const std::string_view PUT = "PUT";
    const std::string_view POST = "POST";
    const std::string_view DELETE = "DELETE";
}

namespace sub_command_post{
    const std::string_view SIGNUP = "signup";
    const std::string_view USERNAME = "username";
    const std::string_view PASSWORD = "password";
    const std::string_view LOGIN = "login";
    const std::string_view LOGOUT = "logout";
    const std::string_view RESERVE = "reserve";
    const std::string_view RESTAURANT_NAME = "restaurant_name";
    const std::string_view TABLE_ID = "table_id";
    const std::string_view START_TIME = "start_time";
    const std::string_view END_TIME = "end_time";
    const std::string_view FOODS = "foods";
    const std::string_view RESERVE_ID = "reserve_id";
    const std::string_view INCREASE_BUDGET = "increase_budget";
    const std::string_view AMOUNT = "amount";
}

namespace sub_command_get{
    const std::string_view DISTRICTS = "districts";
    const std::string_view DISTRICT = "district";
    const std::string_view RESTAURANTS = "restaurants";
    const std::string_view FOOD_NAME = "food_name";
    const std::string_view RESTAURANT_DETAIL = "restaurant_detail";
    const std::string_view RESTAURANT_NAME = "restaurant_name";
    const std::string_view RESERVES = "reserves";
    const std::string_view RESERVE_ID = "reserve_id";
    const std::string_view SHOW_BUDGET = "show_budget";
}

namespace sub_command_put{
    const std::string_view MY_DISTRICT = "my_district";
    const std::string_view DISTRICT = "district";
}

namespace sub_command_delete{
    const std::string_view RESERVE = "reserve";
    const std::string_view RESTAURANT_NAME = "restaurant_name";
    const std::string_view RESERVE_ID = "reserve_id";
}

namespace discount_type{
    const std::string_view PERCENT = "percent";
    const std::string_view AMOUNT = "amount";
    const float RETURN_PERCENT = float(3)/5;
}

namespace output_common{
    const std::string_view COLON = ": ";
    const std::string_view NEW_LINE = "\n";
    const std::string_view COMMA = ", ";
    const std::string_view SPACE = " "; 
    const std::string_view HYPHEN = "-";
    const std::string_view PARANTHESE_OPEN = "(";
    const std::string_view PARANTHESE_CLOSE = ")";
}

namespace output_get{
    const std::string_view RESTURAN_NAME = "Name: ";
    const std::string_view RESTURAN_DISTRICT = "District: ";
    const std::string_view RESTURAN_TIME = "Time: ";
    const std::string_view RESTURAN_MENU = "Menu: ";
    const std::string_view RESTURAN_ORDER_DISCOUNT = "Order Amount Discount: ";
    const std::string_view RESTURAN_ITEM_DISCOUNT = "Item Specific Discount: ";
    const std::string_view RESTURAN_FIRST_DISCOUNT = "First Order Discount: ";
}

namespace output_post{
    const std::string_view RESERVE_ID = "Reserve ID: ";
    const std::string_view RESERVE_TABLE_1 = "Table ";
    const std::string_view RESERVE_TABLE_2 = " for ";
    const std::string_view RESERVE_TABLE_3 = " to ";
    const std::string_view RESERVE_TABLE_4 = " in ";
    const std::string_view RESERVE_ORIGINAL_PRICE = "Original Price: ";
    const std::string_view RESERVE_ORDER_DISCOUNT = "Order Amount Discount: ";
    const std::string_view RESERVE_ITEM_DISCOUNT = "Total Item Specific Discount: ";
    const std::string_view RESERVE_FIRST_DISCOUNT = "First Order Discount: ";
    const std::string_view RESERVE_TOTAL_DISCOUNT = "Total Discount: ";
    const std::string_view RESERVE_TOTAL_PRICE = "Total Price: ";
}

#endif