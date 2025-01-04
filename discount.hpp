#ifndef __DISCOUNT__
#define __DISCOUNT__

#include "global.hpp"

class discount
{
    protected: 
        std::string type;
        float value;
        virtual void set_properties (std::string, std::string, std::string)=0;
        friend class resturan; 
        friend class software;   
};

class total_price_discount : protected discount
{
    private:
        float minimum_total;
    public:
        void set_properties(std::string, std::string, std::string);    
    friend class resturan;
    friend class software;
};

class first_order_discount : protected discount
{
    public:
        void set_properties(std::string, std::string, std::string);
    friend class resturan; 
    friend class software;   
};

class specific_food_discount : protected discount
{
    private:
        std::string food_name;
    public:
        void set_properties(std::string, std::string, std::string);
        std::string get_food_name();
    friend class resturan; 
    friend class software;   
};

#endif