#include <string.h>

int memcmp(const void* a_v, const void* b_v, size_t size) {
    const unsigned char* a;
    const unsigned char* b;
    a = (const unsigned char*) a_v;
    b = (const unsigned char*) b_v;
    for(size_t i=0; i<size; ++i) {
        if(a[i] < b[i]) {
            return -1;
        }else if(b[i] < a[i]) {
            return 1;
        }
    }
    return 0;
}
