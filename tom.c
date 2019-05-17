#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 读取文件内容
 **/
char *readSource(const char *filename) {
    int readSize = 256 * 1024;

    FILE *fd = fopen(filename, "r");
    char *source = malloc(readSize);
    int n = fread(source, 1, readSize, fd);
    source[n] = 0;  // 在字符串的末尾添加结束符
    fclose(fd);

    return source;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("no input file\n");
        return 1;
    }
    const char *filename = argv[1];
    const char *src = readSource(filename);
    printf("%s", src);
    return 0;
}
