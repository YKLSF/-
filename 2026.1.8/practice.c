#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRY 3
#define CORRECT_PWD "123456"

int main(void)
{
    char password[20] = { 0 };
    int i = 0;

    for (i = 0; i < MAX_TRY; i++)
    {
        printf("ÇëÊäÈëÃÜÂë£¨Ê£Óà %d ´Î£©£º\n", MAX_TRY - i);
        scanf("%19s", password);   // ·ÀÖ¹Ô½½ç

        if (strcmp(password, CORRECT_PWD) == 0)
        {
            printf("µÇÂ¼³É¹¦\n");
            return 0;
        }
        else
        {
            printf("ÃÜÂë´íÎó\n\n");
        }
    }

    printf("Èý´ÎÃÜÂë´íÎó£¬³ÌÐòÍË³ö\n");
    return 0;
}