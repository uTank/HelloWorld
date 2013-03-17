#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#ifndef TRUE 
#define TRUE          1
#endif 

#ifndef FALSE 
#define FALSE         0
#endif 

#ifndef OK
#define OK            1
#endif

#ifndef ERROR
#define ERROR         0
#endif

#ifndef INFEASIBLE
#define INFEASIBLE   -1
#endif

#ifndef OVERFLOW
#define OVERFLOW     -2
#endif

typedef int status;
typedef int elemtype;

/*****************************************/
typedef elemtype * ptriplet;
status triplet_init(ptriplet t, elemtype v1, elemtype v2, elemtype v3);
status triplet_destroy(ptriplet t);
status triplet_get(ptriplet t, int i, elemtype *e);
status triplet_put(ptriplet t, int i, elemtype e);
status triplet_isascend(ptriplet t);
status triplet_isdescend(ptriplet t);
status triplet_max(ptriplet t, elemtype *e);
status triplet_min(ptriplet t, elemtype *e);
/*****************************************/

/*****************************************/

/*****************************************/

#endif /* DATA_STRUCT_H */

