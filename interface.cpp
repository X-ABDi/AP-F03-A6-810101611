#include "interface.hpp"

std::string interface::run ()
{
    std::vector<std::string> command_entered;
    general_methods.begin(command_entered);
    if (command_entered[0] == main_command::GET)
    {
        Get* get_object;
        process* base_ptr = &general_methods;
        get_object = dynamic_cast<Get*>(base_ptr);
        get_object->pro_get(command_entered);
    }
    else if (command_entered[0] == main_command::PUT)
    {
        Put* put_object;
        process* base_ptr = &general_methods;
        put_object = dynamic_cast<Put*>(base_ptr);
        put_object->pro_put(command_entered);
    }
    else if (command_entered[0] == main_command::POST)
    {
        Post* post_object;
        process* base_ptr = &general_methods;
        post_object = dynamic_cast<Post*>(base_ptr);
        post_object->pro_post(command_entered);
    }
    else if (command_entered[0] == main_command::DELETE)
    {
        Delete* delete_object;
        process* base_ptr = &general_methods;
        delete_object = dynamic_cast<Delete*>(base_ptr);
        delete_object->pro_delete(command_entered);
    }
}

void interface::init (char *argv[])
{
    district_init(argv[2]);
    restaurant_init(argv[1]);
    run();
}

void interface::restaurant_init (char *resturan_file)
{
    general_methods.resturan_init(resturan_file);
}

void interface::district_init (char *restrict_file)
{
    general_methods.district_init(restrict_file);
}