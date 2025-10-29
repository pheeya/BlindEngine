#ifndef BE_EVENT 
#define BE_EVENT 
#include <stdint.h>
#include <stdbool.h>

struct BeEvent;

typedef bool (*BeEventListener)(struct BeEvent _event, void* _ctx);

struct BeEvent{
uint16_t id;
char debug[10];
void* data;
};

#endif 
