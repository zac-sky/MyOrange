// sds.h
#ifndef SDS_H
#define SDS_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct {
    int len;    // 当前字符串长度
    int alloc;  // 分配的内存大小
    char buf[]; // 字符缓冲区
} sds;

// SDS 函数原型
sds *sds_new(const char *init);
void sds_free(sds *s);
char *sds_get(sds *s);

#endif // SDS_H
