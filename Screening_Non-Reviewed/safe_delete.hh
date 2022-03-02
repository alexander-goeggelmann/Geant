
#ifndef SAFE_DEL
#define SAFE_DEL 1

#define SAFE_DELETE(p) \
if (p != NULL) \
    { \
        delete p; \
        p = NULL; \
    }

#endif
