#define ALLOCSIZE 10000

#undef NULL
#define NULL 0

static char allocbuf[ALLOCSIZE];
/* allocp points at the next free byte */
static char *allocp = allocbuf;

char *alloc(int bytes) {
    if (allocbuf + ALLOCSIZE - allocp >= bytes) {
        /* there are enough bytes to satisfy the request */
        allocp += bytes;
        /* Now return the old pointer */
        return allocp - bytes;
    } else
        return NULL;
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        /* Check if the pointer to deallocate is in range */
        allocp = p;
}
