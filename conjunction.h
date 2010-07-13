#ifndef _CONJUNCTION_H
#define _CONJUNCTION_H

#define CDEF(id, f1, f2, f, g, l, r, m) \
    func_def(id, CONJ, f1, f2, f, g, NULL, l, r, m, 0)

#define CDERV(id, f1, f2, f, g, l, r, m) \
    func_def(id, VERB, f1, f2, f, g, NULL, l, r, m, 0)

#endif
