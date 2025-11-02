#ifndef TEST_SYSTEM
#define TEST_SYSTEM

#include "testsystem.h"
#include <stdio.h>
#include <renderer/model/surface/shader.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stbi/stbi_truetype.h>

static unsigned char *m_roboto_font_buffer;

void ts_startup(engine_t *engine)
{
    stbtt_fontinfo m_robotFont;
    FILE *file = fopen("../assets/fonts/roboto/Roboto-Regular.ttf", "rb");
    if (file == NULL)
    {
        printf("File is null\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    m_roboto_font_buffer = malloc(fileSize);
    fread(m_roboto_font_buffer, 1, fileSize, file);
    int fontLoadStatus = stbtt_InitFont(&m_robotFont, m_roboto_font_buffer, stbtt_GetFontOffsetForIndex(m_roboto_font_buffer, 0));

    printf("Font loaded: %d\n", fontLoadStatus);
}

void ts_first(engine_t *engine)
{
    entity_t Player = engine_create_entity(engine);

    printf("\n");
    printf("created Player entity with id %d\n", entity_get_id(Player));

    printf("total entities: %d\n", engine_get_entity_count(engine));

    model_t *model = engine_add_component(engine, COMPONENT_MODEL, Player);
    component_pool_t *reg = component_registry_get_pool(engine->componentRegistry, COMPONENT_MODEL);

    model_load_gltf_preallocated("../assets/models/susan.glb", model);

    transform_t *PlayerTransform = engine_add_component(engine, COMPONENT_TRANSFORM, Player);
    bool playerHasComponent = engine_has_component(engine, COMPONENT_TRANSFORM, Player);
    printf("Player has transform: %d\n", playerHasComponent);

    playerHasComponent = engine_has_component(engine, COMPONENT_MODEL, Player);

    printf("player has model: %d\n", playerHasComponent);
}

void ts_update(engine_t *engine)
{
}

void ts_post_update(engine_t *engine)
{
}

#endif
