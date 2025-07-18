//
//  minirt.h
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 16.07.2025.
//

#ifndef minirt_h
#define minirt_h

#include <stdbool.h>

typedef struct s_vec3
{
    float    x;
    float    y;
    float    z;
}    t_vec3;

typedef struct s_obj
{
    int         id;
    char        type;
    t_vec3      center;
    int         color;
    t_vec3      norm_vector;
    float       *attrs;
    float       bounding_r;
    bool        selected;
    bool        checkerboard;
    bool        mirror;
    bool        visible;
}    t_obj;

typedef struct s_cam
{
    t_vec3  viewpoint;
    t_vec3  orient_v;
    int     fov;

    float   yaw;
    float   pitch;

    t_vec3  right;
    t_vec3  up;
}   t_cam;

typedef struct s_amb_light
{
    float   ratio;
    int     color;
}   t_amb_light;

typedef struct s_light
{
    t_vec3  point;
    float   ratio;
    int     color;
}    t_light;

/*
 * need to figure out can be more than one light?
 * yep, can be, in bonus part (which we will do)
 */
typedef struct s_scene
{
    t_obj           *objs;
    int             objs_count;

    t_amb_light     *amb;
    t_cam           *cam;
    t_light         *lights;
    int             lights_count;
    t_obj           *selected;
}   t_scene;

typedef struct    s_optim
{
    float   *viewport_x;
    float   *viewport_y;
}   t_optim;

typedef struct s_rt
{
    float       win_aspect_ratio;
    t_optim     *optim;
    t_scene     *scene;
    char        mode;
    
    int         width;
    int         height;
    
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
    long      render_time;
}   t_rt;

/* prototypes */
t_rt    *init_rt(char *file_name, int width, int height, char *addr, int bpp, int line_len);

void    rerender(t_rt *info);

#endif /* minirt_h */
