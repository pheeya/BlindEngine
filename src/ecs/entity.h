#ifndef ECS
#define ECS
#define ECS_32

#include <stdint.h>

#ifdef ECS_32

typedef uint32_t entity_t;
typedef uint32_t entity_id_t;
typedef uint16_t entity_version_t;

static const uint32_t ENTITY_ID_MASK = 0xFFFFF000;
static const uint32_t ENTITY_VERSION_MASK = 0x00000FFF;
static const uint32_t MAX_ENTITIES = 0x000FFFFF - 1;
static const uint32_t ENTITY_ID_NUM_BITS = 20;
static const uint32_t ENTITY_VERSION_NUM_BITS = 12;
static const uint32_t ENTITY_NULL = (1 << ENTITY_ID_NUM_BITS)-1;
#elif ECS_64
typedef uint64_t entity_t;

#endif

typedef struct
{
    uint32_t available;
    entity_id_t next;
    entity_t *entities;
    entity_id_t nextNew;
    uint32_t capacity;
    uint32_t count;
} entity_registry_t;

entity_t entity_create(entity_registry_t *_registry);

entity_registry_t *entity_registry_create(uint32_t _initialSize);

entity_id_t entity_get_id(entity_t _en);
entity_version_t entity_get_version(entity_t _en);

void entity_write_id(entity_t *_en, entity_id_t _newId);

void entity_write_version(entity_t *_en, entity_version_t _newVersion);

void entity_increment_version(entity_t *_en);

void entity_destroy(entity_registry_t *_registry, entity_t _entity);


entity_t entity_compose(entity_id_t _id, entity_version_t _version);

#endif
