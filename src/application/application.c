#include <application/application.h>
#include <stdlib.h>
#include <be_assert.h>

application_t *application_create(BeLogger* _appLogger)
{
    
    application_t *app = malloc(sizeof(application_t));
    ASSERT_MALLOC(app);
    BeEngine *engine = engine_create(_appLogger);
    app->engine = engine;
 return app;
}
