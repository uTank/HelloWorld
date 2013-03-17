#include <stdlib.h>
#include "datastruct.h"


/************************************************************/
status triplet_init(ptriplet t, elemtype v1, elemtype v2, elemtype v3)
{
    t = malloc(3*sizeof(elemtype));
    if(!t)
        exit(OVERFLOW);
    t[0] = v1;
    t[1] = v2;
    t[2] = v3;

    return OK;
}
status triplet_destroy(ptriplet t)
{
    free(t);
    t = NULL;
    return OK;
}
status triplet_get(ptriplet t, int i, elemtype *e)
{
    if(i < 1 || i > 3 || e == NULL)
        return ERROR;
    *e = t[i-1];
    return OK;
}
status triplet_put(ptriplet t, int i, elemtype e)
{
    if(i < 1 || i > 3)
        return ERROR;
    t[i-1] = e;
    return OK;
}
status triplet_isascend(ptriplet t)
{
    return (t[0] <= t[1]) && (t[1] <= t[2]);
}
status triplet_isdescend(ptriplet t)
{
    return (t[0] >= t[1]) && (t[1] >= t[2]);
}
status triplet_max(ptriplet t, elemtype *e)
{
    *e = (t[0] >= t[1]) ? (t[0] >= t[2] ? t[0] : t[2])
                        : (t[1] >= t[2] ? t[1] : t[2]);
    return OK;
}
status triplet_min(ptriplet t, elemtype *e)
{
    *e = (t[0] <= t[1]) ? (t[0] <= t[2] ? t[0] : t[2])
                        : (t[1] <= t[2] ? t[1] : t[2]);
    return OK;
}
/************************************************************/

/************************************************************/

/************************************************************/

/************************************************************/

/************************************************************/

/************************************************************/

