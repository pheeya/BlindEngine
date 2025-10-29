#include <application/application.h>
#include <stdlib.h>
#include <be_assert.h>

application_t *application_create()
{
    
    application_t *app = malloc(sizeof(application_t));
    ASSERT_MALLOC(app);
    engine_t *engine = engine_create();
    app->engine = engine;
    return app;
}