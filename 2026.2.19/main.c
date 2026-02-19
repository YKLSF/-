#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "console.h"
#include "ui.h"
#include "game_data.h"
#include "menu.h"

// main 必须是大写的 main，且返回 int
int main() {
    srand((unsigned int)time(NULL));
    set_fullscreen();
    hide_cursor();

    start_menu();
    int slot = save_menu();

    if (slot >= 1 && slot <= 3) {
        init_game_system(); // logic.c 中的初始化
        generate_room();    // logic.c 中的生成
        init_game_ui();     // ui.c 中的画框

        int choice = 0;
        while (current_player.hp > 0) {
            render_player_panel();
            render_monster_panel();
            render_battle_panel();
            render_choice_panel(choice);
            render_info_panel();

            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 75) choice = (choice + 3) % 4; // 左
                if (key == 77) choice = (choice + 1) % 4; // 右
            }
            else if (key == 13) {
                if (choice == 0) player_attack();
                else if (choice == 1) player_defend();

                if (m_hp <= 0) {
                    current_player.gold += (10 + rand() % 5);
                    current_player.current_level++;
                    add_log("--- 胜利！获得金币，前往下一关 ---");
                    generate_room();
                }
            }
        }
    }
    return 0;
}
