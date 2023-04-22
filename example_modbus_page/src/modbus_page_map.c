#include "modbus_page_map.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void init_() {
    printf("Inside init_()\n");
    printf("address_array: %p\n", handle_modbus_address.address_array);
}

void print_pages(ModbusAddress *address_array, size_t array_size) {
    printf("Modbus Address\tPage\n");
    for (size_t i = 0; i < array_size; i++) {
        printf("[%ld, %ld]\t%s\n", (unsigned long)address_array[i].start_addr, (unsigned long)(address_array[i].start_addr + address_array[i].length - 1), address_array[i].page->name);
    }
}




/**
 * Checks if a page with the given start address and length already exists in the array of Modbus addresses.
 *
 * @param address_array The array of Modbus addresses to search.
 * @param array_size The current size of the address array.
 * @param new_start_addr The start address of the new page to add.
 * @param new_length The length of the new page to add.
 * @return 1 if a page with the same start address already exists, 0 otherwise.
 */
int check_if_page_exists(ModbusAddress **address_array, size_t *array_size, uint16_t new_start_addr, size_t new_length)
{
    // Check if page with the same start address already exists
    printf("%s(%d)\n", __func__, new_start_addr);
    for (size_t i = 0; i < *array_size; i++) {
        printf("%s[%u ~ %zu]\n", (*address_array)[i].page->name, (*address_array)[i].start_addr, (*address_array)[i].length);

        const size_t current_end_addr = (*address_array)[i].start_addr + (*address_array)[i].length - 1; 
        const size_t new_end_addr = new_start_addr + new_length - 1; 
        printf("[ %ld ] ~ [%ld]\n", current_end_addr, new_end_addr);

        if (new_start_addr <= current_end_addr && new_end_addr >= (*address_array)[i].start_addr) {
            printf("Error: Page with the same start address already exists.\n");
            return 1;
        }
    }
    //printf("Page with start address %d does not exist.\n", start_addr);
    return 0;
}



int add_new_page_(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr, size_t length, const char *name) 
{

	if (check_if_page_exists(address_array, array_size, start_addr, length)) {
        printf("Error: Page with the same start address already exists.\n");
        return 0;
    }

    printf("Adding new page: start_addr=%u, length=%zu, name=%s\n", start_addr, length, name);

	ModbusAddress *new_array = realloc(
		*address_array, (*array_size + 1) * sizeof(ModbusAddress));
	if (new_array == NULL) {
		printf("Error: Memory allocation failed while adding new page.\n");
		return 0;
	}
	*address_array = new_array;
	(*address_array)[*array_size].start_addr = start_addr;
	(*address_array)[*array_size].length = length;
	(*address_array)[*array_size].page = malloc(sizeof(Page));
	if ((*address_array)[*array_size].page == NULL) {
		printf("Error: Memory allocation failed while adding new page.\n");
		return 0;
	}
	strncpy((*address_array)[*array_size].page->name, name,
		sizeof((*address_array)[*array_size].page->name));
	(*array_size)++;
    
    printf("New page added: start_addr=%u, length=%zu, name=%s, array_size=%zu\n",
        (*address_array)[*array_size-1].start_addr, (*address_array)[*array_size-1].length,
        (*address_array)[*array_size-1].page->name, *array_size);

	return 1;
}


int delete_page_(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr) {
    int i, j;
    for (i = 0; i < *array_size; i++) {
        if ((*address_array)[i].start_addr == start_addr) {
            // Free memory allocated for the page
            free((*address_array)[i].page);

            // Move remaining elements in the array one position to the left
            for (j = i + 1; j < *array_size; j++) {
                (*address_array)[j - 1] = (*address_array)[j];
            }

            // Resize the array to remove the last element
            ModbusAddress *new_array = realloc(
                *address_array, (*array_size - 1) * sizeof(ModbusAddress));
            if (new_array == NULL) {
                printf("Error: Memory allocation failed while deleting page.\n");
                return 0;
            }
            *address_array = new_array;
            (*array_size)--;

            printf("Page with start address %u deleted.\n", start_addr);
            return 1;
        }
    }

    printf("Error: Page with start address %u not found.\n", start_addr);
    return 0;
}



Page *page_lookup_(ModbusAddress *address_array, size_t array_size, uint16_t register_addr) 
{	
	for (size_t i = 0; i < array_size; i++) 
	{
		if (register_addr >= address_array[i].start_addr && register_addr < address_array[i].start_addr +   address_array[i].length) 
		{
			return address_array[i].page;
		}
	}
	return NULL;
}

int add_register_to_page_(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr, char **ptree_array, size_t ptree_size) {
    printf("\n %s \n", __func__);

    /*
    if (check_if_page_exists(address_array, array_size, start_addr, ptree_size)) {
        printf("Error: Page with the same start address already exists.\n");
        return 0;
    }
    */

    printf("Adding new page: start_addr=%u, ptree_size=%zu\n", start_addr, ptree_size);

    ModbusAddress *new_array = realloc(*address_array, (*array_size + 1) * sizeof(ModbusAddress));
    if (new_array == NULL) {
        printf("Error: Memory allocation failed while adding new page.\n");
        return 0;
    }
    *address_array = new_array;
    (*address_array)[*array_size].start_addr = start_addr;
    (*address_array)[*array_size].length = ptree_size;
    (*address_array)[*array_size].page = malloc(sizeof(Page));
    if ((*address_array)[*array_size].page == NULL) {
        printf("Error: Memory allocation failed while adding new page.\n");
        return 0;
    }

    // Allocate the node_array
    (*address_array)[*array_size].page->node_array = malloc(ptree_size * sizeof(char *));
    if ((*address_array)[*array_size].page->node_array == NULL) {
        printf("Error: Memory allocation failed while adding new page.\n");
        return 0;
    }

    // Copy the ptree_array to the node_array
    for (size_t i = 0; i < ptree_size; i++) {
        (*address_array)[*array_size].page->node_array[i] = malloc(20 * sizeof(char));
        if ((*address_array)[*array_size].page->node_array[i] == NULL) {
            printf("Error: Memory allocation failed while adding new page.\n");
            return 0;
        }
        strncpy((*address_array)[*array_size].page->node_array[i], ptree_array[i], 20);
    }

    (*array_size)++;

    printf("New page added: start_addr=%u, ptree_size=%zu, array_size=%zu\n",
        (*address_array)[*array_size-1].start_addr, (*address_array)[*array_size-1].length, *array_size);

    
    // Print the added page content
    printf("Added page content:\n");
    printf("Start address: %u\n", (*address_array)[*array_size-1].page->start_address);
    printf("Length: %zu\n", (*address_array)[*array_size-1].page->length);
    printf("Node array:\n");
    for (size_t i = 0; i < ptree_size; i++) {
        printf("%s\n", (*address_array)[*array_size-1].page->node_array[i]);
    }
    
    return 1;
}


void print_register_of_page_(ModbusAddress **address_array, size_t *array_size, uint16_t start_addr, size_t length) {
    printf("\n %s \n", __func__);
    
    // Find the page that matches the given start address
    int page_index = -1;
    for (size_t i = 0; i < *array_size; i++) {
        if ((*address_array)[i].start_addr == start_addr) {
            page_index = i;
            break;
        }
    }
    
    if (page_index == -1) {
        printf("Error: Page with start address %u not found.\n", start_addr);
        return;
    }
    
    // Print the page information
    printf("Page information:\n");
    printf("Start address: %u\n", (*address_array)[page_index].start_addr);
    printf("Page length: %zu\n", (*address_array)[page_index].length);
    
    // Make sure that the requested length is not greater than the length of the page
    if (length > (*address_array)[page_index].length) {
        printf("Error: Requested length %zu is greater than page length %zu.\n", length, (*address_array)[page_index].length);
        return;
    }
    
    // Print the page's register array
    printf("Register array:\n");
    for (size_t i = 0; i < length; i++) {
        printf("%s\n", (*address_array)[page_index].page->node_array[i]);
    }
}



modbus_address_handler handle_modbus_address = { 
    .address_array = NULL,
    .array_size = 0,
    .init = init_,
	.add_new_page = add_new_page_,
	.page_lookup = page_lookup_,
    .delete_page = delete_page_,
    .add_register_to_page = add_register_to_page_,
    .print_register_of_page = print_register_of_page_
};

