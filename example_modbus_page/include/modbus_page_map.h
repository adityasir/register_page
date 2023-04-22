#ifndef MODBUS_PAGE_MAP_H
#define MODBUS_PAGE_MAP_H

#include <page_struct.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    ModbusAddress *address_array;
    size_t array_size;
    void (*init)(void);
	int (*add_new_page)(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr, size_t length,const char *name);
	Page *(*page_lookup)(ModbusAddress *address_array, size_t array_size, uint16_t start_addr);
    int (*delete_page)(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr);
    int (*add_register_to_page)(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr, char **ptree_array, size_t ptree_size);
    void (*print_register_of_page)(ModbusAddress *address_array, size_t array_size, uint16_t start_addr, size_t length);
} modbus_address_handler;

extern modbus_address_handler handle_modbus_address; // declare the variable

#endif
