#include <string.h>

void* memset(void* buf_v, int val, size_t size) {
    unsigned char* buf = (unsigned char*) buf_v;
    for(size_t i=0; i<size; ++i) {
        buf[i] = (unsigned char) val;
    }
    return buf_v;
}
