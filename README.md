## TODO 

1. Remove unnecessary asserts on malloc and read about calloc 
2. Simplify folder/file structure
3. Complete engine api so that user only interacts through it in almost all cases
4. Add "be_list_ensure_unique" function and use it to ensure no duplicate events are registered


## Architecture

### Systems
Systems are functions that need to be registered to a specific target (update, fixed_update, render, startup) before app initialization. They run throughout the lifetime of the application unless they are disabled or removed at runtime.

### Events
Events serve a different from system targets, even though they may seem similar at first. It is expected to register events before app initialization in order to make sure an event is registered before any listener is added, although this isn't necessary. 

Events are used by the engine internally but they're also meant to be used by the user application. After an event is registered, listeners can be added to and removed from it at any point. 

An example of where an event may be useful is when an explosion happens and all enemy entities need to be made aware of it to receive damage. In this case, you would add a listener for each enemy entity when it's created for the explosion event and then remove this listener once the enemy is dead.


