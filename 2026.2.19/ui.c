#include <stdio.h>
#include <string.h>
#include "console.h"
#include "ui.h"
#include "game_data.h"

// 定义面板坐标
Panel player_panel = { 0, 0, 36, 25 };
Panel battle_panel = { 36, 0, 108, 25 };
Panel monster_panel = { 144, 0, 36, 25 };
Panel item_panel = { 0, 25, 36, 25 };
Panel choice_panel = { 36, 25, 108, 25 };
Panel info_panel = { 144, 25, 36, 25 };

void draw_panel(Panel p) {
    for (int i = 0; i < p.width; i++) {
        set_cursor_position(p.x + i, p.y); printf("-");
        set_cursor_position(p.x + i, p.y + p.height - 1); printf("-");
    }
    for (int i = 0; i < p.height; i++) {
        set_cursor_position(p.x, p.y + i); printf("|");
        set_cursor_position(p.x + p.width - 1, p.y + i); printf("|");
    }
}

void clear_panel(Panel p) {
    for (int i = 1; i < p.height - 1; i++) {
        set_cursor_position(p.x + 1, p.y + i);
        for (int j = 1; j < p.width - 1; j++) printf(" ");
    }
}

void init_game_ui() {
    clear_screen();
    draw_panel(player_panel); draw_panel(battle_panel); draw_panel(monster_panel);
    draw_panel(item_panel); draw_panel(choice_panel); draw_panel(info_panel);
}

void render_battle_panel() {
    clear_panel(battle_panel);
    set_cursor_position(battle_panel.x + 4, battle_panel.y + 2);
    printf("【 战 况 记 录 】");
    for (int i = 0; i < 10; i++) {
        if (strlen(battle_logs[i]) > 0) {
            set_cursor_position(battle_panel.x + 6, battle_panel.y + 5 + i);
            printf("%s", battle_logs[i]);
        }
    }
}

void render_player_panel() {
    clear_panel(player_panel);
    set_cursor_position(player_panel.x + 4, player_panel.y + 4);
    printf("【 勇者 】");
    set_cursor_position(player_panel.x + 4, player_panel.y + 7);
    printf("HP: %d/%d", current_player.hp, current_player.max_hp);
}

void render_monster_panel() {
    clear_panel(monster_panel);
    if (m_hp > 0) {
        set_cursor_position(monster_panel.x + 4, monster_panel.y + 4);
        printf("【 %s 】", current_monster.name);
        set_cursor_position(monster_panel.x + 4, monster_panel.y + 7);
        printf("HP: %d", m_hp);
    }
}

void render_choice_panel(int current) {
    clear_panel(choice_panel);
    char* opt[] = { "攻击", "防御", "道具", "逃跑" };
    for (int i = 0; i < 4; i++) {
        set_cursor_position(choice_panel.x + 10 + i * 22, choice_panel.y + 10);
        printf("%s %s", (i == current) ? ">>" : "  ", opt[i]);
    }
}

void render_info_panel() {
    clear_panel(info_panel);
    set_cursor_position(info_panel.x + 4, info_panel.y + 4);
    printf("金币: %d G", current_player.gold);
    set_cursor_position(info_panel.x + 4, info_panel.y + 7);
    printf("关卡: %d/54", current_player.current_level);
}
void render_item_panel() { clear_panel(item_panel); } // 占位