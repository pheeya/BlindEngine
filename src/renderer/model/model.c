#define CGLTF_IMPLEMENTATION
#include <cgltf.h>
#include "model.h"

static size_t get_gltf_mesh_vert_count(cgltf_mesh *_m);
static size_t get_gltf_mesh_indices_count(cgltf_mesh *_m);
static mesh_t *mesh_from_node(cgltf_node _node);
static size_t get_gltf_primitive_vert_count(cgltf_primitive *_p);

model_t *model_load_gltf(const char *_path)
{
    cgltf_options opts = {0};

    cgltf_data *data = NULL;

    cgltf_result res = cgltf_parse_file(&opts, _path, &data);
    if (res == cgltf_result_success)
    {
        printf("Parsed model file, res: %d\n", res);
    }
    else
    {
        printf("Failed to parse model file, res: %d\n", res);
    }
    res = cgltf_load_buffers(&opts, data, _path);
    model_t *model;
    mesh_t *meshes;
    if (res == cgltf_result_success)
    {
        model = malloc(sizeof(model_t));
        meshes = malloc(sizeof(mesh_t) * data->meshes_count);
        model->meshes = meshes;
        model->mesh_count = data->meshes_count;

        int meshIndex = 0;
        printf("Model loaded, meshes: %d\n", data->meshes_count);
        for (int i = 0; i < data->nodes_count; i++)
        {
            if (data->nodes[i].mesh != NULL)
            {
                mesh_t *m = mesh_from_node(data->nodes[i]);
                meshes[meshIndex] = *m;
                free(m);
                meshIndex++;
            }
        }
        cgltf_free(data);
    }
    else
    {
        printf("Failed to load model: %d\n", res);
    }

    model->buffers = glBuffer_create_for_model(model->meshes, model->mesh_count);
    printf("Created model from gltf successfully \n");

    // for (int m = 0; m < model->mesh_count; m++)
    // {
    //     printf("\n");
    //     printf("Mesh: %d\n\n ", m+1);
    //     printf("Positions:\n");
    //     for (int i = 0; i < model->meshes[m].vertCount; i++)
    //     {
    //         printf("(%.5f, ", model->meshes[m].vertices[i].position[0]);
    //         printf("%.5f, ", model->meshes[m].vertices[i].position[1]);
    //         printf("%.5f)\n", model->meshes[m].vertices[i].position[2]);
    //     }

    //     printf("Normals:\n");
    //     for (int i = 0; i < model->meshes[m].vertCount; i++)
    //     {
    //         printf("(%.5f, ", model->meshes[m].vertices[i].normal[0]);
    //         printf("%.5f, ", model->meshes[m].vertices[i].normal[1]);
    //         printf("%.5f)\n", model->meshes[m].vertices[i].normal[2]);
    //     }
    // }

    return model;
}

model_t component_model_get_prototype()
{
    model_t mod;
    mod.buffers = NULL;
    mod.meshes = NULL;
    mod.mesh_count = 0;
    return mod;
}

static mesh_t *mesh_from_node(cgltf_node _node)
{
    size_t trisCount = get_gltf_mesh_indices_count(_node.mesh);
    size_t vertCount = get_gltf_mesh_vert_count(_node.mesh);

    mesh_t *m = malloc(sizeof(mesh_t));

    m->vertCount = vertCount;
    m->trisCount = trisCount;

    vertex_t *vertices = malloc(sizeof(vertex_t) * vertCount);
    m->vertices = vertices;

    triangle_t *triangles = malloc(sizeof(triangle_t) * trisCount);

    m->vertices = vertices;
    m->triangles = triangles;

    int vertStartingIndex = 0;
    int indicesStartingIndex = 0;

    for (int i = 0; i < _node.mesh->primitives_count; i += 3)
    {
        cgltf_accessor *indicesAccessor = _node.mesh->primitives[i].indices;

        for (int j = 0; j < trisCount; j += 3)
        {
            int index = j + indicesStartingIndex;
            triangle_t t[3];

            // cgltf_accessor_read_uint(indicesAccessor, index, t, 3);

            t[0] = cgltf_accessor_read_index(indicesAccessor, index);
            t[1] = cgltf_accessor_read_index(indicesAccessor, index + 1);
            t[2] = cgltf_accessor_read_index(indicesAccessor, index + 2);

            triangles[index] = t[0];
            triangles[index + 1] = t[1];
            triangles[index + 2] = t[2];
        }

        for (int j = 0; j < _node.mesh->primitives[i].attributes_count; j++)
        {
            cgltf_attribute *atrib = _node.mesh->primitives[i].attributes + j;
            void *data = atrib->data->buffer_view->buffer->data;

            if (atrib->type == cgltf_attribute_type_position)
            {
                for (int k = 0; k < atrib->data->count; k++)
                {
                    vertex_t v;
                    uint32_t vindex = k + vertStartingIndex;
                    if ((vertices + vindex))
                    {
                        v = vertices[vindex];
                    }

                    cgltf_accessor_read_float(atrib->data, k, v.position, 3);

                    vertices[vindex] = v;
                }
            }
            else if (atrib->type == cgltf_attribute_type_normal)
            {
                for (int k = 0; k < atrib->data->count; k++)
                {
                    vertex_t v;
                    uint32_t vindex = k + vertStartingIndex;
                    if ((vertices + vindex))
                    {
                        v = vertices[vindex];
                    }

                    cgltf_accessor_read_float(atrib->data, k, v.normal, 3);

                    vertices[vindex] = v;
                }
            }
            else if (atrib->type == cgltf_attribute_type_texcoord)
            {
                for (int k = 0; k < atrib->data->count; k++)
                {
                    vertex_t v;
                    uint32_t vindex = k + vertStartingIndex;
                    if ((vertices + vindex))
                    {
                        v = vertices[vindex];
                    }

                    cgltf_accessor_read_float(atrib->data, k, v.texcoord, 2);

                    vertices[vindex] = v;
                }
            }
        }
        vertStartingIndex += get_gltf_primitive_vert_count(&(_node.mesh->primitives[i]));
        indicesStartingIndex += _node.mesh->primitives[i].indices->count;
    }

    // printf("Positions (%d):\n", vertCount);
    // for (int i = 0; i < vertCount; i++)
    // {
    //     printf("(%.5f, ", vertices[i].position[0]);
    //     printf("%.5f, ", vertices[i].position[1]);
    //     printf("%.5f)\n", vertices[i].position[2]);
    // }

    // printf("Normals:\n");
    // for (int i = 0; i < vertCount; i++)
    // {
    //     printf("(%.5f, ", vertices[i].normal[0]);
    //     printf("%.5f, ", vertices[i].normal[1]);
    //     printf("%.5f)\n", vertices[i].normal[2]);
    // }

    // printf("Indices (%d):\n", m->trisCount);
    // for (int i = 2; i < m->trisCount; i += 3)
    // {
    //     printf("(%d, ", m->triangles[i - 2]);
    //     printf("%d, ", m->triangles[i - 1]);
    //     printf("%d)\n", m->triangles[i]);
    // }

    return m;
}

static size_t get_gltf_mesh_vert_count(cgltf_mesh *_m)
{
    size_t count = 0;
    for (int i = 0; i < _m->primitives_count; i++)
    {
        for (int j = 0; j < _m->primitives[i].attributes_count; j++)
        {
            cgltf_attribute *atrib = _m->primitives[i].attributes + j;
            if (atrib->type == cgltf_attribute_type_position)
            {
                for (int k = 0; k < _m->primitives[i].attributes[j].data->count; k++)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

static size_t get_gltf_mesh_indices_count(cgltf_mesh *_m)
{
    size_t count = 0;
    for (int i = 0; i < _m->primitives_count; i++)
    {
        count += _m->primitives[i].indices->count;
    }
    return count;
}

static size_t get_gltf_primitive_vert_count(cgltf_primitive *_p)
{
    size_t count = 0;

    for (int j = 0; j < _p->attributes_count; j++)
    {
        cgltf_attribute *atrib = _p->attributes + j;
        if (atrib->type == cgltf_attribute_type_position)
        {
            for (int k = 0; k < _p->attributes[j].data->count; k++)
            {
                count++;
            }
        }
    }
    return count;
}

void model_load_gltf_preallocated(const char *_path, model_t *_model)
{
    cgltf_options opts = {0};

    cgltf_data *data = NULL;

    cgltf_result res = cgltf_parse_file(&opts, _path, &data);
    if (res == cgltf_result_success)
    {
        printf("Parsed model file, res: %d\n", res);
    }
    else
    {
        printf("Failed to parse model file, res: %d\n", res);
    }
    res = cgltf_load_buffers(&opts, data, _path);
    mesh_t *meshes;
    if (res == cgltf_result_success)
    {
        meshes = malloc(sizeof(mesh_t) * data->meshes_count);
        _model->meshes = meshes;
        _model->mesh_count = data->meshes_count;

        int meshIndex = 0;
        printf("Model loaded, meshes: %d\n", _model->mesh_count);
        for (int i = 0; i < data->nodes_count; i++)
        {
            if (data->nodes[i].mesh != NULL)
            {
                mesh_t *m = mesh_from_node(data->nodes[i]);
                meshes[meshIndex] = *m;
                free(m);
                meshIndex++;
            }
        }
        cgltf_free(data);
    }
    else
    {
        printf("Failed to load mode;: %d\n", res);
    }

    _model->buffers = glBuffer_create_for_model(_model->meshes, _model->mesh_count);
    printf("Created preallocated model from gltf successfully \n");
}

model_t model_create_default_instance()
{
    model_t model;
    model.mesh_count = 0;
    model.buffers = NULL;
    model.meshes = NULL;

    return model;
}
