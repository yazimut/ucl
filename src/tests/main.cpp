#include <iostream>
#include <filesystem>
#include <locale>
#if defined(_WIN32)
    #include <windows.h>
#endif

#include <ucl/version.hpp>

using namespace std;
using namespace ucl;
using namespace ucl::version;

namespace fs = std::filesystem;



int main(int argc, char *argv[], [[maybe_unused]] char *env[]) {
    #if defined(_WIN32)
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        setlocale(LC_ALL, "C.UTF-8");
    #else
        setlocale(LC_ALL, "");
    #endif

    printf("Launching testing UCL v%s...\n", ucl::version::getVersionString());
    for (int i = 0; i < argc; ++i) {
        printf("argv[%d]: \"%s\"\n", i, argv[i]);
    }

    fs::path p = "мой путь";
    p = p / L"мой путь 2.0";
    cout << p << endl;

    return 0x00;
}
