#include <ecs/entity.h>
#include <stdlib.h>
#include <stdio.h>
#include <be_assert.h>

entity_t entity_create(entity_registry_t *_registry)
{
    if (_registry->available > 0)
    {
        entity_id_t nextId = _registry->next;
        entity_version_t version = entity_get_version(_registry->entities[nextId]);

        entity_t newEntity = entity_compose(nextId, version);

        _registry->next = entity_get_id(_registry->entities[_registry->next]);
        _registry->available--;

        _registry->count++;

        return newEntity;
    }

    if (_registry->count == _registry->capacity)
    {
        uint32_t newCap = _registry->capacity * 2;
        if (newCap > MAX_ENTITIES)
        {
            newCap = MAX_ENTITIES;
            printf("Warning: entity registry is now at max capacity");
        }
        entity_t *newMem = realloc(_registry, newCap * sizeof(entity_t));
        if (newMem == NULL)
        {
            printf("Error while reallocating memory for entity registry, exitting");
            exit(1);
        }
        _registry->entities = newMem;
    }

    entity_t en = entity_compose(_registry->nextNew, 0);
    _registry->nextNew++;

    _registry->count++;
    return en;
}

entity_registry_t *entity_registry_create(uint32_t _initialSize)
{
    void *mem = malloc(sizeof(entity_registry_t));
    ASSERT_MALLOC(mem);

    entity_registry_t *reg = mem;
    reg->available = 0;
    reg->next = 0;
    reg->nextNew = 0;

    mem = malloc(sizeof(entity_t) * _initialSize);
    ASSERT_MALLOC(mem);
    reg->entities = mem;

    reg->capacity = _initialSize;
    reg->count = 0;

    // don't really need this i think, count should suffice
    // for (int i = 0; i < reg->capacity; i++)
    // {
    //     reg->entities[i] = ENTITY_NULL;
    // }

    return reg;
}

entity_id_t entity_get_id(entity_t _en)
{
    return (_en & ENTITY_ID_MASK) >> ENTITY_VERSION_NUM_BITS;
}

entity_version_t entity_get_version(entity_t _en)
{
    return _en & ENTITY_VERSION_MASK;
}

void entity_write_id(entity_t *_en, entity_id_t _newId)
{
    *_en = ((*_en & ENTITY_VERSION_MASK) | _newId << ENTITY_VERSION_NUM_BITS);
}

void entity_write_version(entity_t *_en, entity_version_t _newVersion)
{
    *_en = ((*_en & ENTITY_ID_MASK) | _newVersion);
}

entity_t entity_compose(entity_id_t _id, entity_version_t _version)
{
    entity_t ent;
    entity_write_id(&ent, _id);
    entity_write_version(&ent, _version);

    return ent;
}

void entity_increment_version(entity_t *_en)
{
    // & with ENTITY_VERSION_MASK to prevent overflow
    entity_write_version(_en, (entity_get_version(*_en) + 1) & ENTITY_VERSION_MASK);
}

void entity_destroy(entity_registry_t *_registry, entity_t _entity)
{
    entity_id_t id = entity_get_id(_entity);
    entity_id_t nextId = _registry->next;

    entity_write_id(&_registry->entities[id], nextId);
    _registry->next = id;

    entity_increment_version(&_registry->entities[id]);

    _registry->count--;
    _registry->available++;
}

