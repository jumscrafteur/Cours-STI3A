#ifndef _TRI_H_
#define _TRI_H_

#define ECHANGE(v1, v2, type) \
    {                         \
        type v = v1;          \
        v1 = v2;              \
        v2 = v;               \
    }
#define TRI(v1, v2, v3, type)      \
    {                              \
        if (v1 > v2)               \
            ECHANGE(v1, v2, type); \
        if (v2 > v3)               \
            ECHANGE(v2, v3, type); \
        if (v1 > v2)               \
            ECHANGE(v1, v2, type); \
    }
#endif