#include "shader.h"

static const char *shader_source_from_file(FILE *_file)
{
    char *source;
    fseek(_file, 0, SEEK_END);
    long size = ftell(_file);
    fseek(_file, 0, SEEK_SET);

    source = (char *)malloc(size + 1);

    if (source == NULL)
    {
        printf("Couldn't allocate memory for shader source while file read\n");
        return NULL;
    }

    fread(source, 1, size, _file);

    source[size] = '\0';
    return source;
}

shader_t *shader_load_from_file(const char *_pathWithoutExt)
{
    shader_t *shader = malloc(sizeof(shader_t));
    char path[150];
    strcpy(path, _pathWithoutExt);

    shader->filePath = _pathWithoutExt;
    FILE *file;

    // vert
    file = fopen(strcat(path, ".vert"), "rb");
    if (file == NULL)
    {
        printf("Couldn't open file provided: \n");
        printf("%s\n", path);
        return NULL;
    }
    const char *vsource = shader_source_from_file(file);
    uint32_t v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &vsource, NULL);
    glCompileShader(v);

    int suc;
    char log[512];
    glGetShaderiv(v, GL_COMPILE_STATUS, &suc);
    if (!suc)
    {
        glGetShaderInfoLog(v, 512, NULL, log);
        printf("Error while compiling vertex shader:\n");
        printf(log);
        printf("\n");
    }
    free((void *)vsource);
    fclose(file);

    // frag

    strcpy(path, _pathWithoutExt);
    file = fopen(strcat(path, ".frag"), "rb");
    if (file == NULL)
    {
        printf("Couldn't open file provided: \n");
        printf("%s\n", path);
        return NULL;
    }
    vsource = shader_source_from_file(file);
    uint32_t f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &vsource, NULL);
    glCompileShader(f);

    glGetShaderiv(f, GL_COMPILE_STATUS, &suc);
    if (!suc)
    {
        glGetShaderInfoLog(f, 512, NULL, log);
        printf("Error while compiling fragment shader:\n");
        printf(log);
        printf("\n");
    }
    free((void *)vsource);
    fclose(file);

    // link
    shader->id = glCreateProgram();
    glAttachShader(shader->id, v);
    glAttachShader(shader->id, f);
    glLinkProgram(shader->id);
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, &suc);
    if (!suc)
    {
        glGetShaderInfoLog(f, 512, NULL, log);
        printf("Error while compiling shader program:\n");
        printf(log);
        printf("\n");
    }

    glDeleteShader(v);
    glDeleteShader(f);

    return shader;
}

void shader_bind(shader_t *_shader)
{
    glUseProgram(_shader->id);
}
void shader_unbind()
{
    glUseProgram(0);
}