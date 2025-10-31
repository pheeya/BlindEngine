#ifndef BE_LIST
#define BE_LIST

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void *items;
  uint32_t fixedCount;
  uint32_t currentMaxCount;
  uint32_t count;
  size_t itemSize;
  bool fixed;
  bool isPointerList;
} list_t;

list_t *list_create_fixed(uint32_t _fixedCount, size_t _itemSize,
                          bool _isPointerList);
list_t *list_create_dynamic(size_t _itemSize, uint32_t _initialMaxCount,
                            bool _isPointerList);

void list_destroy(list_t *_list);

void *list_pop(list_t *_list);
void *list_add(list_t *_list, void *_item);
void list_clear(list_t *_list);

void *list_getAt(list_t *_list, size_t _index);
void list_setAt(list_t *_list, size_t _index, void *_item);

// BeList

typedef struct {
  size_t count;
  size_t cap;
  size_t stride;
  void* data;
} BeList;

BeList *be_list_create(size_t _initialCapacity, size_t _stride);
void* be_list_append(BeList* _to, void* _data);
void* be_list_get_at(BeList* _from, size_t _at);
void be_list_free(BeList* _list);
void be_list_clear(BeList* _list);
//void be_list_insert_at(BeList* _list, size_t _at);

#endif
