#include <types/system_registry.h>
#include <types/system_function_pointer.h>
#include <be_assert.h>
systems_registry_t *system_registry_create()
{
    systems_registry_t *reg = malloc(sizeof(systems_registry_t));
    ASSERT_MALLOC(reg);

    reg->startup_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);
    reg->first_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);
    reg->pre_update_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);
    reg->update_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);
    reg->post_update_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);
    reg->renderer_update_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);
    reg->fixed_update_list = list_create_dynamic(sizeof(system_function_pointer_t), 50, true);

    return reg;
}