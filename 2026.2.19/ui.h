#ifndef UI_H
#define UI_H

typedef struct { int x, y, width, height; } Panel;

// 声明，不定义
extern Panel player_panel, battle_panel, monster_panel, item_panel, choice_panel, info_panel;

void init_game_ui();
void clear_panel(Panel p);
void render_player_panel();
void render_monster_panel();
void render_battle_panel();
void render_choice_panel(int current);
void render_info_panel();
void render_item_panel();

#endif