#include "global.hpp"
#include "error.hpp"
#include "input.hpp"
#include "output.hpp"
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
        void run ();
        void restaurant_init(char *resturan_file);
        void district_init(char *restrict_file);
};