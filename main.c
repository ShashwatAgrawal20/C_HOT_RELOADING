#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int (*lib_function)(int, int);
int main() {
    void *handle = NULL;
    lib_function function_pointing_to_lib_function = NULL;
    uint8_t should_reload = 1;

    while (1) {
        if (should_reload) {
            system("clang -Wall -Wextra -shared -fPIC lib.c -o lib.so");
            if (handle) {
                dlclose(handle);
            }

            handle = dlopen("./lib.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "Error loading library %s\n", dlerror());
                return 1;
            }

            function_pointing_to_lib_function =
                dlsym(handle, "function_inside_lib");
            if (function_pointing_to_lib_function == NULL) {
                fprintf(stderr, "Error loading symbol: %s\n", dlerror());
                dlclose(handle);
                return 1;
            }
            should_reload = 0;
            printf("Library reloaded!\n");
        }
        int result = function_pointing_to_lib_function(5, 5);
        printf("Result: %d\n", result);

        printf("Press 'r' and Enter to reload, 'q' to quit: ");
        char input = getchar();
        getchar();

        if (input == 'r') {
            should_reload = 1;
        } else {
            break;
        }
    }
    if (handle) {
        dlclose(handle);
    }

    return 0;
}
