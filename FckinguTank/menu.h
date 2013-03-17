#ifndef U_MENU_H
#define U_MENU_H

typedef struct st_fun_table
{
    int  iFunIdx;
    char *pStrItem;
    void (*RunCaseFun)(void);
}ST_FUN_TABLE;

#define ITEM_PER_PAGE   3

#define KEYUP           'j'
#define KEYDOWN         'k'
#define KEY1            '1'
#define KEY2            '2'
#define KEY3            '3'

void RunFun(ST_FUN_TABLE *tFunTab, int iAllItems, int iPageSel, int iItemSel);
void ListFun(ST_FUN_TABLE *tFunTab, int iAllItems, int iPage);
void MenuSelect(void);
void menu_test(void);

#endif /* U_MENU_H */
