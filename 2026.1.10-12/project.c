
#define _CRT_SECRE_NO_WARNINGS
#include<stdio.h>
int main()
{
    int x = 100;//当前体力
    int key = 0;

    while (x > 0)
    {
        printf("\n当前体力，%d", x);
        printf("\n请输入1休息，2行走，3奔跑，4退出");
        scanf_s("%d", &key);

        //根据当前行为，决定发生了什么
        switch (key)
        {
        case 1://休息
            if (x < 100)
            {
                x += 2;
                if (x > 100)
                    x = 100;
            }
            printf("你在休息，体力恢复中\n");
            break;

        case 2://行走
            x -= 1;
            if (x < 0)
                x = 0;

            printf("你正在走路体力消耗中\n");
            break;

        case 3://奔跑
            x -= 5;
            if (x < 0)
                x = 0;

            printf("你正在奔跑，体力消耗中");
            break;

        case 4://退出
            return 0;

        default:
            printf("无效输出请输入1,2,3,4\n");
            break;

        }
        printf("体力耗尽游戏结束\n");
        return 0;
        /*1	休息	每秒恢复 2 点体力
            2	行走	每秒消耗 1 点体力
            3	奔跑	每秒消耗 5 点体力
            4	退出	程序结束*/

    }
}

