#include "interface.hpp"

interface::interface() : general_methods(), post_object(general_methods), get_object(general_methods)
                       , put_object(general_methods), delete_object(general_methods)  
{

}

std::string interface::run (std::vector<std::string> command_entered)
{
    std::string respond;
    // general_methods.begin(command_entered);
    if (command_entered[0] == main_command::GET)
    {
        respond = get_object.pro_get(command_entered);
    }
    else if (command_entered[0] == main_command::PUT)
    {
        respond = put_object.pro_put(command_entered);
    }
    else if (command_entered[0] == main_command::POST)
    {
        respond = post_object.pro_post(command_entered);
    }
    else if (command_entered[0] == main_command::DELETE)
    {
        respond = delete_object.pro_delete(command_entered);
    } 
    return respond;    
}

void interface::initi (char *argv[])
{
    try{
    district_init(argv[3]);
    restaurant_init(argv[2]);
    discount_init(argv[4]);
    // run();
    }
    catch (errors &e)
    {
        e.printError();
    }
}

void interface::restaurant_init (char *resturan_file)
{
    general_methods.resturan_init(resturan_file);
}

void interface::district_init (char *restrict_file)
{
    general_methods.district_init(restrict_file);
}

void interface::discount_init (char *discount_file)
{
    general_methods.discount_init(discount_file);
}