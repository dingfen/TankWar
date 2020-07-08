#include "app.h"

using std::cerr;
using std::endl;
using std::cout;

int main(int argc, char const *argv[])
{
    App* a = App::getInstance();
    a->run();
    return 0;
}
