#include "interface.hpp"

void interface::run ()
{
    std::string respond;
    std::vector<std::string> command_entered;
    output result;
    while(true)
    {
        general_methods.begin(command_entered);
        std::cout << "running interface, parsed and back" << std::endl;
        if (command_entered[0] == main_command::GET)
        {
            Get* get_object;
            process* base_ptr = &general_methods;
            get_object = dynamic_cast<Get*>(base_ptr);
            respond = get_object->pro_get(command_entered);
        }
        else if (command_entered[0] == main_command::PUT)
        {
            Put* put_object;
            process* base_ptr = &general_methods;
            put_object = dynamic_cast<Put*>(base_ptr);
            respond = put_object->pro_put(command_entered);
        }
        else if (command_entered[0] == main_command::POST)
        {
            std::cout << "before casting to sub class" << std::endl;
            Post* post_object = post_object;
            process* base_ptr = &general_methods;
            post_object = dynamic_cast<Post*>(base_ptr);
            std::cout << "after dynamic cast" << std::endl;
            respond = post_object->pro_post(command_entered);
            std::cout << "process done" << std::endl;
        }
        else if (command_entered[0] == main_command::DELETE)
        {
            Delete* delete_object;
            process* base_ptr = &general_methods;
            delete_object = dynamic_cast<Delete*>(base_ptr);
            respond = delete_object->pro_delete(command_entered);
        }
        result.set_respond(respond);
        result.monitor();
    }    
}

void interface::initi (char *argv[])
{
    try{
    std::string respond;
    district_init(argv[2]);
    restaurant_init(argv[1]);
    discount_init(argv[3]);
    run();
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