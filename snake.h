#ifndef SNAKE_H
#define SNAKE_H
#include <stdio.h>
#include "arm_2d_scene_0.h"
#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

#define TBool int
#define True 1
#define False 0
#define SHAPE_FOOD '@'
#define SHAPE_SNAKE '#'
// #define GAMEWIN_YLEN     15
// #define GAMEWIN_XLEN     60
#define LOGBUF_NUM (LOGWIN_YLEN - 2)
#define LOGBUF_LEN (GAMEWIN_XLEN - 2)
#define MAXLEVEL 12
#define food_size 20
#define LOG_HERE printf("the code come %d\n", __LINE__)

#define GetSnakeTail(s) ((s)->head->front)

#define GAMEWIN_XLEN __GLCD_CFG_SCEEN_WIDTH__
#define GAMEWIN_YLEN __GLCD_CFG_SCEEN_HEIGHT__

extern struct user_scene_0_t *gameScene;
// extern struct TFood *pfood;

enum TDirection
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

typedef struct TFood
{
    int y;
    int x;
} TFood;

typedef struct TSnakeNode
{
    int y;
    int x;
    struct TSnakeNode *front;
} TSnakeNode;

typedef struct TSnake
{
    int length;
    struct TSnakeNode *head;
    enum TDirection dir;
} TSnake;

enum GAME_STATUS
{
    GAME_START,
    GAME_PLAYING,
    GAME_WRONG,
    GAME_END,
    GAME_WIN
};

int refreshgamew(struct user_scene_0_t *ptTarget, struct TSnake *psnake);
void movesnake(struct TSnake *psnake);
int checksnake(struct TFood *pfood, struct TSnake *psnake);
void snakegrowup(struct TFood *pfood, struct TSnake *psnake);

struct TSnakeNode *newsnakenode(struct TSnakeNode **ppsnode, int y, int x);
const arm_2d_tile_t *newgamew(const arm_2d_tile_t *ptTarget);
struct TSnake *initsnake();
void destroysnake(struct TSnake *psnake);

void gameover(const arm_2d_tile_t *ptTarget, char *str);
void drawsnakew(const arm_2d_tile_t *ptTarget, struct TSnake *psnake, const int size);
void drawfoodw(TFood *pfood, TSnake *psnake);
void mvwaddch(const arm_2d_tile_t *ptTarget, const int xx, const int yy, const int size);

TBool checkfood(struct TFood *pfood, struct TSnake *psnake);
const arm_2d_tile_t *newlogw();
void runlog(struct user_scene_0_t *ptTarget, char *str);
void cleanline(struct user_scene_0_t *ptTarget, int y, int x);
#endif
