#include "district.hpp"

district::district() : district_neighbors(new std::map<std::string, std::vector<std::string>*>), 
                        district_resturans(new  std::map<std::string, std::vector<std::shared_ptr<resturan>>*>)
{

}

district::~district()
{
    for (auto i : *district_neighbors)
        delete i.second;
    for (auto i : *district_resturans)
    {
        delete i.second;    
    }
}

bool district::user_district_check (std::string district_name)
{
    if (find_if(district_neighbors->begin(), district_neighbors->end(), [district_name](std::pair<std::string, std::vector<std::string>*> a){return a.first == district_name;}) != district_neighbors->end())
        return true;
    return false;    
}

void district::set_neighbors (std::vector<std::string> properties)
{
    if(district_neighbors->find(properties[0]) == district_neighbors->end())
    {
        std::vector<std::string> *new_vector = new std::vector<std::string>;
        (*district_neighbors)[properties[0]] = new_vector;
        for (int i=1; i<district_neighbors->size(); i++)
        {
            (*district_neighbors)[properties[0]]->push_back(properties[i]);
        }
    }
}

void district::set_resturans (std::string district_name, std::shared_ptr<resturan> new_resturan)
{
    if(district_resturans->find(district_name) != district_resturans->end())
    {
        (*district_resturans)[district_name]->push_back(new_resturan);
    }
    else
    {
        std::vector<std::shared_ptr<resturan>> *new_vector = new std::vector<std::shared_ptr<resturan>>;
        (*district_resturans)[district_name] = new_vector;
        (*district_resturans)[district_name]->push_back(new_resturan);
    }
}

void district::get_district(std::string_view district_name, std::string &respond)
{
    std::map<std::string, std::vector<std::string>*>::iterator map_it;
    map_it = district_neighbors->find(std::string(district_name));
    if (map_it == district_neighbors->end())
    respond += map_it->first;
    respond += output_common::COLON;
    for (auto i : (*map_it->second))
    {
        respond += i;
        if (i != (*map_it->second).back())
            respond += output_common::COMMA;
    }
}

void district::get_all_districts(std::string &respond)
{
    std::map<std::string, std::vector<std::string>*>::iterator map_it;
    for (map_it = district_neighbors->begin(); map_it != district_neighbors->end(); map_it++)
    {
        respond += map_it->first;
        respond += output_common::COLON;
        for (auto i : (*map_it->second))
        {
            respond += i;
            if (i != (*map_it->second).back())
                respond += output_common::COMMA;
        }
        respond += output_common::NEW_LINE;
    }
}

void district::get_resturans(std::string_view user_district, std::string &food_name, std::string &respond)
{
    std::map<std::string, std::vector<std::string>*>::iterator dis_neigh_it;
    std::map<std::string, bool> checked;
    for (auto i : *district_neighbors)
        checked[i.first] = false;

    dis_neigh_it = district_neighbors->find(std::string(user_district));
    std::queue<std::pair<std::string,std::vector<std::string>*>> my_q;
    my_q.push((*dis_neigh_it));
    checked[dis_neigh_it->first] = true;
    for (auto i : (*dis_neigh_it->second))
    {
        my_q.push((*district_neighbors->find(i)));
        checked[district_neighbors->find(i)->first] = true;
    }
    split_resturan_request(food_name, my_q, checked);
}

void district::split_resturan_request(std::string &food_name, std::queue<std::pair<std::string,std::vector<std::string>*>> &my_q,
                                                std::map<std::string, bool> &checked)
{
    std::pair<std::string, std::vector<std::string>*> dis_pair;
    std::map<std::string, std::vector<std::string>*>::iterator dis_neigh_it;
    std::string respond;
    while (!my_q.empty())
    {
        dis_pair = my_q.front();
        my_q.pop();
        if (food_name == EMPTY_STRING)
            get_resturans_by_food(respond, dis_pair, food_name);
        else
            get_all_resturans(respond, dis_pair);    
        for (auto j : (*dis_pair.second))
        {
            if (!checked[j])
            {
                dis_neigh_it = district_neighbors->find(j);
                my_q.push((*dis_neigh_it));
                checked[dis_neigh_it->first] = true;
            }
        }
    }
}

void district::get_resturans_by_food(std::string &respond, std::pair<std::string, std::vector<std::string>*> &dis_pair, std::string &food_name)
{
    for (auto i : (*(*district_resturans)[dis_pair.first]))
    {
        if (i->menu->count(food_name))
        {
            respond += i->name;
            respond += output_common::SPACE;
            respond += output_common::PARANTHESE_OPEN;
            respond += i->district;
            respond += output_common::PARANTHESE_CLOSE;
            respond += output_common::NEW_LINE;
        }
    }
}

void district::get_all_resturans(std::string &respond, std::pair<std::string, std::vector<std::string>*> &dis_pair)
{
    for (auto i : (*(*district_resturans)[dis_pair.first]))
    {
        respond += i->name;
        respond += output_common::SPACE;
        respond += output_common::PARANTHESE_OPEN;
        respond += i->district;
        respond += output_common::PARANTHESE_CLOSE;
        respond += output_common::NEW_LINE;
    }
}