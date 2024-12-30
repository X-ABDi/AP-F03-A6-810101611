#include "district.hpp"

district::district()
{

}

district::~district()
{
    // vectors in map
}

void district::set_neighbors (std::vector<std::string> properties)
{
    if(district_neighbors.find(properties[0]) == district_neighbors.end())
    {
        std::vector<std::string> *new_vector = new std::vector<std::string>;
        district_neighbors[properties[0]] = new_vector;
        for (int i=1; i<district_neighbors.size(); i++)
        {
            district_neighbors[properties[0]]->push_back(properties[i]);
        }
    }
}

void district::set_resturans (std::string disstrict_name, std::string resturan_name)
{
    if(district_resturans.find(disstrict_name) != district_resturans.end())
    {
        district_resturans[disstrict_name]->push_back(resturan_name);
    }
    else
    {
        std::vector<std::string> *new_vector = new std::vector<std::string>;
        district_resturans[disstrict_name] = new_vector;
        district_resturans[disstrict_name]->push_back(resturan_name);
    }
}

std::string district::get_district(std::string district_name)
{
    std::map<std::string, std::vector<std::string>*>::iterator map_it;
    map_it = district_neighbors.find(district_name);
    if (map_it == district_neighbors.end())
        throw errors(error_message::NOT_FOUND);
    std::string respond{""};
    respond += map_it->first;
    respond += ": ";
    for (auto i : (*map_it->second))
    {
        respond += i;
        if (i != (*map_it->second).back())
            respond += ", ";
    }
    return respond;
}

std::string district::get_all_districts()
{
    std::string respond{""};
    std::map<std::string, std::vector<std::string>*>::iterator map_it;
    for (map_it = district_neighbors.begin(); map_it != district_neighbors.end(); map_it++)
    {
        respond += map_it->first;
        respond += ": ";
        for (auto i : (*map_it->second))
        {
            respond += i;
            if (i != (*map_it->second).back())
                respond += ", ";
        }
        respond += "\n";
    }
    return respond;
}