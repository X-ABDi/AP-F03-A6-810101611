#include <sstream>
#include <regex>
#include "process.hpp"

process::process(process &process_obj) 
{
    // std::cout << "process constructor with argument" << std::endl;
    UTaste = process_obj.UTaste;
}

process::process() : UTaste(std::make_shared<software>())
{
    // std::cout << "process constructor without argument" << std::endl;
    // std::cout << UTaste->current_user->get_wallet() << std::endl;
}

std::vector<std::string_view> process::main_commands = {main_command::GET, main_command::POST, main_command::PUT, main_command::DELETE};
std::vector<std::string_view> process::sub_comma_get = {sub_command_get::DISTRICTS, sub_command_get::RESTAURANTS, sub_command_get::RESTAURANT_DETAIL, sub_command_get::RESERVES, sub_command_get::SHOW_BUDGET};
std::vector<std::string_view> process::sub_comma_put = {sub_command_put::MY_DISTRICT};
std::vector<std::string_view> process::sub_comma_post = {sub_command_post::LOGIN, sub_command_post::LOGOUT, sub_command_post::RESERVE, sub_command_post::SIGNUP, sub_command_post::INCREASE_BUDGET};
std::vector<std::string_view> process::sub_comma_delete = {sub_command_delete::RESERVE};

std::string process::pro_get (std::vector<std::string> &command_entered){}
std::string process::pro_put (std::vector<std::string> &command_entered){}
std::string process::pro_post (std::vector<std::string> &command_entered){}
std::string process::pro_delete (std::vector<std::string> &command_entered){} 

bool double_qoute_error (std::string input)
{
    if (input == EMPTY_STRING_VIEW || input[0] != DOUBLE_QUOTE || input[input.length()-1] != DOUBLE_QUOTE)
        return true;
    input = input.substr(1, input.length()-2);
    if (input == EMPTY_STRING_VIEW)
        return true;  
    return false;      
}

bool is_not_int (std::string input)
{
    for (char c : input)
        if (!isdigit(c))
            return true;
    return false;        
}

std::vector<std::string> process::parse_line (std::string line) 
{
    std::regex re(","); 
    std::sregex_token_iterator it(line.begin(), line.end(), re, -1);
    std::sregex_token_iterator reg_end;

    std::vector<std::string> result(it, reg_end);
    return result;
}

std::vector<std::string> process::parse_neighbor (std::string line)
{
    std::regex re(";");
    std::sregex_token_iterator it(line.begin(), line.end(), re, -1);
    std::sregex_token_iterator reg_end;

    std::vector<std::string> result(it, reg_end);
    return result;
} 

void parse_get_resturants(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_get::FOOD_NAME)
        return;
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);        
}

void parse_get_restdetail(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;    
    if (input != sub_command_get::RESTAURANT_NAME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);        
}

void parse_get_district(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_get::DISTRICT)
        return;
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);    
}

void parse_get_reserves (std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_get::RESTAURANT_NAME)
        return;
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_get::RESERVE_ID)
        return;
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);                
}

void parse_get_budget (std::vector<std::string> &command_entered, std::stringstream &ss)
{
    return;
}

void process::parse_sub_get(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (find(sub_comma_get.begin(), sub_comma_get.end(), input) == sub_comma_get.end())
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);
    ss >> input;
    if (input != QUESTION_MARK_VIEW)
        throw errors(error_message::BAD_REQUEST);
    if (command_entered[1] == sub_command_get::RESTAURANTS)
        parse_get_resturants(command_entered, ss);
    else if (command_entered[1] == sub_command_get::RESTAURANT_DETAIL)
        parse_get_restdetail(command_entered, ss);
    else if (command_entered[1] == sub_command_get::DISTRICTS)
        parse_get_district(command_entered, ss);  
    else if (command_entered[1] == sub_command_get::RESERVES)
        parse_get_reserves(command_entered, ss);  
    else if (command_entered[1] == sub_command_get::SHOW_BUDGET)
        parse_get_budget(command_entered, ss);                   
}

void parse_put_district(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_put::DISTRICT)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);        
}

void process::parse_sub_put(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (find(sub_comma_put.begin(), sub_comma_put.end(), input) == sub_comma_put.end())
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);    
    ss >> input;
    if (input != QUESTION_MARK_VIEW)
        throw errors(error_message::BAD_REQUEST);
    if (command_entered[1] == sub_command_put::MY_DISTRICT)
        parse_put_district(command_entered, ss);    
}

void process::parse_post_signup (std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_post::USERNAME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);    
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_post::PASSWORD)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);    
    command_entered.push_back(input);
}

void process::parse_post_login (std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_post::USERNAME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);    
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_post::PASSWORD)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);    
    command_entered.push_back(input);
}

void process::parse_post_reserve (std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_post::RESTAURANT_NAME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_post::TABLE_ID)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    if (is_not_int(input))
        throw errors(error_message::BAD_REQUEST);  
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_post::START_TIME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    if (is_not_int(input))
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_post::END_TIME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    if (is_not_int(input))
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);
    ss >> input;
    if (input != sub_command_post::FOODS)
        return;
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    command_entered.push_back(input);                                
}

void parse_post_inc_budget(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_post::AMOUNT)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    if (is_not_int(input))
        throw errors(error_message::BAD_REQUEST);
    if (std::stoi(input) < 0)
        throw errors(error_message::BAD_REQUEST);    
    command_entered.push_back(input);     
}

void process::parse_sub_post(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (find(sub_comma_post.begin(), sub_comma_post.end(), input) == sub_comma_post.end())
        throw errors(error_message::BAD_REQUEST);    
    command_entered.push_back(input);  
    // std::cout << "pushed back sub command to vector: " << command_entered[1] << std::endl;  
    ss >> input;  
    if (input != QUESTION_MARK_VIEW)  
        throw errors(error_message::BAD_REQUEST);
    // std::cout << "checking command vector[1]" <<std::endl;    
    if (command_entered[1] == sub_command_post::LOGOUT)
        return;
    else if (command_entered[1] == sub_command_post::SIGNUP)
        parse_post_signup(command_entered, ss);
    else if (command_entered[1] == sub_command_post::LOGIN)
        parse_post_login(command_entered, ss);
    else if (command_entered[1] == sub_command_post::RESERVE)
        parse_post_reserve(command_entered, ss);
    else if (command_entered[1] == sub_command_post::INCREASE_BUDGET)
        parse_post_inc_budget(command_entered, ss);   
}

void parse_delete_reserve(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_delete::RESTAURANT_NAME)
        throw errors(error_message::BAD_REQUEST);
    ss >> input; 
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);    
    command_entered.push_back(input);       
    ss >> input;
    if (input != sub_command_delete::RESERVE_ID)
        throw errors(error_message::BAD_REQUEST);
    ss >> input;
    if (double_qoute_error(input))
        throw errors(error_message::BAD_REQUEST);
    input = input.substr(1, input.length()-2);
    if (is_not_int(input))
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);    
}

void process::parse_sub_delete(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (input != sub_command_delete::RESERVE)
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);    
    ss >> input;
    if (input != QUESTION_MARK_VIEW)
        throw errors(error_message::BAD_REQUEST);
    if (command_entered[1] == sub_command_delete::RESERVE)
        parse_delete_reserve(command_entered, ss);      
}

void process::parse_sub_command(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    if(command_entered[0] == main_command::GET)
        parse_sub_get(command_entered, ss);
    else if(command_entered[0] == main_command::PUT)
        parse_sub_put(command_entered, ss);
    else if(command_entered[0] == main_command::POST)
        parse_sub_post(command_entered, ss);
    else if(command_entered[0] == main_command::DELETE)
        parse_sub_delete(command_entered, ss);     
}

void process::parse_command(std::vector<std::string> &command_entered, std::string input)
{
    std::stringstream ss = std::stringstream();
    ss << input;
    ss >> input;
    // std::cout << input << std::endl;
    // for (auto i : main_commands)
    //     std::cout << i << std::endl;
    if(find(main_commands.begin(), main_commands.end(), input) == main_commands.end())
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);
    parse_sub_command(command_entered, ss);
}

void process::resturan_init (char *resturan_file)
{
    std::ifstream properties;
    std::string file = resturan_file;
    properties.open(file);
    if (!properties.is_open())
        throw errors("can not open file");
    std::string line;
    std::vector<std::string> rest_prop;
    while(getline(properties, line))
    {
        rest_prop = parse_line (line);
        UTaste->resturan_init (rest_prop);
    }
    properties.close();
}

void process::district_init (char *restrict_file)
{
    std::ifstream properties;
    std::string file = restrict_file;
    properties.open(file);
    if (!properties.is_open())
        throw errors("can not open file");
    std::string line;
    std::vector<std::string> rest_prop;
    std::vector<std::string> neighbors;
    while(getline(properties, line))
    {
        rest_prop = parse_line (line);
        if (rest_prop.size() > 1)
        {
            neighbors = parse_neighbor(rest_prop[1]);
            rest_prop.erase(rest_prop.begin()+1);
            rest_prop.insert(rest_prop.end(), neighbors.begin(), neighbors.end());
        }
        UTaste->district_init (rest_prop);
    }
    properties.close();
}

void process::discount_init (char *discount_file)
{
    std::ifstream properties(discount_file);
    if (!properties)
        throw errors("can not open file");
    std::string line;
    std::vector<std::string> discount_info;
    while(getline(properties, line))
    {
        discount_info = parse_line(line);
        UTaste->discount_init(discount_info);
    }
    properties.close();
}

void process::begin(std::vector<std::string> &command_entered)
{
    std::string input;
    getline(std::cin, input);
    try
    {
        parse_command(command_entered, input);
    }
    catch (errors &e)
    {
        e.printError();
    }
}