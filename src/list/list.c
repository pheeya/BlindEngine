#include "list.h"
#include <be_assert.h>
list_t *list_create_fixed(uint32_t _fixedCount, size_t _itemSize,
                          bool _isPointerList) {
  list_t *l = (list_t *)malloc(sizeof(list_t));
  ASSERT_MALLOC(l);
  l->fixed = true;
  l->fixedCount = _fixedCount;
  l->items = malloc(_itemSize * _fixedCount);
  ASSERT_MALLOC(l->items);
  l->itemSize = _itemSize;
  l->count = 0;
  l->isPointerList = _isPointerList;

  return l;
}

list_t *list_create_dynamic(size_t _itemSize, uint32_t _initialMaxCount,
                            bool _isPointerList) {
  list_t *l = (list_t *)malloc(sizeof(list_t));
  ASSERT_MALLOC(l);
  l->fixed = false;
  l->fixedCount = 0;
  l->items = malloc(_itemSize * _initialMaxCount);
  ASSERT_MALLOC(l->items);
  l->itemSize = _itemSize;
  l->currentMaxCount = _initialMaxCount;
  l->count = 0;
  l->isPointerList = _isPointerList;

  return l;
}

void list_destroy(list_t *_l) {
  if (!_l->isPointerList) {
    free(_l->items);
  }
  free(_l);
}

void *list_add(list_t *_l, void *_item) {
  if (_l->fixed && _l->count == _l->fixedCount) {
    printf("Tried to add to a full list\n");
    exit(1);
  }
  if (!_l->fixed && _l->currentMaxCount == _l->count) {

    // uint8_t because we're getting a pointer to a single byte, the first byte
    // in the list's data

    void *new = realloc(_l->items, _l->currentMaxCount * 2 * _l->itemSize);
    ASSERT_REALLOC(_l->items, new);

    _l->items = new;
    _l->currentMaxCount *= 2;
  }

  uint8_t *location;
  location = _l->items;
  location += (_l->count * _l->itemSize);
  if (_l->isPointerList) {
    *(void **)location = _item;
  } else {
    memcpy(location, _item, _l->itemSize);
  }
  _l->count++;
  return location;
}

void list_clear(list_t *_list) { _list->count = 0; }

void *list_pop(list_t *_l) {
  if (_l->count == 0) {
    printf("Couldn't pop from list for it is empty\n");
    return NULL;
  }
  uint8_t *item = (_l->items + --_l->count * _l->itemSize);

  return item;
}

void *list_getAt(list_t *_l, size_t _index) {

  if (_index >= _l->count) {
    printf("index out of list range\n");
    exit(1);
  };
  return (uint8_t *)_l->items + (_index * _l->itemSize);
}

void list_setAt(list_t *_l, size_t _index, void *_item) {
  if (_index >= _l->count) {
    printf("index out of list range\n");
    exit(1);
  };

  if (_l->isPointerList) {
    uint8_t *location = (uint8_t *)_l->items + (_index * _l->itemSize);

    *(void **)location = _item;
  }

  else {
    memcpy((uint8_t *)_l->items + (_index * _l->itemSize), _item, _l->itemSize);
  }
}

// BeList

BeList *be_list_create(size_t _initialCapacity, size_t _stride) {
  if (_initialCapacity < 8) {
    _initialCapacity = 8;
  }
  BeList *list = malloc(sizeof(BeList));
  list->stride = _stride;
  list->data = malloc(_stride * _initialCapacity);
  list->cap = _initialCapacity;
  list->count = 0;
  return list;
}

void *be_list_append(BeList *_to, void *_data) {
  if (_to->count == _to->cap) {
    size_t newCap = _to->cap * 2;
    _to->data = realloc(_to->data, newCap * _to->stride);
    _to->cap = newCap;
  }
  uint8_t *location = _to->data + _to->stride * _to->count;
  memcpy(location, _data, _to->stride);
  return location;
}

void *be_list_get_at(BeList *_from, size_t _at) { return &_from->data[_at]; }

void be_list_free(BeList *_list) {
  free(_list->data);
  free(_list);
}
void be_list_clear(BeList *_list) { _list->count = 0; }

//void be_list_insert_at(BeList* _list, size_t _at){
//
//}
