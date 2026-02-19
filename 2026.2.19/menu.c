#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "console.h"
#include "menu.h"

#define SCREEN_WIDTH 180
#define SCREEN_HEIGHT 50

// ===== 存档文件名生成 =====
void get_filename(int slot, char* buffer) {
    sprintf_s(buffer, 20, "save%d.dat", slot);
}

// ===== 读取存档 =====
void load_save(int slot, SaveData* data) {

    char filename[20];
    get_filename(slot, filename);

    FILE* fp = fopen(filename, "rb");

    if (fp == NULL) {
        // 默认初始化
        data->level = 1;
        data->gold = 0;
        data->item_count = 0;
        return;
    }

    fread(data, sizeof(SaveData), 1, fp);
    fclose(fp);
}

// ===== 保存存档 =====
void save_game(int slot, SaveData* data) {

    char filename[20];
    get_filename(slot, filename);

    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) return;

    fwrite(data, sizeof(SaveData), 1, fp);
    fclose(fp);
}



// ===== 开始界面 =====
void start_menu() {

    clear_screen();

    set_cursor_position(75, 12);
    printf("黑暗地牢");

    set_cursor_position(70, 16);
    printf("按任意键进入存档选择...");

    _getch();
}



// ===== 存档界面 =====
int save_menu() {

    SaveData saves[3];

    for (int i = 0; i < 3; i++)
        load_save(i + 1, &saves[i]);

    int current = 0;
    int key;

    while (1) {

        clear_screen();

        set_cursor_position(75, 5);
        printf("请选择存档");

        for (int i = 0; i < 3; i++) {

            int box_width = 40;
            int box_height = 10;

            int start_x = 20 + i * 50;
            int start_y = 15;

            // 画框
            for (int x = 0; x < box_width; x++) {
                set_cursor_position(start_x + x, start_y);
                printf("-");
                set_cursor_position(start_x + x, start_y + box_height);
                printf("-");
            }

            for (int y = 0; y <= box_height; y++) {
                set_cursor_position(start_x, start_y + y);
                printf("|");
                set_cursor_position(start_x + box_width, start_y + y);
                printf("|");
            }

            // 选中效果
            if (i == current) {
                set_cursor_position(start_x + 2, start_y - 1);
                printf(">> 当前选择");
            }

            // 内容
            set_cursor_position(start_x + 5, start_y + 2);
            printf("存档 %d", i + 1);

            set_cursor_position(start_x + 5, start_y + 4);
            printf("到达层数：%d", saves[i].level);

            set_cursor_position(start_x + 5, start_y + 6);
            printf("金币数量：%d", saves[i].gold);

            set_cursor_position(start_x + 5, start_y + 8);
            printf("道具数量：%d", saves[i].item_count);
        }

        key = _getch();

        if (key == 224) {
            key = _getch();

            if (key == 75) {   // ←
                current--;
                if (current < 0) current = 2;
            }
            else if (key == 77) {  // →
                current++;
                if (current > 2) current = 0;
            }
        }
        else if (key == 13) {  // 回车
            return current + 1;
        }
    }
}