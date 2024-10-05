// database.cpp
#include "db.h"

std::map<sds *, sds *> database;

// 使用自定义比较器的全局数据库
// 设置命令
void set_command(sds *key, sds *value) {
    database[key] = value;
    printf("Set %s to %s\n", sds_get(key), sds_get(value));
}

// 获取命令
void get_command(sds *key) {
    auto it = database.find(key);
    if (it != database.end()) {
        printf("Value for1 %s: %s\n", sds_get(it->first), sds_get(it->second));
    } else {
        printf("Key %s not found1\n", sds_get(it->first));
    }
}

// 删除命令
void delete_command(sds *key) {
    if (database.erase(key)) {
        printf("Deleted key: %s\n", sds_get(key));
    } else {
        printf("Key %s not found\n", sds_get(key));
    }
}

// 处理命令
void process_command(const char *command) {
    char op[10], key_buf[256], value_buf[256];
    
    // 解析命令
    if (sscanf(command, "%s %s %s", op, key_buf, value_buf) < 2) {
        printf("Illegal Input\n");
        return;
    }

    // 创建 SDS 结构
    sds *key = sds_new(key_buf);
    sds *value = nullptr;

    // 处理命令
    if (strcmp(op, "set") == 0) {
        value = sds_new(value_buf); // 仅在 set 操作时创建 value
        set_command(key, value);
    } else if (strcmp(op, "get") == 0) {
        get_command(key);
    } else if (strcmp(op, "delete") == 0) {
        delete_command(key);
    } else {
        printf("Illegal Input\n");
    }

    // 释放内存
    sds_free(key);
    if (value) sds_free(value);
}

