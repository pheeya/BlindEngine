## Reminder for what i was last doing
- reworking the code so that sub systems like renderer and window don't take engine as argument and instead take only what they need as argument such as logger and BeRenderer
- reworking engine so it takes raw pointer array. I'm doing this while considering making all the engine's sub systems independent modules, in which case the blindengine itself would just be the central coordinating system that puts all the subsystems together. This way people can use any part of the engine in their own engine without committing to blindengine's framework
## TODO 

- Check if all BeEngine fields are initialized in engine_create
- Set up test app and engine for debug build to use under gdb
- Remove unnecessary asserts on malloc and read about calloc 
- Complete engine api so that user only interacts through it in almost all cases
- Add "be_list_ensure_unique" function and use it to ensure no duplicate events are registered
- Check all compiler warnings, we might be using invalid pointer after calls to realloc in some places
- Renderer should render frame buffers, not cameras. This way we can just pass frame buffers to the renderer instead to decouple it from the camera.


## Architecture

### Systems
Systems are functions that need to be registered to a specific target (update, fixed_update, render, startup) before app initialization. They run throughout the lifetime of the application unless they are disabled or removed at runtime.

### Events
Events serve a different from system targets, even though they may seem similar at first. It is expected to register events before app initialization in order to make sure an event is registered before any listener is added, although this isn't necessary. 

Events are used by the engine internally but they're also meant to be used by the user application. After an event is registered, listeners can be added to and removed from it at any point. 

An example of where an event may be useful is when an explosion happens and all enemy entities need to be made aware of it to receive damage. In this case, you would add a listener for each enemy entity when it's created for the explosion event and then remove this listener once the enemy is dead.


