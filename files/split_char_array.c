#include <stdio.h>

int main()
{
    char str[] = "abcdefg";

    printf("The char array \"abcdefg\" printed out one by one array[item] in different formats\n\n");

    printf("\nChar array split:\n");
    for (int i = 0; i < sizeof(str) - 1; i++)  // we do not want to print out end zero '\0' so we use: -1 
    {
        printf("%c\n", str[i]);
    }
    
    printf("\nInteger hex:\n");
    for (int i = 0; i < sizeof(str)-1; i++)
    {
        printf("0x%X\n", str[i]);
    }

    printf("\nInteger decimal:\n");
    for (int i = 0; i < sizeof(str) - 1; i++)
    {
        printf("%d\n", str[i]);
    }

    printf("\nInteger converted to string:\n");
    for (int i = 0; i < sizeof(str) - 1; i++)
    {
        char buf[10];
        sprintf_s(buf, sizeof(buf),"%d", str[i]);
        printf("%s\n", buf);
    }

    // ** Pause before exit
    getchar();

    return 0;
};
