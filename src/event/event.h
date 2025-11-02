#ifndef BE_EVENT
#define BE_EVENT
#include <stdbool.h>
#include <stdint.h>
#include <list/list.h>
struct BeEvent;

typedef bool (*BeEventListener)(struct BeEvent *_event, void *_ctx);



struct BeEvent {
  uint16_t id;
  char *debug;
  void *data;
};

struct BeEventListenersList {

};

struct BeEventDispatcher {
  char* debug;
  BeList* lists;
};

void be_event_dispatch(struct BeEventDispatcher *_from, struct BeEvent *_event, void* _ctx);
void be_event_register(struct BeEventDispatcher *_in, uint16_t _eventId);
void be_event_add_listener(struct BeEventDispatcher* _to, uint16_t _eventId, BeEventListener _listener);
void be_event_remove_listener(struct BeEventDispatcher* _t, uint16_t _eventId, BeEventListener _listener);


#endif
