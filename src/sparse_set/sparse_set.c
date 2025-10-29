#include <types/sparse_set/sparse_set.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <be_assert.h>
sparse_set_t *sparse_set_create(uint32_t _initialCapacity, uint32_t _maxIndices, uint32_t _dataSize, uint32_t _nullValue)
{
    sparse_set_t *set = malloc(sizeof(sparse_set_t));
    ASSERT_MALLOC(set);

    set->dataCount = 0;
    set->dataSize = _dataSize;
    set->nullValue = _nullValue;

    set->indicesPages.count = 0;
    set->reversePages.count = 0;
    set->dataPages.count = 0;

    set->indicesPages.capacity = 0;
    set->reversePages.capacity = 0;
    set->dataPages.capacity = 0;

    set->indicesPages.pageSize = 1024;

    // these two pages should have the same size and everything about them should be identical
    // except the reverse's values should be indices to the indices sparse array
    // and the data should just have the data
    set->reversePages.pageSize = 1024;
    set->dataPages.pageSize = 1024;

    set->storageMode = SPARSE_SET_STORAGE_MODE_DENSE;

    enlarge_memory_page_array(10, &set->indicesPages);
    enlarge_memory_page_array(10, &set->reversePages);
    enlarge_data_page_array(10, &set->dataPages);

    return set;
}

void *sparse_set_get(sparse_set_t *_set, uint32_t _index)
{
    uint32_t pageNum = _index / _set->indicesPages.pageSize;
    uint32_t relativeIndex = get_page_relative_index(_set->indicesPages.pageSize, _index);
    memory_page_t *page = _set->indicesPages.pagePointers[pageNum];

    uint32_t dataPageAbsIndex = page->content[relativeIndex];

    uint32_t dataPageNum = dataPageAbsIndex / _set->dataPages.pageSize;
    uint32_t dataPageRelativeIndex = get_page_relative_index(_set->dataPages.pageSize, dataPageAbsIndex);
    data_page_t *dataPage = _set->dataPages.pagePointers[dataPageNum];

    return &dataPage->content[dataPageRelativeIndex];
}
bool sparse_set_exists(sparse_set_t *_set, uint32_t _index)
{
    uint32_t pageNum = _index / _set->indicesPages.pageSize;
    uint32_t relativeIndex = get_page_relative_index(_set->indicesPages.pageSize, _index);

    if (pageNum > _set->indicesPages.count)
    {
        printf("page index out of range\n");
        return false;
    }

    memory_page_t *page = _set->indicesPages.pagePointers[pageNum];

    if(page == NULL){
        return false;
    }

    if (relativeIndex > page->count)
    {
        return false;
    }
    uint32_t denseIndex = page->content[relativeIndex];
    return page->content[relativeIndex] != _set->nullValue;
}

// memory_page and memory_page_array stuff

memory_page_t *new_mem_page(uint32_t _capacity, uint32_t _nullValue)
{
    memory_page_t *newPage = malloc(sizeof(memory_page_t));
    newPage->content = malloc(sizeof(uint32_t) * _capacity);

    for (int i = 0; i < _capacity; i++)
    {
        newPage->content[i] = _nullValue;
    }

    // initialize all content entries to null value

    newPage->count = 0;

    return newPage;
}

void enlarge_memory_page_array(uint32_t _numPages, memory_page_array_t *_pagesArray)
{

    uint32_t newCap = _numPages;
    // if newcap greater than some limit, then newcap = some limit

    if (_pagesArray->capacity == 0)
    {
        _pagesArray->pagePointers = malloc(sizeof(memory_page_t *) * newCap);
    }
    else
    {
        _pagesArray->pagePointers = realloc(_pagesArray->pagePointers, sizeof(memory_page_t *) * newCap);
    }

    for (uint32_t i = _pagesArray->capacity; i < newCap; i++)
    {
        _pagesArray->pagePointers[i] = NULL;
    }

    _pagesArray->capacity = newCap;
}

void insert_to_memory_page(uint32_t _index, uint32_t _insert, memory_page_array_t *_owner, uint32_t _contentNullValue)
{
    uint32_t pageNumber = (_index / _owner->pageSize);
    uint32_t relativeIndex = get_page_relative_index(_owner->pageSize, _index);

    if (pageNumber > _owner->capacity)
    {
        enlarge_memory_page_array(pageNumber, _owner);
    }

    memory_page_t *page = _owner->pagePointers[pageNumber];
    if (page == NULL)
    {
        page = new_mem_page(_owner->pageSize, _contentNullValue);
        _owner->pagePointers[pageNumber] = page;
        _owner->count++;
    }
    page->content[relativeIndex] = _insert;

    page->count++;
}

// data_page and data_page_array stuff
data_page_t *new_data_page(uint32_t _capacity, uint32_t _dataSize)
{
    data_page_t *newPage = malloc(sizeof(data_page_t));
    newPage->content = malloc(sizeof(_dataSize) * _capacity);

    newPage->count = 0;

    return newPage;
}

void enlarge_data_page_array(uint32_t _pageNumber, data_page_array_t *_pagesArray)
{

    uint32_t newCap = _pageNumber;
    // if newcap greater than some limit, then newcap = some limit

    if (_pagesArray->capacity == 0)
    {
        _pagesArray->pagePointers = malloc(sizeof(data_page_t *) * newCap);
    }
    else
    {
        _pagesArray->pagePointers = realloc(_pagesArray->pagePointers, sizeof(data_page_t *) * newCap);
    }

    for (uint32_t i = _pagesArray->capacity; i < newCap; i++)
    {
        _pagesArray->pagePointers[i] = NULL;
    }

    _pagesArray->capacity = newCap;
}

void insert_to_data_page(uint32_t _index, void *_data, data_page_array_t *_owner, uint32_t _dataSize)
{
    uint32_t pageNumber = (_index / _owner->pageSize);
    uint32_t relativeIndex = get_page_relative_index(_owner->pageSize, _index);

    if (pageNumber > _owner->capacity)
    {
        enlarge_data_page_array(pageNumber, _owner);
    }

    data_page_t *page = _owner->pagePointers[pageNumber];
    if (page == NULL)
    {
        page = new_data_page(_owner->pageSize, _dataSize);
        _owner->pagePointers[pageNumber] = page;
        _owner->count++;
    }

    uint8_t *dataTail = (uint8_t *)page->content + page->count * _dataSize;
    memcpy(dataTail, _data, _dataSize);

    page->count++;
}

// sparse_set_operations

void sparse_set_insert(sparse_set_t *_set, uint32_t _index, void *_data)
{

    insert_to_memory_page(_index, _set->dataCount, &_set->indicesPages, _set->nullValue);
    insert_to_memory_page(_set->dataCount, _index, &_set->reversePages, _set->nullValue);
    insert_to_data_page(_set->dataCount, _data, &_set->dataPages, _set->dataSize);
    _set->dataCount++;
}

bool sparse_set_remove(sparse_set_t *_set, uint32_t _index)
{

    if (!sparse_set_exists(_set, _index))
    {
        return false;
    }

    uint32_t pageNum = _index / _set->indicesPages.pageSize;
    uint32_t relativeIndex = get_page_relative_index(_set->indicesPages.pageSize, _index);
    memory_page_t *indicesPage = _set->indicesPages.pagePointers[pageNum];

    if (_set->storageMode == SPARSE_SET_STORAGE_MODE_DENSE)
    {
        uint32_t dataPageNum = _index / _set->dataPages.pageSize;
        data_page_t *dataPage = _set->dataPages.pagePointers[dataPageNum];

        uint32_t dataPageRemoveIndex = get_page_relative_index(_set->dataPages.pageSize, _index);

        uint32_t dataPageLastIndex = _set->dataPages.pagePointers[pageNum]->count - 1;

        uint32_t reversePageNum = _index / _set->reversePages.pageSize;
        memory_page_t *reversePage = _set->reversePages.pagePointers[reversePageNum];

        // this can happen if we only have 1 entry and we remove it or if we are removing the last entity
        if (dataPageRemoveIndex != dataPageLastIndex)
        {
            uint8_t *contentPointer = dataPage->content;

            uint8_t *dataPageTail = contentPointer + dataPageLastIndex * _set->dataSize;
            uint8_t *dataPageRemoveIndexPointer = contentPointer + dataPageRemoveIndex * _set->dataSize;

            printf("Remove Index: %d\n", dataPageRemoveIndex);
            printf("Last Index: %d\n", dataPageLastIndex);
            memcpy(dataPageRemoveIndexPointer, dataPageTail, _set->dataSize);

            reversePage->content[dataPageRemoveIndex] = reversePage->content[dataPageLastIndex];
        }
        indicesPage->content[relativeIndex] = _set->nullValue;

        indicesPage->count--;
        reversePage->count--;
        dataPage->count--;

        _set->dataCount--;
    }
    else
    {
        // do sumtin
    }

    // if (_set->indices[_index] > _set->count - 1)
    // {
    //     printf("sparse set index out of capacity bounds");
    //     return;
    // }

    // uint32_t removeIndex = _set->indices[_index];
    // uint32_t lastIndex = _set->count - 1;

    // if (removeIndex != lastIndex)
    // {

    //     uint8_t *pointer = _set->data;
    //     pointer += (removeIndex * _set->dataSize);
    //     uint8_t *lastEntry = _set->data + _set->dataSize * lastIndex;
    //     memcpy(pointer, lastEntry, _set->dataSize);

    //     // 2 3 5
    //     // - - 0 1 - 2

    //     // remove(1)

    //     // 2 5
    //     // - - 0 - - 1

    //     _set->indices[_set->reverse[lastIndex]] = removeIndex;
    //     _set->reverse[removeIndex] = _set->reverse[lastIndex];
    // }
    // _set->indices[_index] = _set->nullValue;

    // _set->count--;

    return true;
}

void sparse_set_release(sparse_set_t *_set)
{
    // free(_set->reverse);
    // free(_set->indices);
    // free(_set->data);
    // free(_set);
}

uint32_t get_page_relative_index(uint32_t _pageSize, uint32_t _index)
{
    uint32_t pageNum = _index / _pageSize;
    if (pageNum == 0)
        return _index;
    return _index % pageNum;
}