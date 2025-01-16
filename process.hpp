#ifndef __PROCESS__
#define __PROCESS__

#include "global.hpp"
#include "software.hpp"

class process
{
    public:
    process();
    process(process &process_obj);
    void resturan_init (char *);
    void district_init (char *);
    void discount_init (char *);
    void begin(std::vector<std::string> &command_entered);
    protected:
    std::shared_ptr<software> UTaste;
    private:
    static std::vector<std::string_view> main_commands;
    static std::vector<std::string_view> sub_comma_get;
    static std::vector<std::string_view> sub_comma_put;
    static std::vector<std::string_view> sub_comma_post;
    static std::vector<std::string_view> sub_comma_delete;
    static std::vector<std::string> parse_line(std::string line);
    static std::vector<std::string> parse_neighbor(std::string nghbrs);
    static void parse_command(std::vector<std::string> &command_entered, std::string input); 
    static void parse_sub_command(std::vector<std::string> &command_entered, std::stringstream &ss);   
    static void parse_sub_get(std::vector<std::string> &command_entered, std::stringstream &ss);
    static void parse_sub_put(std::vector<std::string> &command_entered, std::stringstream &ss);
    static void parse_sub_post(std::vector<std::string> &command_entered, std::stringstream &ss);
    static void parse_post_signup (std::vector<std::string> &command_entered, std::stringstream &ss);
    static void parse_post_login (std::vector<std::string> &command_entered, std::stringstream &ss);
    static void parse_post_reserve (std::vector<std::string> &command_entered, std::stringstream &ss);
    static void parse_sub_delete(std::vector<std::string> &command_entered, std::stringstream &ss);
    virtual std::string pro_get (std::vector<std::string> &command_entered);
    virtual std::string pro_put (std::vector<std::string> &command_entered);
    virtual std::string pro_post (std::vector<std::string> &command_entered);
    virtual std::string pro_delete (std::vector<std::string> &command_entered);
};

#endif