#include <sstream>
#include <regex>
#include "process.hpp"

process::process()
{
}

std::vector<std::string> commands = {main_command::GET, main_command::POST, main_command::PUT, main_command::DELETE};

bool double_qoute_error (std::string input)
{
    if (input == "" || input[0] != '\"' || input[input.length()-1] != '\"')
        return true;
    input = input.substr(1, input.length()-2);
    if (input == "")
        return true;    
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
    std::regex re(",\\s*"); 
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

void process::parse_sub_get(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (find(sub_comma_get.begin(), sub_comma_get.end(), input) == sub_comma_get.end())
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);
    ss >> input;
    if (input != "?")
        throw errors(error_message::BAD_REQUEST);
    if (command_entered[1] == sub_command_get::RESTAURANTS)
        parse_get_resturants(command_entered, ss);
    else if (command_entered[1] == sub_command_get::RESTAURANT_DETAIL)
        parse_get_restdetail(command_entered, ss);
    else if (command_entered[1] == sub_command_get::DISTRICTS)
        parse_get_district(command_entered, ss);  
    else if (command_entered[1] == sub_command_get::RESERVES)
        parse_get_reserves(command_entered, ss);                  
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
    if (input != "?")
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

void process::parse_sub_post(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    std::string input;
    ss >> input;
    if (find(sub_comma_post.begin(), sub_comma_post.end(), input) == sub_comma_post.end())
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);    
    ss >> input;    
    if (input != "?" )
        throw errors(error_message::BAD_REQUEST);
    if (command_entered[1] == sub_command_post::LOGOUT)
        return;
    else if (command_entered[1] == sub_command_post::SIGNUP)
        parse_post_signup(command_entered, ss);
    else if (command_entered[1] == sub_command_post::LOGIN)
        parse_post_login(command_entered, ss);
    else if (command_entered[1] == sub_command_post::RESERVE)
        parse_post_reserve(command_entered, ss);
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
    if (input != "?")
        throw errors(error_message::BAD_REQUEST);
    if (command_entered[1] == sub_command_delete::RESERVE)
        parse_delete_reserve(command_entered, ss);      
}

void process::parse_sub_command(std::vector<std::string> &command_entered, std::stringstream &ss)
{
    if (std::find(main_commands.begin(), main_commands.end(), command_entered[0]) == command_entered.end())
        throw errors(error_message::BAD_REQUEST);
    if(command_entered[0] == main_command::GET)
        parse_sub_get(command_entered, ss);
    else if(command_entered[0] == main_command::PUT)
        parse_sub_put(command_entered, ss);
    else if(command_entered[0] == main_command::POST)
        parse_sub_post(command_entered, ss);
    else if(command_entered[0] == main_command::DELETE)
        parse_sub_delete(command_entered, ss);     

}

std::vector<std::string> process::parse_command(std::string input)
{
    std::vector<std::string> command_entered;
    std::stringstream ss = std::stringstream();
    ss << input;
    ss >> input;
    if(find(main_commands.begin(), main_commands.end(), input) == main_commands.end())
        throw errors(error_message::BAD_REQUEST);
    command_entered.push_back(input);
    parse_sub_command(command_entered, ss);
    return command_entered;
}

void process::resturan_init (char *resturan_file)
{
    std::ifstream properties(resturan_file);
    if (!properties.is_open())
    {
        std::cerr << "trouble opening file" << std::endl;
        return;
    } 
    std::string line;
    std::vector<std::string> rest_prop;
    while(getline(properties, line))
    {
        rest_prop = parse_line (line);
        UTaste.resturan_init (rest_prop);
    }
}

void process::district_init (char *restrict_file)
{
    std::ifstream properties(restrict_file);
    if (!properties.is_open())
    {
        std::cerr << "trouble opening file" << std::endl;
        return;
    } 
    std::string line;
    std::vector<std::string> rest_prop;
    std::vector<std::string> neighbors;
    while(getline(properties, line))
    {
        rest_prop = parse_line (line);
        neighbors = parse_neighbor(rest_prop[1]);
        rest_prop.erase(rest_prop.begin()+1);
        rest_prop.insert(rest_prop.end(), neighbors.begin(), neighbors.end());
        UTaste.district_init (rest_prop);
    }
}

void process::begin(std::vector<std::string> &command_entered)
{
    std::string input;
    std::cin >> input;
    
    try
    {
        command_entered = parse_command(input);
    }
    catch (errors &e)
    {
        e.printError();
    }
    
}