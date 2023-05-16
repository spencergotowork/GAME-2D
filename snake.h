#include <stdio.h>
#include "arm_2d_scene_0.h"
#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

#define TBool            int
#define True             1
#define False            0    
#define SHAPE_FOOD       '@'
#define SHAPE_SNAKE      '#'
//#define GAMEWIN_YLEN     15
//#define GAMEWIN_XLEN     60
#define LOGBUF_NUM       (LOGWIN_YLEN-2)
#define LOGBUF_LEN       (GAMEWIN_XLEN-2)
#define MAXLEVEL         12
#define food_size				 20
#define LOG_HERE				printf("the code come %d\n", __LINE__)
  
#define GetSnakeTail(s)  ((s)->head->front)

static uint16_t g_level;
static uint16_t GAMEWIN_XLEN = __GLCD_CFG_SCEEN_WIDTH__;
static uint16_t GAMEWIN_YLEN = __GLCD_CFG_SCEEN_HEIGHT__;

enum TDirection {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};
  
struct TFood {
    int y;
    int x;
};
  
struct TSnakeNode {
    int y;
    int x;
    struct TSnakeNode *front;
};
  
struct TSnake {
    int    length;
    struct TSnakeNode *head;
    enum   TDirection  dir;
};

int refreshgamew(const arm_2d_tile_t *ptTarget, struct TSnake *psnake);
void movesnake(struct TSnake *psnake);
int checksnake(struct TFood *pfood, struct TSnake *psnake);
void snakegrowup(struct TFood *pfood, struct TSnake *psnake);
void gameover(const arm_2d_tile_t *ptTarget, char *str);
struct TSnakeNode *newsnakenode(struct TSnakeNode **ppsnode, int y, int x);
const arm_2d_tile_t* newgamew(const arm_2d_tile_t *ptTarget);
struct TSnake* initsnake();
void destroysnake(struct TSnake *psnake);
void drawsnakew(const arm_2d_tile_t *ptTarget, struct TSnake *psnake, const int size);
void drawfoodw(const arm_2d_tile_t *ptTarget, struct TFood *pfood, struct TSnake *psnake);

TBool checkfood(struct TFood *pfood, struct TSnake *psnake);
const arm_2d_tile_t* newlogw();
void runlog(const arm_2d_tile_t *ptTarget, char *str);
void cleanline(const arm_2d_tile_t *ptTarget, int y, int x);
void mvwaddch(const arm_2d_tile_t *ptTarget,const int xx, const int yy,const int size);
extern struct TSnake *psnake;