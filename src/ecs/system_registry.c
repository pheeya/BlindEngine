#include <be_assert.h>
#include <ecs/system_function_pointer.h>
#include <ecs/system_registry.h>
BeSystemsRegistry *system_registry_create() {
  BeSystemsRegistry *reg = malloc(sizeof(BeSystemsRegistry));
  ASSERT_MALLOC(reg);


  reg->startup_list = be_list_create(8, sizeof(BeSystemFunction));
  reg->update_list = be_list_create(8, sizeof(BeSystemTimedFunction));
  reg->renderer_update_list = be_list_create(8, sizeof(BeSystemTimedFunction));
  reg->fixed_update_list = be_list_create(8, sizeof(BeSystemTimedFunction));

  return reg;
}
