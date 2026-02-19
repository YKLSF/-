#ifndef UI_H
#define UI_H

typedef struct {
    int x, y, width, height;
} Panel;

// 声明面板变量，让其他文件能引用
extern Panel player_panel, battle_panel, monster_panel, item_panel, choice_panel, info_panel;

// 声明函数
void init_game_ui();
void clear_panel(Panel p); // 必须声明，否则会报错“无法解析”
void render_player_panel();
void render_monster_panel();
void render_battle_panel();
void render_choice_panel(int current);
void render_info_panel();

#endif