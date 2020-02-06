#include <stdlib.h>
#include <stdio.h>

#include "lib/fileadapter/fileadapter.h"
#include "lib/lexer/lexer.h"

int main(void) {

    FileAdapter* file = (FileAdapter*) malloc(sizeof(FileAdapter));
    FileAdapter_Load(file, "foo.txt");

    lex(file);

    FileAdapter_Close(file);
    getchar();
    return 0;

}
