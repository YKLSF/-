#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "menu.h"

// 房间类型
typedef enum { RM_MOB, RM_ELITE, RM_BOSS, RM_SHOP, RM_EVENT, RM_NPC } RoomType;

typedef struct {
    char name[30];
    int type; // 0:普通, 1:精英, 2:BOSS
    float rate;
    char desc[128];
} MonsterTemplate;

typedef struct {
    int hp, max_hp, atk, def, gold, current_level;
} PlayerStatus;

// 全局变量定义
extern PlayerStatus current_player;
extern MonsterTemplate current_monster;
extern int m_hp, m_atk, m_def;
extern RoomType current_room;
extern char battle_logs[10][100]; // 10行堆叠日志

// 函数
void add_log(const char* format, ...);
void init_game_system();
void generate_room();
void player_attack();
void player_defend();

#endif