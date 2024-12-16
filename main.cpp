#include "main.hpp"
int main (int argc, char* argv[])
{
    application ut_taste;
    initializer init(ut_taste, argv);
    ut_taste.begin();
}