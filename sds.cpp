// sds.cpp
#include "sds.h"

// 创建新的 SDS
sds *sds_new(const char *init) {
    size_t init_len = strlen(init);
    sds *s = (sds *)malloc(sizeof(sds) + init_len + 1);
    if (s == NULL) return NULL;
    s->len = init_len;
    s->alloc = init_len;
    memcpy(s->buf, init, init_len + 1);
    return s;
}

// 释放 SDS
void sds_free(sds *s) {
    if (s) free(s);
}

// 获取 SDS 字符串
char *sds_get(sds *s) {
    return s->buf;
}

