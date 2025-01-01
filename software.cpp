#include "software.hpp"

software::software()
{
    all_resturans = new std::map<std::string, resturan*>;
    all_users = new std::map<std::string, user*>;
    user* admin = new user("admin", "admin");
    current_user->logged_in = false;
}

software::~software()
{
    delete all_resturans;
    delete all_users;
}

bool software::logged_in()
{
    return current_user->logged_in;
}

void software::resturan_init (std::vector<std::string> rest_prop)
{
    resturan *new_resturan = new resturan;
    new_resturan->name = rest_prop[0];
    new_resturan->district = rest_prop[1];
    new_resturan->set_menu(rest_prop[2]);
    new_resturan->working_time.first = stoi(rest_prop[3]);
    new_resturan->working_time.second = stoi(rest_prop[4]);
    new_resturan->set_tables(rest_prop[5]);
    districts.set_resturans(rest_prop[1], new_resturan);
    (*all_resturans)[new_resturan->name] = new_resturan; 
}

void software::district_init (std::vector<std::string> rest_prop)
{
    district *new_district = new district;
    new_district->set_neighbors(rest_prop);
}

void software::set_district (std::string district_name)
{
    if (!districts.user_district_check(district_name))
        throw errors(error_message::NOT_FOUND);
    current_user->district = district_name;
}

void software::delete_reserve (std::vector<std::string> &command_entered)
{
    if ((*all_resturans).count(command_entered[2]) == 0)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves.count(command_entered[3]) == 0)  
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->username != current_user->username)
        throw errors(error_message::PERMISSION_DENIED);
    (*all_resturans)[command_entered[2]]->reserves.erase(command_entered[2]);
    (*current_user->reserves).erase(command_entered[3]); 
}

std::string software::get_district(std::string district_name)
{
    std::string respond;
    respond = districts.get_district(district_name);
    return respond;
}

std::string software::get_all_districts()
{
    std::string respond;
    if (districts.district_neighbors.size() == 0)
        throw errors(error_message::EMPTY);
    respond = districts.get_all_districts();  
    return respond;
}

std::string software::get_resturans(std::string food_name)
{
    std::string respond;
    if (current_user->district == "")
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans).size() == 0)
        throw errors(error_message::EMPTY);
    std::string user_district = current_user->district;    
    respond = districts.get_resturans(user_district, food_name);  
    if (respond == "")
        throw errors(error_message::EMPTY);
    return respond;    
}

std::vector<std::pair<std::string,rest_reserve*>> software::sort_reserves_by_times(resturan* my_resturan, std::pair<std::string, table *> i)
{
    std::vector<std::pair<std::string,rest_reserve*>> reserves;

    for (auto j : i.second->reseve_ids)
    {
        reserves.push_back((*my_resturan->reserves.find(j)));
    }
    sort(reserves.begin(), reserves.end(), [](std::pair<std::string, rest_reserve*> a, std::pair<std::string, rest_reserve*> b){return a.second->time_interval.first < b.second->time_interval.first;});
    return reserves;
}

std::string software::resturan_detail_tables(std::string resturan_name)
{
    std::string respond;
    std::vector<std::pair<std::string,rest_reserve*>> sorted_reserves;
    for (std::pair<std::string, table *> i : (*all_resturans)[resturan_name]->tables)
    {
        respond += i.first+": ";
        sorted_reserves = sort_reserves_by_times((*all_resturans)[resturan_name], i);
        for (auto j : sorted_reserves)
        {
            respond += "("+j.second->time_interval.first+'-'+j.second->time_interval.second+"), ";   
        }
        respond = respond.substr(0, respond.length()-2);
        respond += "\n";
    }
    return respond;
}

std::string software::get_resturan_detail(std::string resturan_name)
{
    if ((*all_resturans).count(resturan_name) == 0)
        throw errors(error_message::NOT_FOUND);
    std::string respond = "";
    respond += "Name: "+(*all_resturans)[resturan_name]->name+"\n";
    respond += "District: "+(*all_resturans)[resturan_name]->district+"\n";
    respond += "Time: "+(*all_resturans)[resturan_name]->working_time.first+'-'+(*all_resturans)[resturan_name]->working_time.second+"\n";
    respond += "Menu: ";
    for (auto i : (*all_resturans)[resturan_name]->menu)
        respond += i.first+"("+i.second+"), ";
    respond = respond.substr(0, respond.length()-2);
    respond += "\n";
    respond += resturan_detail_tables(resturan_name);
    return respond;
}

std::string software::get_all_reserves()
{
    std::string respond = "";
    for (auto i : (*current_user->reserves))
    {
        respond += i.second->reserve_id+": ";
        respond += i.second->resturan_name+" ";
        respond += i.second->table_id+" ";
        respond += i.second->time_interval.first+'-'+i.second->time_interval.second+" ";
        if (!i.second->foods.empty())
        {
            for (auto j : i.second->foods)
            {
                respond += j.first+"("+j.second.first+") ";
            }
        }
        respond += "\n";
    }
    return respond;
}

std::string software::get_resturan_reserves(std::vector<std::string> &command_entered)
{
    std::string respond="";
    if (find_if((*current_user->reserves).begin(), (*current_user->reserves).end(), [command_entered](std::pair<std::string, user_reserve*> a){return a.second->resturan_name == command_entered[2];}) == (*current_user->reserves).end())
        throw errors(error_message::EMPTY);
    for (auto i : (*current_user->reserves))
    {
        if (i.second->resturan_name == command_entered[2])
        {
            respond += i.second->reserve_id+": ";
            respond += i.second->resturan_name+" ";
            respond += i.second->table_id+" ";
            respond += i.second->time_interval.first+'-'+i.second->time_interval.second+" ";
            if (!i.second->foods.empty())
            {
                for (auto j : i.second->foods)
                {
                    respond += j.first+"("+j.second.first+") ";
                }
            }
            respond += "\n";
        }
    }
    return respond;
}

std::string software::get_resturan_one_reserve(std::vector<std::string> &command_entered)
{
    std::string respond="";
    if ((*all_resturans).count(command_entered[2]) == 0)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves.count(command_entered[3]) == 0)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->username != current_user->username)
        throw errors(error_message::PERMISSION_DENIED);
    respond += command_entered[3]+": ";
    respond += command_entered[2]+" ";
    respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->table_id+" ";
    respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->time_interval.first+'-';
    respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->time_interval.second+" ";
    if (!(*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->foods.empty())
    {
        for (auto i : (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->foods)
            respond += i.first+"("+i.second.first+") ";
    }   
    respond += "\n";        
    return respond;
}

std::string software::get_reserves(std::vector<std::string> &command_entered)
{
    std::string respond;
    if ((*current_user->reserves).empty())
        throw errors(error_message::EMPTY);
    if (command_entered.size() == 2)
        respond = get_all_reserves();
    if (command_entered.size() == 3)
        respond = get_resturan_reserves(command_entered); 
    if (command_entered.size() == 4)
        respond = get_resturan_one_reserve(command_entered);
    return respond;           
}

void software::signup(std::vector<std::string> &command_entered)
{
    std::map<std::string, user*>::iterator map_it;
    map_it = find_if((*all_users).begin(), (*all_users).end(), [command_entered](std::pair<std::string, user*> a){return a.first == command_entered[2];});
    if (map_it != (*all_users).end())
        if (map_it->second->password != command_entered[3])
            throw errors(error_message::BAD_REQUEST);
        else
            if (current_user->logged_in == true)
                throw errors(error_message::PERMISSION_DENIED);
            else
            {
                current_user = map_it->second;  
                current_user->logged_in = true;
            }      
    else
    {
        user* new_user = new user(command_entered[2], command_entered[3]);
        (*all_users)[command_entered[2]] = new_user;
    }
}

void software::login(std::vector<std::string> &command_entered)
{
    if (find_if((*all_users).begin(), (*all_users).end(), [command_entered](std::pair<std::string, user*> a){return a.second->username==command_entered[2];}) == (*all_users).end())
        throw errors(error_message::NOT_FOUND);
    std::map<std::string, user*>::iterator map_it;
    map_it = find_if((*all_users).begin(), (*all_users).end(), [command_entered](std::pair<std::string, user*> a){return a.second->username==command_entered[2];});
    if ((*map_it).second->password != command_entered[3])
        throw errors(error_message::PERMISSION_DENIED);
    if (current_user->logged_in == true)
        throw errors(error_message::PERMISSION_DENIED);
    current_user = (*map_it).second;
    current_user->logged_in = true;            
}

void software::logout()
{
    if (current_user->logged_in == false)
        throw errors(error_message::PERMISSION_DENIED);
    current_user->logged_in = false;    
}

std::map<std::string, std::pair<std::string, int>> parse_foods(std::string foods)
{
    std::map<std::string, std::pair<std::string, int>> food_vec;
    std::stringstream ss = std::stringstream();
    ss << foods;
    while (ss.good())
    {
        getline (ss, foods, ',');
        if (food_vec.count(foods) == 0)
            food_vec[foods] = {"", 1};
        else
            food_vec[foods].second += 1;    
    }
    return food_vec;
}

std::string calculate_price (std::map<std::string, std::pair<std::string, int>> &foods)
{
    int sum=0;
    for (auto i : foods)
        sum += std::stoi(i.second.first)*i.second.second;
    return std::to_string(sum);   
}

std::string software::set_reserve(std::vector<std::string> &command_entered, std::map<std::string, std::pair<std::string, int>> &foods, std::map<std::string, resturan*>::iterator &map_it)
{
    rest_reserve* rest_res = new rest_reserve;
    user_reserve* user_res = new user_reserve;
    rest_res->table_id = command_entered[3];
    user_res->table_id = command_entered[3];
    rest_res->username = current_user->username;
    user_res->resturan_name = command_entered[2];
    int res_id = stoi(map_it->second->last_reserve_id);
    res_id += 1;
    map_it->second->last_reserve_id = std::to_string(res_id);
    rest_res->reserve_id = std::to_string(res_id);
    user_res->reserve_id = std::to_string(res_id);
    rest_res->time_interval.first = command_entered[4];
    user_res->time_interval.first = command_entered[4];
    rest_res->time_interval.second = command_entered[5];
    user_res->time_interval.second = command_entered[5];
    if (command_entered.size() == 7)
    {
        for (auto i : foods)
        {
            user_res->foods[i.first] = {i.second.first, i.second.second};
            rest_res->foods[i.first] = {i.second.first, i.second.second};
        }
    }
    (*current_user->reserves)[std::to_string(res_id)] = user_res;
    (*all_resturans)[map_it->first]->reserves[std::to_string(res_id)] = rest_res;
    std::string respond = "";
    respond += "Reserve ID: "+std::to_string(res_id)+"\n";
    respond += "Table "+command_entered[3]+" for "+command_entered[4]+" to "+command_entered[5];
    respond += " in "+command_entered[2]+"\n";
    respond += "Price: ";
    if (command_entered.size() == 7)
    {
        std::string price = calculate_price(foods);
        respond += price+"\n";
    }
    else
        respond += "0\n";
    return respond;    
}

std::string software::reserve(std::vector<std::string> &command_entered)
{
    std::map<std::string, resturan*>::iterator map_it;
    std::map<std::string, std::pair<std::string, int>> foods;
    map_it = find_if((*all_resturans).begin(), (*all_resturans).end(), [command_entered](std::pair<std::string, resturan*> a){return a.first==command_entered[2];});
    if (map_it == (*all_resturans).end())
        throw errors(error_message::NOT_FOUND);
    if (find_if(map_it->second->tables.begin(), map_it->second->tables.end(), [command_entered](std::pair<std::string, table*> a){return a.second->table_id==command_entered[3];}) == map_it->second->tables.end())
        throw errors(error_message::NOT_FOUND);
    if (command_entered.size() == 7)
    {
        foods = parse_foods(command_entered[6]);
        std::map<std::string, std::string>::iterator menu_it;
        for (auto i : foods)
        {
            menu_it = find_if(map_it->second->menu.begin(), map_it->second->menu.end(), [i](std::pair<std::string, std::string> a){return a.first==i.first;});
            if (menu_it == map_it->second->menu.end())   
                throw errors(error_message::NOT_FOUND);
            else
                i.second.first = menu_it->second;
        }
    }  
    for (auto i : map_it->second->reserves)
    {
        if (i.second->table_id == command_entered[3])
        {
            if(stoi(i.second->time_interval.first) < stoi(command_entered[4]) && stoi(i.second->time_interval.second) > stoi(command_entered[4]))
                throw errors(error_message::PERMISSION_DENIED);
            else if(stoi(i.second->time_interval.first) < stoi(command_entered[5]) && stoi(i.second->time_interval.second) > stoi(command_entered[5]))  
                throw errors(error_message::PERMISSION_DENIED);      
        }
    } 
    for (auto i : (*current_user->reserves))
    {
        if (stoi(i.second->time_interval.first) < stoi(command_entered[4]) && stoi(i.second->time_interval.second) > stoi(command_entered[4]))
            throw errors(error_message::PERMISSION_DENIED);
        if (stoi(i.second->time_interval.first) < stoi(command_entered[5]) && stoi(i.second->time_interval.second) > stoi(command_entered[5]))
            throw errors(error_message::PERMISSION_DENIED);    
    }
    if (stoi(map_it->second->working_time.first) > stoi(command_entered[4]) || stoi(map_it->second->working_time.second) < stoi(command_entered[4]))
        throw errors(error_message::PERMISSION_DENIED);
    if (stoi(map_it->second->working_time.first) > stoi(command_entered[5]) || stoi(map_it->second->working_time.second) < stoi(command_entered[5]))
        throw errors(error_message::PERMISSION_DENIED); 
    std::string respond;
    respond = set_reserve(command_entered, foods, map_it);
    return respond;  
}