#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "base.h"
//#define U_DEBUG

void fun_0(void)
{
    printf("function 0 -.-\n");
}
void fun_1(void)
{
    printf("function 1 -.-\n");
}
void fun_2(void)
{
    printf("function 2 -.-\n");
}
void fun_3(void)
{
    printf("function 3 -.-\n");
}
void fun_4(void)
{
    printf("function 4 -.-\n");
}
void fun_5(void)
{
    printf("function 5 -.-\n");
}
void fun_6(void)
{
    printf("function 6 -.-\n");
}
void fun_7(void)
{
    printf("function 7 -.-\n");
}

ST_FUN_TABLE tFunMainMenu[] = 
{
    {0, "Menu Function 0", fun_0},
    {1, "Menu Function 1", fun_1},
    {2, "Menu Function 2", fun_2},
    {3, "Menu Function 3", fun_3},
    {4, "Menu Function 4", fun_4},
    {5, "Menu Function 5", fun_5},
    {6, "Menu Function 6", fun_6},
    {7, "Menu Function 7", fun_7},
    {8, "Menu Function 8", fun_7},
    {9, "Menu Function 9", fun_0},
    {10, "Menu Function 10", fun_1},
    {11, "Menu Function 11", fun_2},
    {12, "Menu Function 12", fun_3},
    {13, "Menu Function 13", fun_3},
    {14, "Menu Function 14", fun_4},
    {15, "Menu Function 15", fun_5},
    {16, "Menu Function 16", fun_6},
    {17, "Menu Function 17", fun_7},
    {18, "Menu Function 18", fun_7},
    {19, "Menu Function 19", fun_7},
};

void RunFun(ST_FUN_TABLE *tFunTab, int iAllItems, int iPageSel, int iItemSel)
{
    int iCount = (iPageSel - 1) * ITEM_PER_PAGE + iItemSel;
    if(iCount > iAllItems)
    {
        printf(" - Page or Item Select Error -\n");
        exit(-1);
    }
    debug_msg("%s\n", tFunTab[iCount-1].pStrItem);
    tFunTab[iCount-1].RunCaseFun();
}

void ListFun(ST_FUN_TABLE *tFunTab, int iAllItems, int iPage)
{
    int i, iListCount;
    int iBegin = (iPage - 1) * ITEM_PER_PAGE;

    if((iAllItems + ITEM_PER_PAGE - 1) / ITEM_PER_PAGE < iPage)
    {
        printf(" - Page Select Error -\n");
        exit(-1);    
    }
    
    iListCount = (iAllItems-iBegin)/ITEM_PER_PAGE ? ITEM_PER_PAGE : (iAllItems-iBegin);
/*    
    if((iAllItems - iBegin) / ITEM_PER_PAGE)
    {
        iListCount = ITEM_PER_PAGE;
    }
    else
    {
        iListCount = iAllItems - iBegin;
    }
*/
    debug_msg("iListCount = %d\n", iListCount);
    for(i=0; i<iListCount; i++)
        printf("%d: %s\n", i+1, tFunTab[iBegin+i].pStrItem);
}

void MenuSelect(void)
{
    int iItem = 1;
    int iPage = 1;
    int iMaxPage, iAllItems;
    int iGetKey;

    iAllItems = sizeof(tFunMainMenu) / sizeof(ST_FUN_TABLE);
    iMaxPage  = (iAllItems + ITEM_PER_PAGE - 1) / ITEM_PER_PAGE;
    debug_msg("iAllItems = %d\n", iAllItems);
    debug_msg("iMaxPage = %d\n", iMaxPage);
    printf(" == Main Menu == \n");
    ListFun(tFunMainMenu, sizeof(tFunMainMenu)/sizeof(ST_FUN_TABLE), iPage);

    while(1)
    {
        debug_msg(" == Main Menu == \n");
        debug_msg("iPage = %d, iItem = %d\n", iPage, iItem);
        iGetKey = getchar();
//        scanf("%c", &iGetKey);
        switch(iGetKey)
        {
            case KEYUP:
                iPage = (iPage <= 1 ? iMaxPage : iPage-1);
            /*
                if(iPage <= 1)
                    iPage = iMaxPage;
                else
                    iPage--;
            */
                break;
            case KEYDOWN:
                iPage = (iPage >= iMaxPage ? 1 : iPage+1);
            /*
                if(iPage >= iMaxPage)
                    iPage = 1;
                else
                    iPage++;
            */
                break;
            case KEY1:
            case KEY2:
            case KEY3:
                RunFun(tFunMainMenu, sizeof(tFunMainMenu)/sizeof(ST_FUN_TABLE), iPage, iItem);
                break;
            default:
//                exit(-1);
                goto end;
                break;
        }
//        iPage++;
//        iItem++;
        printf(" == Main Menu == \n");
        ListFun(tFunMainMenu, sizeof(tFunMainMenu)/sizeof(ST_FUN_TABLE), iPage);
end:
        ;
    }
}

void menu_test(void)
{
    MenuSelect();
}

