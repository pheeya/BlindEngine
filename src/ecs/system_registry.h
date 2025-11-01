#ifndef SYSTEM_REGISTRY
#define SYSTEM_REGISTRY
#include <list/list.h>

// to prevent cyclic dependency with engine
// sytem_runner.h needs engine, engine needs system_registry
typedef struct
{
    BeList *startup_list;
    BeList *update_list;
    BeList *renderer_update_list;
    BeList *fixed_update_list;
} BeSystemsRegistry;

BeSystemsRegistry* system_registry_create();


#endif
