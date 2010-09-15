#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "symbol.h"
#include "verb.h"
#include "lexer.h"
#include "parser.h"
#include "util.h"

C charf(A z) { C *v=CAV(z); R v[0];       }
C charl(A z) { C *v=CAV(z); R v[AN(z)-1]; }
I intf(A z)  { I *v=IAV(z); R v[0];       }
I intl(A z)  { I *v=IAV(z); R v[AN(z)-1]; }

A scalar(I t, I v) { A z=ga(t,0,1,NULL);    *IAV(z)=v; R z; }
A schar(C c)       { A z=ga(CHAR,0,1,NULL); *CAV(z)=c; R z; }
A sbool(B b)       { A z=ga(BOOL,0,1,NULL); *BAV(z)=b; R z; }
A sint(I i)        { A z=ga(INT,0,1,NULL);  *IAV(z)=i; R z; }
A sflt(D d)        { A z=ga(FLT,0,1,NULL);  *DAV(z)=d; R z; }
A scmpx(D r, D i)  { A z=ga(CMPX,0,1,NULL);
    Z *zv=ZAV(z); zv->re=r; zv->img=i;
    R z;
}
MONAD(sbox)        { A z=ga(BOX,0,1,NULL);  *AAV(z)=y; R z; }

VO a_init(VO) {
    gcinit();
    zero=sbool(0);       rsta(zero);
    one=sbool(1);        rsta(one);
    ten=sint(10);        rsta(ten);
    zone=scmpx(0,1);     rsta(zone);
    alcl=scalar(ASGN,0); rsta(alcl);
    agbl=scalar(ASGN,1); rsta(agbl);
    ace=gsa(BOX,0,0,NULL);
    mark=gsa(MARK,0,0, NULL);
    lpar=gsa(LPAR,0,0, NULL);
    rpar=gsa(RPAR,0,0, NULL);
    symbinit();
}

VO a_clean(VO) {
    freea(zero); freea(one);
    freea(ten);  freea(zone);
    freea(alcl); freea(agbl);
    freea(mark); freea(lpar);
}

I a_strtoi(I n, C *s, C **e) {  R (I)a_strtod(n,s,e); }

D a_strtod(I n, C *s, C**e) { I si=1; D v, p;
    if (*s==CUNDS) { si=-1; s++; }
    for (v=0;isdigit(*s);) { v=(10*v)+(*s++-'0'); }
    if (*s=='.') { s++; }
    for (p=1;isdigit(*s);) { v=(10*v)+(*s++-'0'); p*=10; }
    *e=s;
    R si*(v/p);
}

A eval(const C *str) { A w, z;
    w=gstr(strlen(str)+1,str);
    z=parse(tokens(w));
    R z;
}

VO a_repl(const C *s) { C *v, str[100]; A z;
    do {
        printf("%s",s);
        v=fgets(str,SIZ(str),stdin);
        if (!v) { break; }
        v=strndup(str,strlen(str)-1); /* remove carriage return */
        println(z=eval(v));
        free(v);
    } while (v);
}
