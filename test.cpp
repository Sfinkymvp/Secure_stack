#include <stdio.h>

#define GREEN "\e[32m"
#define DEFAULT "\e[0m"

int main()
{
    printf(GREEN "YOY\n" DEFAULT);

    printf("HAHA\n");

    printf(GREEN "LOL\n" DEFAULT);

    return 0;
}
