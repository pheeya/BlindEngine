#ifndef LIST_TYPE 
#define LIST_TYPE 

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    void *items;
    uint32_t fixedCount;
    uint32_t currentMaxCount;
    uint32_t count;
    size_t itemSize;
    bool fixed;
    bool isPointerList;
} list_t;

list_t *list_create_fixed(uint32_t _fixedCount, size_t _itemSize, bool _isPointerList);
list_t *list_create_dynamic(size_t _itemSize, uint32_t _initialMaxCount, bool _isPointerList);


void list_destroy(list_t *_list);

void *list_pop(list_t *_list);
void *list_add(list_t *_list, void* _item);
void list_clear(list_t *_list);

void *list_getAt(list_t *_list, size_t _index);
void list_setAt(list_t *_list, size_t _index, void* _item);



#endif 