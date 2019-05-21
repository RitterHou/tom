# include <stdio.h>
# include <stdlib.h>

# define PAGE_LINES 24
# define LINE_LENGTH 80

int seeMore(FILE * cmd) {
    printf("\033[7m more? \033[m");
    int c;
    while ((c = getc(cmd)) != EOF) {
        if (c == 'q') { // 退出
            return 0;
        }
        if (c == ' ') { // 下一页
            return PAGE_LINES;
        }
        if (c == '\n') { // 下一行
            return 1;
        }
    }
    return 0;
}

void doMore(FILE * fd) {
    char line[LINE_LENGTH];
    int lineNum = 0; // 已经显示的行数
    FILE * ttyFd = fopen("/dev/tty", "r");
    if (ttyFd == NULL) {
        exit(1);
    }
    while (fgets(line, LINE_LENGTH, fd)) {
        if (lineNum == PAGE_LINES) {
            int replay = seeMore(ttyFd);
            if (replay == 0) {
                break;
            }
            lineNum -= replay;
        }
        if (fputs(line, stdout) == EOF) {
            exit(1);
        }
        lineNum++;
    }
}

int main(int argc, char const * argv[]) {
    if (argc == 1) {
        doMore(stdin);
    } else {
        FILE * fd = fopen(argv[1], "r");
        if (fd == NULL) {
            exit(1);
        }
        doMore(fd);
        fclose(fd);
    }
    return 0;
}
