/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:26:09 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 21:21:46 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <rtdefs.h>

# define EPS 0.01
# define VPWIDTH 10
# define VPHEIGHT 7.2
# define VPDIST 20
# define SPEC 50
# define KD 0.6
# define KS 0.2
# define KA 0.2
# define RA 255
# define GA 255
# define BA 255
# define MAX_DEPTH 25

/*
** FOV = atan(VPWIDTH / 2 / VPDIST)
** With VPWIDTH = 6.4 and VPDIST = 12 FOV = 30
*/

# define CAMPOSX env->cam.campos.x
# define CAMPOSY env->cam.campos.y
# define CAMPOSZ env->cam.campos.z
# define CAMPOS env->cam.campos
# define XINDENT env->cam.xindent
# define YINDENT env->cam.yindent
# define VPUL env->cam.vpul
# define OBJCOLOR env->obj->color
# define XS env->obj->vec1.x
# define YS env->obj->vec1.y
# define ZS env->obj->vec1.z
# define POS env->obj->vec1
# define NX env->obj->vec2.x
# define NY env->obj->vec2.y
# define NZ env->obj->vec2.z
# define N env->obj->vec2
# define RS env->obj->r
# define D1 env->obj->d1
# define D2 env->obj->d2

/*
** COMPOSED OBJECTS DEFINE
*/

# define COMPOSEPOS env->obj->compose->vec1
# define COMPOSEN env->obj->compose->vec2

/*
** ray define
*/

# define RCOLOR ray->color
# define VDIR ray->vecdir
# define RDIST ray->dist
# define REFLECT ray->reflect

/*
**  define vec dir camera
*/

# define VDZX cam.vecdirz.x
# define VDZY cam.vecdirz.y
# define VDZZ cam.vecdirz.z
# define VDYX cam.vecdiry.x
# define VDYY cam.vecdiry.y
# define VDYZ cam.vecdiry.z
# define VDXX cam.vecdirx.x
# define VDXY cam.vecdirx.y
# define VDXZ cam.vecdirx.z

# define LINE env->file->line
# define LINENEXT env->file->next->line

/*
** DEFINE GUI
*/

# define CONTAINER gui->container[id]
# define BLOCK gui->container
# define PATH gui->path
# define BG gui->bg
# define TTF gui->ttf
# define BUTTON BLOCK[id]->button
# define TEXTBOX BLOCK[id]->textbox
# define SCROLL BLOCK[id]->scroll
# define SCROLL_B SCROLL[i]->button
# define CHECKBOX BLOCK[id]->checkbox
# define ALT_SCREEN_CENTERED 2325
# define SCANCODE event.key.keysym.scancode
# define HELP gui->help
# define PARAM gui->param
# define PARAM_SCL PARAM->scroll[i]
# define PARAM_SCL_B PARAM_SCL->button
# define PARAM_CBX PARAM->checkbox[i]
# define WIDGET gui->widget_active
# define REF t_widget_ref
# define DEF gui->def_widget

# define GUI_WIDTH gui->dest.w
# define GUI_HEIGHT gui->dest.h
# define GUI_THEME 0
# define GUI_AA 0
# define GUI_DYNAMIC 1
# define GUI_CONSTANT 0
# define GUI_FONT_BORDER_STEP 15
# define GUI_FONT_SIZE TTF->def_size
# define GUI_ALIGN_LEFT 0
# define GUI_ALIGN_MID 1
# define GUI_ALIGN_RIGHT 2
# define GUI_TEXTBOX_W GUI_WIDTH / 8
# define GUI_TEXTBOX_H 20
# define GUI_SCROLL_H 20
# define GUI_SCROLL_MAX_SHOWN 5
# define GUI_LIST_STEP 20
# define GUI_BUTTON_H 25
# define GUI_BUTTON_DEPTH 1
# define GUI_CHECKBOX_SIZE 20
# define GUI_XYZ_MAX 99999
# define GUI_XYZ_MIN -99999
# define GUI_VH_MAX 180
# define GUI_VH_MIN -180
# define GUI_RGBA_MAX 255
# define GUI_RGBA_MIN 0
# define GUI_INDEX_MAX 35
# define GUI_INDEX_MIN 0
# define GUI_HELP_W 360
# define GUI_HELP_H 530
# define GUI_CONTAINER_TOTAL_NB 10
# define GUI_CONTAINER_DYNAMIC_NB 1
# define GUI_CONTAINER_RESERVED 640
# define GUI_CONTAINER_RESIZED ((gui->height - \
			GUI_CONTAINER_RESERVED) / GUI_CONTAINER_DYNAMIC_NB)

# include <math.h>
# include <fcntl.h>
# ifdef __APPLE__
#  include <SDL.h>
#  include <SDL_ttf.h>
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif
# include <libft.h>
# include <lib_vec.h>

/*
** Unused now, but needed for compilation
*/

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_cam
{
	t_vector		pos;
	t_vector		ang;
}					t_cam;

typedef struct		s_light
{
	int				type;
	t_vector		pos;
	t_vector		ang;
	unsigned int	color;
	float			mod;
	float			k1;
	float			k2;
	float			k3;
	struct s_light	*next;
}					t_light;

/*
**end of unused structs
*/

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			a;
}					t_color;

typedef struct		s_line
{
	char			*line;
	int				size;
	struct s_line	*next;
}					t_line;

typedef struct		s_obj
{
	int				type;
	void			(*func)();
	void			(*normale)();
	int				**base;
	int				negative;
	t_vector		pos;
	t_vector		ang;
	t_vector		exp;
	unsigned int	color;
	unsigned int	color2;
	unsigned int	color3;
	unsigned int	color_refract;
	unsigned int	size;
	float			mod;
	float			reflect_k;
	float			refract_k;
	float			refract_ind;
	float			dst;
	struct s_obj	*next;
	t_vec			vec1;
	t_vec			vec2;
	int				cap1;
	int				cap2;
	int				reflect;
	double			r;
	double			d1;
	double			d2;
	t_color			color_t;
	char			*textures;
	struct s_obj	*compose;
	struct s_obj	*first;
}					t_obj;

typedef struct		s_parse
{
	t_vec			pos;
	t_vec			n;
	t_color			color;
	double			r;
}					t_parse;

typedef struct		s_ray
{
	t_vec			vecdir;
	t_vec			pos;
	t_vec			reflect;
	double			dist;
	t_color			color;
}					t_ray;

typedef struct		s_camera
{
	t_vec			campos;
	t_vec			vecdirx;
	t_vec			vecdiry;
	t_vec			vecdirz;
	t_vec			vpul;
	double			xindent;
	double			yindent;
}					t_camera;

typedef struct		s_spot
{
	t_vec			spotpos;
	t_color			color;
	t_ray			ray;
	char			*nature;
	struct s_spot	*first;
	struct s_spot	*next;
}					t_spot;

typedef struct		s_settings
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	aa;
	unsigned int	deph;
	unsigned int	reflect;
	unsigned int	refract;
	unsigned int	fov;
	unsigned int	d3_mode;
	float			d3_offset;
	float			d3_conv;
	char			*name;
	unsigned int	focus;
	int				focus_dst;
	int				focus_range;
	float			focus_k;
	t_cam			*cam;
	t_cam			*cam2;
	int				preview;
	int				display;
	int				threads;
	int				verbose;
}					t_settings;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*img;
	SDL_Event		event;
	t_settings		*set;
	int				i;
	unsigned int	x;
	unsigned int	y;
	t_parse			data;
	t_line			*file;
	t_obj			*obj;
	t_obj			*neg_obj;/////compilation only
	t_light			*light;//unused now
	t_camera		cam;
	t_spot			*spot;
}					t_env;

typedef enum
{
					false,
					true
}					bool;

typedef enum
{
					BTN,
					TXB,
					SCL,
					PRM,
					HLP,
					CBX,
					CNT
}					widget_type;

typedef struct		s_txt
{
	char			*content;
	char			*anchor;
	int				align;
}					t_txt;

typedef struct		s_ttf
{
	TTF_Font		*font;
	SDL_Texture		*texture;
	SDL_Rect		rect;
	int				h_px;
	int				w_px;
	int				def_size;
	char			*def_ttf;
	int				def_border_step;
}					t_ttf;

typedef struct		s_checkbox
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_txt			*txt;
	int				id;
	int				p;
	char			*tag;
	bool			selected;
}					t_checkbox;

typedef struct		s_button
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_txt			*txt;
	int				id;
	int				p;
	char			*action;
}					t_button;

typedef struct		s_scroll
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_txt			*txt;
	int				id;
	int				p;
	char			*tag;
	t_button		*button;
	char			**value;
	int				nb_value;
	int				active_value;
	int				mod;

}					t_scroll;

typedef struct		s_textbox
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_txt			*txt;
	int				id;
	int				p;
	char			*tag;
	char			*value;
	int				vlen;
	int				maxlen;
	int				min;
	int				max;
	int				edited;
}					t_textbox;

typedef struct		s_container
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_txt			*txt;
	int				up_lim;
	int				bot_lim;
	int				button_qt;
	int				scroll_qt;
	int				textbox_qt;
	int				checkbox_qt;
	t_button		**button;
	t_scroll		**scroll;
	t_textbox		**textbox;
	t_checkbox		**checkbox;
}					t_container;

typedef struct		s_help
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	int				active;
}					t_help;

typedef struct		s_param
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_button		**button;
	t_scroll		**scroll;
	t_textbox		**textbox;
	t_checkbox		**checkbox;
	int				button_qt;
	int				scroll_qt;
	int				textbox_qt;
	int				checkbox_qt;
	int				active;
}					t_param;

typedef struct		s_bg
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
}					t_bg;

typedef struct		s_path
{
	char			*texture;
	char			*font;
}					t_path;

typedef struct		s_widget_ref
{
	widget_type		nature;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_txt			*txt;
	int				id;
	int				p;
}					t_widget_ref;

typedef struct		s_def_widget
{
	int				txb_w;
	int				txb_h;
	char			*txb_texture;
	char			*txb_texture_selected;
	int				scl_w;
	int				scl_h;
	int				scl_max_shown;
	char			*scl_texture_head;
	char			*scl_texture_list;
	char			*sclb_texture;
	char			*sclb_texture_selected;
	int				btn_w;
	int				btn_h;
	char			*btn_texture;
	char			*btn_texture_selected;
	int				cbx_size;
	char			*cbx_texture;
	char			*cbx_texture_selected;
}					t_def_widget;

typedef struct		s_gui
{
	SDL_Window		*win;
	SDL_Renderer	*img;
	unsigned int	winID;
	SDL_Event		gui_event;
	SDL_DisplayMode	*display;
	SDL_Rect		dest;
	SDL_Color		color;
	t_color			p_color;
	t_path			*path;
	t_bg			*bg;
	t_container		**container;
	t_ttf			*ttf;
	t_help			*help;
	t_param			*param;
	t_def_widget	*def_widget;
	void			*widget_active;
	int				anchor_x;
	int				anchor_y;
	int				tmp_lim;
}					t_gui;

/*
** NOT SORTED - DAWNAUR
*/

t_env				*get_env(void);
//void				*get_normale(unsigned int i);
//void				*get_func(unsigned int i);
int					**new_base(void);
unsigned int		get_color(char *str);
void				aff_settings(t_settings *set);

/*
** COLOR_UTILS
*/
void				color_mix_k(unsigned int *src, unsigned int color,
								unsigned int k);
void				color_mix_float(t_color *src, t_color *color,
									float k);
unsigned int		limit_nb(unsigned int nb, unsigned int max);

void				raycaster(t_env *env);
t_color				trace(t_env *env, t_ray *ray, int i);
int					lightcaster(t_env *env, t_vec pos, t_ray ray, t_obj *obj);
void				reflect(t_env *env, int i);
void				pixel_put(t_env *env, t_color color);
t_ray				init_ray(t_env *env);
t_color				calc_color(t_ray *ray, t_color cobj, t_color clight,
								double angle);
t_color				calc_shadow(t_ray *ray, t_color cobj);
t_color				extract_color(int color);
int					event(SDL_Event event, t_env *env);
void				error(int n);
t_line				*ft_new_line(char *line, int size);
t_line				*save_file(int fd);
double				ft_atod(char *str);
t_color				default_color(void);
t_color				default_color_spot(void);
t_vec				default_pos(void);
t_vec				default_n(void);
void				free_file(t_env *env);
int					gotonextvalue(t_env *env, int i);
t_color				init_color_black(void);

t_vec				calc_ncone(t_ray *ray, t_obj *obj);
t_vec				calc_ncylinder(t_ray *ray, t_obj *obj);

t_env				*init_env(int fd);
void				init_graphics(t_env *env);

/*
** PARSER FUNCTIONS
*/

t_vec				get_vector(t_env *env);
t_color				get_color_t(t_env *env);
t_color				get_color_spot(t_env *env);
t_color				color_correc_spot(t_color color);
t_color				color_correc_obj(t_color color);
void				old_parse_camera(t_env *env);
void				old_parse_sphere(t_env *env);
void				old_parse_spot(t_env *env);
void				old_parse_plane(t_env *env);
void				old_parse_cylinder(t_env *env);
void				old_parse_cone(t_env *env);
void				old_parse_file(t_env *env);

/*
** CAMERA FUNCTIONS
*/

t_camera			init_cam(t_env *env, double x, double y, double z);
void				transcam(t_env *env, t_vec trans);
void				rotcam(t_env *env, double rx, double ry, double rz);
void				camangle(t_env *env, double rx, double ry, double rz);

/*
** GUI FUNCTIONS
*/

t_gui				*get_gui(void);
t_gui				*gui_init(void);
void				gui_parse_builder(t_gui *gui, char *file);
void				gui_parse_param_builder(t_gui *gui, int fd, int nb);
void				gui_parse_main_builder(t_gui *gui, int fd, int nb);
void				gui_find_header(t_gui *gui, int fd, char *line);
void				gui_pixel_put(t_gui *gui, int x, int y);
SDL_Color			gui_color(char *choice);
void				gui_background_get_set_n_display(t_gui *gui);
void				gui_container_build(t_gui *gui, int mode, int px);
void				gui_error(int n);
void				gui_font_init(t_gui *gui, char *ttf, int size);
void				gui_font_build(t_gui *gui);
void				gui_button_build(t_gui *gui);
void				gui_button_set(t_button *button);
void				gui_button_selected(t_gui *gui, t_button *button);
void				gui_button_free(t_button *button);
void				gui_textbox_build(t_gui *gui);
void				gui_scroll_build(t_gui *gui);
void				gui_textbox_get_len(t_textbox *textbox);
void				gui_textbox_set(t_textbox *textbox);
void				gui_textbox_get_bmp(t_gui *gui, t_textbox *textbox);
void				gui_textbox_display(t_gui *gui, t_textbox *textbox);
void				gui_write_textbox_value(t_gui *gui, t_textbox *textbox, char *color);
void				gui_write_button(char *text, t_button *button, char *color);
void				event_textbox_edit(t_gui *gui, t_textbox *textbox, char *color);
void				gui_textbox_value_clear(t_textbox *textbox, int len);
void				event_widget_deselect(t_gui *gui);
void				gui_main_refresh(t_gui *gui);
void				gui_textbox_create_all(t_gui *gui);
void				gui_button_create_all(t_gui *gui);
void				gui_scroll_create_all(t_gui *gui);
int					gui_scroll_value_select(t_gui *gui, SDL_Event event, t_scroll *scroll);
void				gui_scroll_toggle(t_gui *gui, t_scroll *scroll);
void				gui_scroll_set(t_scroll *scroll);
void				gui_scroll_set_halign(t_scroll *scroll);
void				gui_scroll_free(t_scroll *scroll);
void				gui_scroll_write_list(t_gui *gui, t_scroll *scroll, int motion);
void				gui_scroll_value_write(t_gui *gui, t_scroll *scroll, char *color);
void				gui_help_toggle(t_gui *gui);
void				gui_help_open(t_gui *gui);
void				gui_help_close(t_gui *gui);
void				gui_write_help(t_gui *gui, char *text, int align, int y);
void				gui_write_param(t_gui *gui, char *text, int align, int y);
void				gui_param_toggle(t_gui *gui);
void				gui_param_open(t_gui *gui);
void				gui_param_close(t_gui *gui);
void				gui_param_refresh(t_gui *gui);
t_scroll			*gui_param_scroll_init();
void				gui_param_scroll_set(t_scroll *scroll);
t_checkbox			*gui_param_checkbox_init(void);
void				gui_param_checkbox_set(t_checkbox *checkbox);
void				gui_param_checkbox_get_bmp(t_gui *gui, t_checkbox *checkbox, char *file);
void				gui_param_checkbox_display(t_gui *gui, t_checkbox *checkbox);
void				gui_param_checkbox_create_all(t_gui *gui);
void				gui_param_checkbox_toggle(t_gui *gui, t_checkbox *checkbox);
void				gui_widget_draw_depth(SDL_Rect widget, int px, char *color);
void				gui_widget_draw_outline(SDL_Rect widget, int px, char *color);
void				gui_widget_draw_in_line(SDL_Rect widget, int in, char *color);
void				gui_widget_texture_get_bmp(void *widget, char *file);
void				gui_widget_display(void *widget);
void				gui_widget_write_txt(void *widget, char *color);
void				gui_anti_aliasing_set(int x, int y, int w, int h);
/*
** OBJECTS FUNCTIONS
*/

void				create_sphere(t_env *env, t_vec pos, t_color color,
									double r);
t_obj				*test_sphere(t_env *env, t_ray *ray);
int					test_sphere2(t_env *env, t_vec pos, t_ray ray);
int					test_sphere3(t_env *env, t_vec pos);
void				create_spot(t_env *env, t_vec pos, t_color color);
t_color				test_spot(t_env *env, t_ray *ray, t_obj *obj,
								t_vec point);
void				create_plan(t_env *env, t_vec pos, t_color color,
								t_vec n);
t_obj				*test_plan(t_env *env, t_ray *ray);
int					test_plan2(t_env *env, t_vec pos, t_ray ray);
int					test_plan3(t_env *env, t_vec pos);
void				create_cylinder(t_env *env, t_parse data);
t_obj				*test_cylinder(t_env *env, t_ray *ray);
int					test_cylinder2(t_env *env, t_vec pos, t_ray ray);
int					test_cylinder3(t_env *env, t_vec pos);
void				create_cone(t_env *env, t_parse data);
t_obj				*test_cone(t_env *env, t_ray *ray);
int					test_cone2(t_env *env, t_vec pos, t_ray ray);
int					test_cone3(t_env *env, t_vec pos);
void				trans_rotation(t_env *env);
t_obj				*test_obj(t_env *env, t_ray *ray);

/*
** COMPOSED OBJECTS
*/

int					compose_obj(t_env *env, t_ray *ray, float dist);
t_obj				*create_plan_compose(t_vec pos, t_color color, t_vec n);
t_obj				*create_sphere_compose(t_vec pos, t_color color, float r);

/*
** PROCEDURAL TEXTURES
*/

t_color				stripe(t_vec point);
t_color				square(t_vec point);
 #endif
