#include <stdio.h>
#include <stdlib.h>

#include "modbus_page_map.h"

int main() 
{
	printf("modbus_address: %p\n", &handle_modbus_address);
    handle_modbus_address.init();

    // Allocate memory for the address array
    handle_modbus_address.address_array = malloc(0);
    /*
	// Add new page
    if(handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100, 10, "Page 1"))
    {
        printf("Page added: [100 ~ 10] Page 1\n");
    }

    // Add new page with same start address as Page 1
    if(handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100, 10, "Page 2"))
    {
        printf("Page added: [100 ~ 10] Page 2\n");
    }
    else
    {
        printf("Error: Page with the same start address already exists.\n");
    }

    // Add new page with overlapping address range as Page 1
    if(handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 105, 10, "Page 3"))
    {
        printf("Page added: [105 ~ 10] Page 3\n");
    }
    else
    {
        printf("Error: Overlapping address range with existing page.\n");
    }

 	// Add new page with overlapping address range as Page 1
    if(handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 113, 10, "Page 3"))
    {
        printf("Page added: [111 ~ 10] Page 3\n");
    }
    else
    {
        printf("Error: Overlapping address range with existing page.\n");
    }

    uint16_t register_addr = 105;
	Page *page = handle_modbus_address.page_lookup(handle_modbus_address.address_array, handle_modbus_address.array_size, register_addr);
    if (page != NULL) {
        printf("Page name: %s\n", page->name);
    } else {
        printf("No matching page found");
    }
    */
    //handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100, 10, "Page 1");
    //handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 110, 10, "Page 2");
    //handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 120, 10, "Page 3");
    //handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 130, 10, "Page 4");
    //print_pages(handle_modbus_address.address_array, handle_modbus_address.array_size);
    //handle_modbus_address.delete_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100);

    //print_pages(handle_modbus_address.address_array, handle_modbus_address.array_size);

    handle_modbus_address.add_new_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100, 10, "Page 1");
    print_pages(handle_modbus_address.address_array, handle_modbus_address.array_size);
    char *example_node[] = {"i32", "u32","e32", "s32"};
    size_t example_node_size = sizeof(example_node) / sizeof(example_node[0]);
    handle_modbus_address.add_register_to_page(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100, example_node, example_node_size);

    
   //print_register_of_page_(handle_modbus_address.address_array, handle_modbus_address.array_size, 100, 4);
   // print_register_of_page_(&handle_modbus_address.address_array, &handle_modbus_address.array_size, 100, 4);




    free(handle_modbus_address.address_array);

    return 1;
}
