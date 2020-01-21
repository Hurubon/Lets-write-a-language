#include <stdio.h>
#include <stdlib.h>
#include "lib/bool/bool.h"
#include "lib/z_algorithm/z_algorithm.h"

int main(void) {


    const char* a = "abababab";
    const char* b = "b";

    bool was_found = find(a, b);

    if (was_found) {
        printf("%s was found in %s!\n", b, a);
    } else {
        printf("%s was not found in %s!\n", b, a);
    }

    getchar();
    return 0;

}
