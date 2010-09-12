#include <stdio.h>

#include "anicca.h"
#include "symbol.h"
#include "print.h"

VO print(A y) { C *cv; I yn=AN(y), *iv; D *dv; Z *zv; V *vv; A *bv; SY *sy;

    if (!y) { printf("NULL"); R; }

    switch (AT(y)) {
    case BOOL: { cv=BAV(y); DO(yn, printf("%d ",(I)cv[i])); break; }
    case NAME:
    case CHAR: { cv=CAV(y); DO(yn, printf("%c",cv[i]));     break; }
    case INT:  { iv=IAV(y); DO(yn, printf("%d ",iv[i]));    break; }
    case FLT:  { dv=DAV(y); DO(yn, printf("%f ",dv[i]));    break; }
    case CMPX: {
        zv=ZAV(y); DO(yn, printf("%fj%f ",ZR(zv[i]),ZI(zv[i]))); break;
    }
/* TODO?: fancy line drawings */
    case BOX: {
        bv=AAV(y);
        DO(AN(y), printf("(<");
           print(bv[i]);
           printf(")%s", (i+1 == AN(y))?"":",")
        );
        break;
    }
    case VERB: case ADV: case CONJ: {
        vv=VAV(y);
        printf("%c ", vv->id);
        if (VF(vv)) { print(vv->f);
            if (VG(vv)) { print(vv->g);
                if (VH(vv)) { print(vv->h); };
            }
        };
        break;
    }
    case SYMB: {
        sy=SYAV(y);
        DO(AN(y), printf("(<");
           printf("nm: "); print(sy->name); printf(" vl: "); print(sy->value);
           printf(")%s", (i+1 == AN(y))?"":",");
           sy++;
        );
        break;
    }
    case LPAR: { printf("LPAR"); break; }
    case RPAR: { printf("RPAR"); break; }
    case ASGN: { intf(y) ? printf("=:") : printf("=."); break; }
    case MARK: { break; }
    default:   { printf("HUH?"); break; }
    }
}

VO println(A y) { if (!(AT(y)&MARK)) { print(y); printf("\n"); } }
