#ifndef __DISCOUNT__
#define __DISCOUNT__

#include "global.hpp"

class discount
{
    protected: 
        std::string type;
        int value;
        virtual void set_properties (std::string, std::string, std::string)=0;
        friend class resturan;    
};

class total_price_discount : protected discount
{
    private:
        int minimum_total;
    public:
        void set_properties(std::string, std::string, std::string);    

};

class first_order_discount : protected discount
{
    public:
        void set_properties(std::string, std::string, std::string);
};

class specific_food_discount : protected discount
{
    private:
        std::string food_name;
    public:
        void set_properties(std::string, std::string, std::string);
        std::string get_food_name();
};

#endif