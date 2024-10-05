#ifndef __DATABASE_H__
#define __DATABASE_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>

using std::map;

typedef struct{
    int len;  //已使用空间大小
    int alloc;  //总共申请的空间大小(包括未使用的)
    char buf[];  //真实存储字符串的字节数组
}sds;

sds *sds_new(const char* init);
void sds_free(sds* s);
char *sds_get(sds* s);


void set_command(const char* key,const char* value);
void get_command(const char* key);
void delete_command(const char* key);
void process_command(const char* command);

#endif