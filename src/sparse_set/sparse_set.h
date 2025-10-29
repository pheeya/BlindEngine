#ifndef SPARSE_SET
#define SPARSE_SET
#include <stdint.h>
#include <stdbool.h>

#define SPARSE_SET_STORAGE_MODE_DENSE  0
#define SPARSE_SET_STORAGE_MODE_SPARSE  1

typedef struct
{
    uint32_t count;
    uint32_t *content;
} memory_page_t;
typedef struct
{
    memory_page_t **pagePointers;
    uint32_t count;
    uint32_t capacity;
    uint32_t pageSize;
} memory_page_array_t;

typedef struct
{
    uint32_t count;
    void *content;
} data_page_t;

typedef struct
{
    data_page_t **pagePointers;
    uint32_t count;
    uint32_t capacity;
    uint32_t pageSize;
} data_page_array_t;

typedef struct
{

    memory_page_array_t indicesPages;
    memory_page_array_t reversePages;
    data_page_array_t dataPages;

    uint32_t dataSize;
    uint32_t dataCount;
    uint32_t nullValue;
    uint8_t storageMode;
} sparse_set_t;

sparse_set_t *sparse_set_create(uint32_t _initialCapacity, uint32_t _maxIndices, uint32_t _dataSize, uint32_t nullValue);

void *sparse_set_get(sparse_set_t *_set, uint32_t _index);

void sparse_set_insert(sparse_set_t *_set, uint32_t _index, void *_data);

bool sparse_set_remove(sparse_set_t *_set, uint32_t _index);

void sparse_set_release(sparse_set_t *_set);

bool sparse_set_exists(sparse_set_t *_set, uint32_t _index);

void enlarge_memory_page_array(uint32_t _pageNumber, memory_page_array_t *_pagesArray);

memory_page_t *new_mem_page(uint32_t _capacity, uint32_t _nullValue);

void enlarge_data_page_array(uint32_t _pageNumber, data_page_array_t *_pagesArray);
data_page_t *new_data_page(uint32_t _capacity, uint32_t _dataSize);


uint32_t get_page_relative_index(uint32_t _pageSize, uint32_t _index); 

#endif