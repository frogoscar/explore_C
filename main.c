#include <stdio.h>

int main(int argc, char *argv[])
{
    char name[20] = {0};

    printf("您的名字是什么 ? ");
    scanf("%s", name);
    printf("您名叫 %s!\n", name);

    return 0;
}
