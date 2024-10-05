// database.h
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include "sds.h"

// 使用自定义比较器的全局数据库
extern std::map<sds *, sds *> database;

// 数据库函数原型
void set_command(sds *key, sds *value);
void get_command(sds *key);
void delete_command(sds *key);
void process_command(const char *command);

#endif // __DATABASE_H__
