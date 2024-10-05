#include "database.h"

// 创建 SDS
sds *sds_new(const char *init) {
    size_t init_len = strlen(init);
    sds *s = (sds *)malloc(sizeof(sds) + init_len + 1);
    if (s == NULL) return NULL;
    s->len = init_len;
    s->malloc = init_len;
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

// 全局数据库
map<string, string> database;

void set_command(const char *key, const char *value) {
    database[key] = value;
    printf("Set %s to %s\n", key, value);
}

void get_command(const char *key) {
    auto it = database.find(key);
    if (it != database.end()) {
        printf("Value for %s: %s\n", key, it->second.c_str());
    } else {
        printf("Key %s not found\n", key);
    }
}

void delete_command(const char *key) {
    if (database.erase(key)) {
        printf("Deleted key: %s\n", key);
    } else {
        printf("Key %s not found\n", key);
    }
}

void process_command(const char *command) {
    char op[10], key[256], value[256];
    if (sscanf(command, "%s %s %s", op, key, value) < 2) {
        printf("Illegal Input\n");
        return;
    }

    if (strcmp(op, "set") == 0) {
        set_command(key, value);
    } else if (strcmp(op, "get") == 0) {
        get_command(key);
    } else if (strcmp(op, "delete") == 0) {
        delete_command(key);
    } else {
        printf("Illegal Input\n");
    }
}
