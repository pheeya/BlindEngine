#include <event/event.h>
#include <stdlib.h>
void be_event_dispatch(struct BeEventDispatcher *_from, struct BeEvent *_event,
                       void *_ctx) {
  BeList *list = (BeList *)be_list_get_at(_from->lists, _event->id);

  for (int i = 0; i < list->count; i++) {
    BeEventListener listener = (BeEventListener)be_list_get_at(list, i);
    bool consumed = listener(_event, _ctx);
    if (consumed) {
      break;
    }
  }
}
void be_event_register(struct BeEventDispatcher *_in, uint16_t _eventId) {
  if (_eventId != _in->lists->count) {

    printf("Tried to register event with bad id, event ids need to be "
           "consecutive with no gaps\n");
    exit(EXIT_FAILURE);
    return;
  };
 BeList *newList = be_list_create(8, sizeof(BeEventListener));
  be_list_append(_in->lists, newList);
}

void be_event_add_listener(struct BeEventDispatcher *_dispatcher, uint16_t _eventId, BeEventListener _listener){
BeList* listeners = (BeList*)be_list_get_at(_dispatcher->lists, _eventId);
be_list_append(listeners,_listener);
}

void be_event_remove_listener(struct BeEventDispatcher *_dispatcher, uint16_t _eventId, BeEventListener _listener){

}
