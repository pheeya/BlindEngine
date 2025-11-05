#ifndef ECS_COMPONENTS
#define ECS_COMPONENTS

#include <sparse_set/sparse_set.h>





typedef uint32_t ComponentId;


// components



typedef struct
{
    void* prototype;
    sparse_set_t *set;
} component_pool_t;

typedef struct
{
    component_pool_t *pools;
    uint32_t capacity;
    uint32_t count;
} component_registry_t;



component_registry_t* component_registry_create_registry(uint32_t _initialCap);

ComponentId component_register(component_registry_t *_registry,void* _prototype, size_t _dataSize, size_t _initialcap, size_t _maxInstances);

component_pool_t *component_registry_get_pool(component_registry_t* _registry,ComponentId _componentId);

void *component_get(component_registry_t *_registry, ComponentId _componentId, uint32_t _instance);

void* component_create_instance(component_registry_t *_registry, ComponentId _componentType, uint32_t _instanceIdentifier);

bool component_remove_instance(component_registry_t *_registry, ComponentId _componentType, uint32_t _instanceIdentifier);

bool component_exists(component_registry_t *_reg, ComponentId _componentId, uint32_t _instanceId);

#endif
