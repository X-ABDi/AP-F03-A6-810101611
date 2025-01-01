#ifndef __INTERFACE__
#define __INTERFACE__

#include "global.hpp"
#include "error.hpp"
#include "output.hpp"
#include "process.hpp"
#include "put.hpp"
#include "post.hpp"
#include "get.hpp"
#include "delete.hpp"

class interface
{
    process general_methods;
    public:
        void init (char *argv[]);
        void run ();
        void restaurant_init(char *resturan_file);
        void district_init(char *restrict_file);
};

#endif