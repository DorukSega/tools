#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
EXIT:
        printf("Changes the title of the active terminal window\n");
        printf("Usage: %s <title>\n", argv[0]);
        return 1;
    }
    if (argv[1][0] == '-' && argv[1][2]=='\0') // captures any flag
        goto EXIT;
    printf("\033]0;%s\007",argv[1]);
    return 0;
}
