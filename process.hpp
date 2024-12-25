#include "global.hpp"
#include "software.hpp"
#include "output.hpp"

// enum main_commads
// {
//     GET = 1,
//     PUT = 2,
//     POST = 3,
//     DELETE = 4
// };

class process
{
    public:
    process();
    void resturan_init (char *);
    void restrict_init (char *);
    void begin(std::vector<std::string> &command_entered);
    protected:
    software UTaste;
    output response;
    private:
    static std::vector<std::string> main_commands;
    static std::vector<std::string> sub_comma_get;
    static std::vector<std::string> sub_comma_put;
    static std::vector<std::string> sub_comma_post;
    static std::vector<std::string> sub_comma_delete;
    static std::vector<std::string> parse_line(std::string line);
    static std::vector<std::string> parse_neighbor(std::string nghbrs);
    static std::vector<std::string> parse_command(std::string command); 
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

class Delete : protected process
{
    public:
        std::string pro_delete (std::vector<std::string> &command_entered);
};