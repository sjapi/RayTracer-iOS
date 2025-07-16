//
//  minirt.c
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 16.07.2025.
//

#include "minirt.h"
#include "parser.h"
#include "defines.h"
#include "renderer.h"
#include <stdlib.h>
#include <stdio.h>

static void print_point(t_vec3 p)
{
    printf("(%.2f, %.2f, %.2f)", p.x, p.y, p.z);
}

static void debug_print_scene(t_scene *scene)
{
    if (scene->amb)
        printf("amb: ratio=%.2f color=#%06X\n", scene->amb->ratio, scene->amb->color);
    if (scene->cam)
    {
        printf("cam: view_point=");
        print_point(scene->cam->viewpoint);
        printf(" orient_v=");
        print_point(scene->cam->orient_v);
        printf(" fov=%u\n", scene->cam->fov);
    }
    for (int i = 0; i < scene->lights_count; i++)
    {
        printf("light %d: point=", i + 1);
        print_point(scene->lights[i].point);
        printf(" ratio=%.2f color=#%06X\n", scene->lights[i].ratio, scene->lights[i].color);
    }
    for (int i = 0; i < scene->objs_count; i++)
    {
        t_obj *obj = &scene->objs[i];
        printf("obj %d: ", i + 1);
        switch (obj->type)
        {
            case SPHERE: printf("sphere"); break;
            case PLANE: printf("plane"); break;
            case CYLINDER: printf("cylinder"); break;
            case CONE: printf("cone"); break;
            default: printf("unknown"); break;
        }
        printf(" center=");
        print_point(obj->center);
        printf(" color=#%06X", obj->color);
        if (obj->type != 2)
        {
            printf(" norm=");
            print_point(obj->norm_vector);
        }
        if (obj->type == 2 || obj->type == 4)
            printf(" diameter=%.2f", obj->attrs[SPHERE_D_I]);
        if (obj->type == 4)
            printf(" height=%.2f", obj->attrs[CYLINDER_H_I]);
        printf("\n");
    }
}

bool    init_optimization(t_rt *info);
void    free_optimization(t_optim *optim);

void rerender(t_rt *info)
{
    if (info->optim)
    {
        free_optimization(info->optim);
        info->optim = NULL;
    }
    init_optimization(info);
    render_scene(info);
}

t_rt    *init_rt(char *file_name, int width, int height, char *addr, int bpp, int line_len)
{
    t_scene *scene;
    t_rt    *info;
    
    scene = load_scene(file_name);
    if (!scene)
        return (NULL);
    debug_print_scene(scene);
    info = malloc(sizeof(t_rt));
    if (!info)
        return (free(scene), NULL);
    info->width = width;
    info->height = height;
    info->addr = addr;
    info->bpp = bpp;
    info->line_len = line_len;
    info->scene = scene;
    info->win_aspect_ratio = (float)info->width / (float)info->height; // pizdec
    init_optimization(info);
    render_scene(info);
    return (info);
}
