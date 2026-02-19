#ifndef MENU_H
#define MENU_H

typedef struct {
    int level;
    int gold;
    int item_count;
} SaveData;

void start_menu();
int save_menu();
void load_save(int slot, SaveData* data);
void save_game(int slot, SaveData* data);

#endif