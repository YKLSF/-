#include "game_data.h"
#include "ui.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

PlayerStatus current_player;
MonsterTemplate current_monster;
int m_hp, m_atk, m_def;
RoomType current_room;
char battle_logs[10][100];

// 文档 1.1：怪物全库
MonsterTemplate monster_pool[] = {
    {"流浪野兽", 0, 1.00f, "一只瘦弱的野兽在烈日下徘徊。"},
    {"沙漠盗匪", 0, 1.00f, "一个盗匪举起短剑挡住了你的去路。"},
    {"干枯蝎子", 0, 1.05f, "沙地里突然窜出一只毒蝎，尾针闪着寒光。"},
    {"巨型蜥蜴", 0, 1.00f, "巨大的蜥蜴鳞片坚硬，动作迅捷。"},
    {"荒漠蝗虫", 0, 0.90f, "成群的蝗虫遮蔽了你的视线。"},
    {"食尸鹫",   0, 1.10f, "它在低空盘旋，等待你倒下。"},
    {"沙丘爬行者", 0, 1.00f, "它从沙子里突然钻出！"},
    {"仙人掌精", 0, 1.15f, "浑身布满尖刺的植物。"},
    {"流沙灵",   0, 1.20f, "纯粹由黄沙构成的怪物。"},
    {"荒野守卫", 1, 1.40f, "遗迹的守护者，压迫感十足。"},
    {"沙漠之王", 2, 2.50f, "【BOSS】沙漠的主宰，庞大身影。"}
};

// 安全的日志堆叠逻辑
void add_log(const char* format, ...) {
    for (int i = 0; i < 9; i++) {
        strcpy_s(battle_logs[i], 100, battle_logs[i + 1]);
    }
    va_list args;
    va_start(args, format);
    vsprintf_s(battle_logs[9], 100, format, args);
    va_end(args);
}

void init_game_system() {
    current_player.hp = 120; current_player.max_hp = 120;
    current_player.atk = 12; current_player.def = 4;
    current_player.gold = 50; current_player.current_level = 1;
    for (int i = 0; i < 10; i++) strcpy_s(battle_logs[i], 100, "");
}

// 房间生成：包含保底商店与文档概率
void generate_room() {
    int lvl = current_player.current_level;
    if (lvl % 9 == 0) current_room = RM_BOSS;
    else if (lvl == 5) current_room = RM_SHOP; // 第5关保底
    else {
        int r = rand() % 100;
        if (r < 40) current_room = RM_MOB;      // 40% 小怪
        else if (r < 60) current_room = RM_EVENT; // 20% 事件
        else if (r < 75) current_room = RM_ELITE; // 15% 精英
        else current_room = RM_SHOP;              // 其余商店或NPC
    }

    int midx = (current_room == RM_BOSS) ? 10 : (current_room == RM_ELITE ? 9 : rand() % 9);
    current_monster = monster_pool[midx];
    m_hp = (int)((15 + lvl * 5) * current_monster.rate);
    m_atk = (int)((4 + lvl * 1) * current_monster.rate);
    m_def = (current_monster.type == 1) ? 2 : 0;

    add_log("--- 第 %d 关 ---", lvl);
    if (current_room == RM_SHOP) add_log("你遇到了一个驼背的沙漠商人。");
    else add_log("遭遇了 [%s]！", current_monster.name);
}

void player_attack() {
    int dmg = current_player.atk - m_def;
    if (dmg < 1) dmg = 1;
    m_hp -= dmg;
    add_log(">> 你发起攻击，造成了 %d 点伤害。(怪HP:%d)", dmg, (m_hp < 0 ? 0 : m_hp));

    if (m_hp > 0) {
        int m_dmg = m_atk - current_player.def;
        if (m_dmg < 1) m_dmg = 1;
        current_player.hp -= m_dmg;
        add_log("<< %s 猛击！你失去了 %d 点生命。", current_monster.name, m_dmg);
    }
}

void player_defend() {
    add_log(">> 你稳住重心进行防御。");
    int m_dmg = (m_atk - current_player.def) / 2;
    if (m_dmg < 0) m_dmg = 0;
    current_player.hp -= m_dmg;
    add_log("<< 你防御了部分攻击，仅损失 %d HP。", m_dmg);
}