#ifndef SYSTEM_REGISTRY
#define SYSTEM_REGISTRY
#include <list/list.h>


// to prevent cyclic dependency with engine
// sytem_runner.h needs engine, engine needs system_registry
typedef struct
{
    list_t *startup_list;
    list_t *first_list;
    list_t *pre_update_list;
    list_t *update_list;
    list_t *post_update_list;
    list_t *renderer_update_list;
    list_t *fixed_update_list;
} BeSystemsRegistry;

BeSystemsRegistry* system_registry_create();


#endif
