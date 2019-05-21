#include <stdio.h>
#include <stdlib.h>

void doMore(FILE* fd) {}

int main(int argc, char const* argv[]) {
    if (argc == 1) {
        doMore(stdin);
    } else {
        while (--argc) {
            FILE* fd = fopen(argv[argc], "r");
            if (fd == NULL) {
                exit(1);
            }
            doMore(fd);
            fclose(fd);
        }
    }
    return 0;
}
