#include "system.h"
#include <stdlib.h>
#include <be_assert.h>


void system_register(systems_registry_t *_registry, system_function_pointer_t _systemFunc, systems_target_t _target)
{
    switch (_target)
    {
    case SYSTEMS_TARGET_STARTUP:
    {

        list_add(_registry->startup_list, _systemFunc);
        break;
    }
    case SYSTEMS_TARGET_FIRST:
    {

        list_add(_registry->first_list, _systemFunc);
        break;
    }
    case SYSTEMS_TARGET_PRE_UPDATE:
    {

        list_add(_registry->pre_update_list, _systemFunc);
        break;
    }
    case SYSTEMS_TARGET_UPDATE:
    {

        list_add(_registry->update_list, _systemFunc);
        break;
    }
    case SYSTEMS_TARGET_POST_UPDATE:
    {

        list_add(_registry->post_update_list, _systemFunc);
        break;
    }
    case SYSTEMS_TARGET_RENDERER_UPDATE:
    {

        list_add(_registry->renderer_update_list, _systemFunc);
        break;
    }
    case SYSTEMS_TARGET_FIXED_UPDATE:
    {

        list_add(_registry->fixed_update_list, _systemFunc);
        break;
    }
    }
}
