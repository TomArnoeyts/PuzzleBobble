#include <Program.h>
#include <Configuration.h>

int main()
{
    Configuration::initialize();

    Program p;

    p.run(25);

    Configuration::release();

    return 0;
}
