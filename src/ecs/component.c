#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ecs/entity.h>
#include <be_assert.h>

component_registry_t *component_registry_create_registry(uint32_t _initialCap)
{
    component_registry_t *_reg = malloc(sizeof(component_registry_t));
    ASSERT_MALLOC(_reg);

    _reg->pools = malloc(sizeof(component_pool_t) * _initialCap);
    ASSERT_MALLOC(_reg->pools);
    _reg->capacity = _initialCap;
    _reg->count = 0;
    return _reg;
}

component_id_t component_register(component_registry_t *_registry, void *_prototype, size_t _dataSize, size_t _initialcap, size_t _maxInstances)
{
    if (_registry->count == _registry->capacity)
    {
        uint32_t newCap = _registry->capacity;
        newCap *= 2;
        void *newMem = realloc(_registry->pools, sizeof(component_pool_t) * newCap);
        ASSERT_REALLOC(_registry->pools, newMem);
        _registry->pools = newMem;
    }

    component_pool_t newPool;
    newPool.set = sparse_set_create(_initialcap, _maxInstances, _dataSize, ENTITY_NULL);
    void *mem = malloc(_dataSize);
    ASSERT_MALLOC(mem);
    newPool.prototype = mem;
    memcpy(newPool.prototype, _prototype, _dataSize);

    _registry->pools[_registry->count] = newPool;

    component_id_t newId = _registry->count;
    _registry->count++;
    return newId;
}
/// @brief  gets pool component from a specific registry
/// @param _registry  the registry to get the pool from
/// @param _componentId  the components id
/// @return 
component_pool_t *component_registry_get_pool(component_registry_t *_registry, component_id_t _componentId)
{
    if (_componentId > _registry->count)
    {
        printf("component pool %d does not exist. Registry count is %d. Make sure the component is registered.", _componentId, _registry->count);
        exit(1);
    }
    return &_registry->pools[_componentId];
}

void *component_create_instance(component_registry_t *_registry, component_id_t _componentType, uint32_t _instanceIdentifier)
{
    component_pool_t *pool = component_registry_get_pool(_registry, _componentType);
    sparse_set_insert(pool->set, _instanceIdentifier, pool->prototype);

    return sparse_set_get(pool->set, _instanceIdentifier);
}

bool component_remove_instance(component_registry_t *_registry, component_id_t _componentType, uint32_t _instanceIdentifier)
{
    component_pool_t *pool = component_registry_get_pool(_registry, _componentType);
    bool did = sparse_set_remove(pool->set, _instanceIdentifier);
    return did;
}

bool component_exists(component_registry_t *_reg, component_id_t _componentId, uint32_t _instanceId)
{
    component_pool_t *pool = component_registry_get_pool(_reg, _componentId);
    return sparse_set_exists(pool->set, _instanceId);
}

void *component_get(component_registry_t *_registry, component_id_t _componentId, uint32_t _instance)
{
    component_pool_t *pool = component_registry_get_pool(_registry, _componentId);

    return sparse_set_get(pool->set, _instance);
}