#include <stdio.h>
#include <string.h>

int main()
{
    char *secret = "This is bad news!";
    printf("%p is a string of %zu length\n", secret, strlen(secret));

    getchar();

    return 0;
}
