#ifndef PAGE_STRUCTS_H
#define PAGE_STRUCTS_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char name[20];
    char **node_array;
    uint16_t start_address;
    size_t length;
} Page;


typedef struct {
uint16_t start_addr;
size_t length;
Page *page;
} ModbusAddress;

#endif//PAGE_STRUCTS_H