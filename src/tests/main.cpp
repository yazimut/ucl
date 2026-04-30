#include <iostream>

#include <ucl/version.hpp>

using namespace std;
using namespace ucl;
using namespace ucl::version;



int main(int argc, char *argv[], [[maybe_unused]] char *env[]) {
    printf("Launching testing UCL v%s...\n", ucl::version::getVersionString());
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d]: \"%s\"\n", i, argv[i]);
    }

    return 0x00;
}
