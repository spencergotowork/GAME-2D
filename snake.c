#include <stdio.h>
#include <snake.h>
#include <stdlib.h>
#include "DEV_Config.h"
#include "arm_2d_scene_0.h"

user_scene_0_t *gameScene = NULL;
// struct TFood *pfood = NULL;

int refreshgamew(user_scene_0_t *ptTarget, struct TSnake *psnake)
{
    int key = -1;

    if (!dev_read_key(KEY_RIGHT))
    {
        (psnake->dir == DIR_LEFT) ?: (psnake->dir = DIR_RIGHT);
        printf("push the RIGHT\n");
    }
    else if (!dev_read_key(KEY_DOWN))
    {
        (psnake->dir == DIR_UP) ?: (psnake->dir = DIR_DOWN);
        printf("push the DOWN\n");
    }
    else if (!dev_read_key(KEY_LEFT))
    {
        (psnake->dir == DIR_RIGHT) ?: (psnake->dir = DIR_LEFT);
        printf("push the LEFT\n");
    }
    else if (!dev_read_key(KEY_UP))
    {
        (psnake->dir == DIR_DOWN) ?: (psnake->dir = DIR_UP);
        printf("push the UP\n");
    }
    else if (!dev_read_key(KEY_B))
    {
        return 2;
    }

    // if (arm_2d_helper_is_time_out(99999999 /* 3000 */, &this.lTimestamp[0]))
    if (arm_2d_helper_is_time_out(300))
    {
        movesnake(psnake);
    }

    switch (checksnake(ptTarget->pfood, psnake))
    {
    case 0:
        break;

    case 1:
        ptTarget->ffood = False;
        if (++(ptTarget->g_level) > MAXLEVEL)
        {
            return 3;
        }
        arm_2d_op_wait_async(NULL);
        snakegrowup(ptTarget->pfood, psnake);
        break;

    default:
        return -1;
    }

    return 1;
}

/**
 * stuct TSnake is a chain, head->front point to the end of the snake
 * ?: [a]<-[b]<-[c]<-[d]    a?head
 *      |              ^     snake?????,??head??d,
 *      `--------------'     ????d?(y,x)?snake???????.
 */
void movesnake(struct TSnake *psnake)
{
    int hy = psnake->head->y;
    int hx = psnake->head->x;

    psnake->head = GetSnakeTail(psnake);

    switch (psnake->dir)
    {
    case DIR_UP:
        psnake->head->y = hy - food_size;
        psnake->head->x = hx;
        break;

    case DIR_DOWN:
        psnake->head->y = hy + food_size;
        psnake->head->x = hx;
        break;

    case DIR_LEFT:
        psnake->head->y = hy;
        psnake->head->x = hx - food_size;
        break;

    case DIR_RIGHT:
        psnake->head->y = hy;
        psnake->head->x = hx + food_size;
        break;

    default:
        break;
    }
}

int checksnake(struct TFood *pfood, struct TSnake *psnake)
{
    if (psnake->head->y < 0 || psnake->head->y > GAMEWIN_YLEN || psnake->head->x < 0 || psnake->head->x > GAMEWIN_XLEN)
    {
        // LOG_HERE;
        return -1;
    }

    struct TSnakeNode *pnode = GetSnakeTail(psnake);
    int i = 0;
    for (; i < psnake->length - 1; ++i, pnode = pnode->front)
    {
        if (psnake->head->y == pnode->y && psnake->head->x == pnode->x)
        {
            // LOG_HERE;
            return -1;
        }
    }

    if (psnake->head->y == pfood->y && psnake->head->x == pfood->x)
        return 1;

    return 0;
}

void snakegrowup(struct TFood *pfood, struct TSnake *psnake)
{
    struct TSnakeNode *pnode = (struct TSnakeNode *)malloc(sizeof(struct TSnakeNode));

    switch (psnake->dir)
    {
    case DIR_UP:
        pnode->y = psnake->head->y - food_size;
        pnode->x = psnake->head->x;
        break;

    case DIR_DOWN:
        pnode->y = psnake->head->y + food_size;
        pnode->x = psnake->head->x;
        break;

    case DIR_LEFT:
        pnode->y = psnake->head->y;
        pnode->x = psnake->head->x - food_size;
        break;

    case DIR_RIGHT:
        pnode->y = psnake->head->y;
        pnode->x = psnake->head->x + food_size;
        break;

    default:
        break;
    }

    pnode->front = GetSnakeTail(psnake);
    psnake->head->front = pnode;
    psnake->head = pnode;
    ++psnake->length;
}

void gameover(const arm_2d_tile_t *ptTarget, char *str)
{
    //    mvwprintw(win, (int)(GAMEWIN_YLEN/2), (GAMEWIN_XLEN/2 - strlen(str)/2), str);
    //    mvwprintw(win, (int)(GAMEWIN_YLEN/2 + 1), 20, "Press any key to quit...");
    //    wrefresh(win);

    arm_2d_canvas(ptTarget, __top_canvas)
    {
        /*-----------------------draw the foreground begin-----------------------*/

        /* following code is just a demo, you can remove them */

        // arm_2d_fill_colour(ptTarget, NULL, GLCD_COLOR_WHITE);

        arm_2d_align_centre(__top_canvas, ptTarget->tRegion.tSize)
        {
            draw_round_corner_box(ptTarget,
                                  &__centre_region,
                                  GLCD_COLOR_WHITE,
                                  255,
                                  1);

            arm_2d_op_wait_async(NULL);
        }

        /* draw text at the top-left corner */
        // if (arm_2d_helper_is_time_out(1000, &this.lTimestamp[0])) {
        arm_lcd_text_set_target_framebuffer((arm_2d_tile_t *)ptTarget);
        arm_lcd_text_set_colour(GLCD_COLOR_RED, GLCD_COLOR_WHITE);
        arm_lcd_text_set_font(&ARM_2D_FONT_16x24.use_as__arm_2d_font_t);
        arm_lcd_text_location(0, __GLCD_CFG_SCEEN_HEIGHT__ / 2);
        arm_lcd_puts(str);
        // }

        /*-----------------------draw the foreground end  -----------------------*/
    }
    int64_t tmp = arm_2d_helper_get_system_timestamp();
    while (arm_2d_helper_get_system_timestamp() - tmp < 3000)
    {
    }

    arm_2d_op_wait_async(NULL);
}

const arm_2d_tile_t *newgamew(const arm_2d_tile_t *ptTarget)
{
    arm_2d_fill_colour(ptTarget, NULL, GLCD_COLOR_WHITE);

    return ptTarget;
}

struct TSnake *initsnake()
{
    struct TSnake *psnake = (struct TSnake *)malloc(sizeof(struct TSnake));

    psnake->dir = DIR_RIGHT;
    psnake->length = 4;

    //    newsnakenode (
    //        &newsnakenode (
    //            &newsnakenode (
    //                &newsnakenode( &psnake->head, 20, 20 )->front, 20, 80
    //            )->front, 20, 60
    //        )->front, 20, 40
    //    )->front = psnake->head;
    struct TSnakeNode *tmp = newsnakenode(&psnake->head, 20, 120);

    tmp->front = newsnakenode(&tmp->front, 20, 180);
    tmp = tmp->front;
    tmp->front = newsnakenode(&tmp->front, 20, 160);
    tmp = tmp->front;
    tmp->front = newsnakenode(&tmp->front, 20, 140);
    tmp = tmp->front;
    tmp->front = psnake->head;

    return psnake;
}

struct TSnakeNode *newsnakenode(struct TSnakeNode **ppsnode, int x, int y)
{
    *ppsnode = (struct TSnakeNode *)malloc(sizeof(struct TSnakeNode));
    (*ppsnode)->y = y;
    (*ppsnode)->x = x;
    (*ppsnode)->front = NULL;

    return *ppsnode;
}

void destroysnake(struct TSnake *psnake)
{
    struct TSnakeNode *psnode = GetSnakeTail(psnake);
    struct TSnakeNode *ptmp = NULL;

    int i = 0;
    for (; i < psnake->length; ++i)
    {
        ptmp = psnode;
        psnode = psnode->front;
        free(ptmp);
    }

    free(psnake);
    psnake = NULL;
}

void mvwaddch(const arm_2d_tile_t *ptTarget,
              const int xx,
              const int yy,
              const int size)
{
    arm_2d_region_t my_region = {
        .tLocation = {
            .iX = xx,
            .iY = yy,
        },
        .tSize = {
            .iWidth = size,
            .iHeight = size,
        },
    };
    draw_round_corner_box(ptTarget,
                          &my_region,
                          GLCD_COLOR_RED,
                          255,
                          1);
}

// void drawsnakew(const arm_2d_tile_t *ptTarget, struct TSnake *psnake, const int size, struct TFood *pfood, bool flag)
void drawsnakew(const arm_2d_tile_t *ptTarget, TSnake *psnake, const int size)
{
    static int taily = 0;
    static int tailx = 0;

    // -------------------------
    // arm_2d_fill_colour(ptTarget, NULL, GLCD_COLOR_BLUE);

    if (taily != 0 && tailx != 0)
    {
        /* mvwaddch : draw the box */
        mvwaddch(ptTarget, tailx, taily, size);
    }

    /* #define GetSnakeTail(s)  ((s)->head->front) */
    struct TSnakeNode *psnode = GetSnakeTail(psnake);

    int i = 0;
    for (; i < psnake->length; ++i)
    {
        mvwaddch(ptTarget, psnode->x, psnode->y, size);
        psnode = psnode->front;
        // printf("the code come here, the psnode->y, psnode->x is : %d,%d\n",psnode->y,psnode->x );
    }
    taily = GetSnakeTail(psnake)->y;
    tailx = GetSnakeTail(psnake)->x;

    arm_2d_op_wait_async(NULL);
}

void drawfoodw(struct TFood *pfood, struct TSnake *psnake)
{
    int y, x;
    do
    {
        pfood->y = (rand() % (GAMEWIN_YLEN / food_size)) * food_size;
        pfood->x = (rand() % (GAMEWIN_XLEN / food_size)) * food_size;
    } while (False == checkfood(pfood, psnake));

    printf("the pfood x, y is %d, %d\n", pfood->x, pfood->y);
    arm_2d_op_wait_async(NULL);
}

/* if food equal to snake? */
TBool checkfood(struct TFood *pfood, struct TSnake *psnake)
{
    struct TSnakeNode *pnode = GetSnakeTail(psnake);

    int i = 0;
    for (; i < psnake->length; ++i, pnode = pnode->front)
    {
        if (pfood->y == pnode->y && pfood->x == pnode->x)
            return False;
    }
    return True;
}
