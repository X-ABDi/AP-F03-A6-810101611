#include "restrict.hpp"

restrict::restrict()
{

}

restrict::~restrict()
{
    // vectors in map
}

void restrict::set_neighbors (std::vector<std::string> properties)
{
    if(restrict_neighbors.find(properties[0]) == restrict_neighbors.end())
    {
        std::vector<std::string> *new_vector = new std::vector<std::string>;
        restrict_neighbors[properties[0]] = new_vector;
        for (int i=1; i<restrict_neighbors.size(); i++)
        {
            restrict_neighbors[properties[0]]->push_back(properties[i]);
        }
    }
}

void restrict::set_resturans (std::string restrict_name, std::string resturan_name)
{
    if(restrict_resturans.find(restrict_name) != restrict_resturans.end())
    {
        restrict_resturans[restrict_name]->push_back(resturan_name);
    }
    else
    {
        std::vector<std::string> *new_vector = new std::vector<std::string>;
        restrict_resturans[restrict_name] = new_vector;
        restrict_resturans[restrict_name]->push_back(resturan_name);
    }
}