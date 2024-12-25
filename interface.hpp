#include "global.hpp"
#include "error.hpp"
#include "input.hpp"
#include "process.hpp"
#include "put.hpp"
#include "post.hpp"
#include "get.hpp"
#include "delete.hpp"

class interface
{
    input request;
    process general_methods;
    public:
        void init (char *argv[]);
        std::string run ();
        void restaurant_init(char *resturan_file);
        void restrict_init(char *restrict_file);
};