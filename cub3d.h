/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:56:34 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/04 11:13:34 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define ROTATION_ANGLE 10
# define MOVE_DIST 0.066

# define RED 16711680
# define BLUE 255
# define GREEN 65280
# define DARK_GREEN 3970620
# define BLACK 0
# define WHITE 16777215
# define YELLOW 16776960
# define DARK_YELLOW 9868860
# define KEY_A 0
# define KEY_Q 12
# define KEY_D 2
# define KEY_W 13
# define KEY_Z 6
# define KEY_S 1
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_M 46

typedef enum	e_path
{
	NORTH = 1,
	SOUTH,
	WEST,
	EAST,
	SPRITE
}				t_path;

typedef enum	e_error
{
	MALLOC = 10,
	MLX,
	ARG,
	PARSE,
	OPEN,
	SCENE
}				t_error;

typedef struct	s_remain
{
	char	*str;
	int		size;
}				t_remain;

typedef struct	s_dir_pos
{
	double x;
	double y;
	double plane_x;
	double plane_y;
}				t_dir_pos;

typedef struct	s_player_pos
{
	double x;
	double y;
}				t_player_pos;

typedef struct	s_sprite
{
	double x;
	double y;
}				t_sprite;

typedef struct	s_texture_data
{
	void	*img_ptr;
	int		height;
	int		width;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}				t_texture_data;

typedef struct	s_draw_spt_data
{
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				texture_x;
	int				texture_y;
	t_texture_data	texture;
}				t_draw_spt_data;

typedef struct	s_draw_wall_data
{
	t_player_pos	play_pos;
	t_texture_data	texture;
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			perpwalldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				top;
	int				left;
	int				line_height;
	int				draw_start_y;
	int				draw_end_y;
	double			wall_x;
	int				texture_x;
	int				texture_y;
}				t_draw_wall_data;

typedef struct	s_desc
{
	t_error			error;
	int				resolution_ok;
	int				x;
	int				y;
	int				to_save;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*sprite_path;
	int				floor_ok;
	int				ceiling_ok;
	int				floor_tab[3];
	int				ceiling_tab[3];
	int				player_found;
	int				start_parse_scene;
	char			*scene_str;
	char			**scene;
	int				nb_col;
	int				nb_l;
	int				floor_color;
	int				ceiling_color;
	t_player_pos	play_pos;
	t_dir_pos		dir_pos;
	t_sprite		*sprite_tab;
	int				nb_sprite;
}				t_desc;

typedef struct	s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_texture_data	tex_north;
	t_texture_data	tex_south;
	t_texture_data	tex_west;
	t_texture_data	tex_east;
	t_texture_data	tex_sprite;
	char			*main_img_data;
	int				main_img_bpp;
	int				main_img_size_line;
	int				main_img_endian;
	t_desc			*desc;
	int				map_on;
}				t_mlx_data;

typedef struct	s_map_data
{
	int	element_size;
	int	player_color;
	int camera_color;
	int	wall_color;
	int	empty_color;
	int sprite_color;
}				t_map_data;

int				ft_exit_hook(t_mlx_data *mlx_data);
int				ft_create_scene(t_desc *desc, char *scene_str, int i);
int				ft_check_args(int argc, char **argv, t_desc *desc);
void			ft_add_player(t_desc *desc, char player_char, int j, int l);
int				ft_draw_map(t_mlx_data mlx_data);
int				ft_draw_sprite(t_mlx_data mlx_data, t_desc *desc,
					double *perp_dist_buffer, int i);
void			ft_put_pixel_to_image(t_mlx_data mlx_data, int x,
					int y, int color);
int				ft_get_color_from_texture(t_texture_data texture,
					int texture_x, int texture_y);
void			ft_draw_wall_loop(t_mlx_data mlx_data,
					t_draw_wall_data draw_data, int x, int j);
void			ft_draw_sprite_loop(t_mlx_data mlx_data,
					t_draw_spt_data draw_dt, double *perp_dist_buffer);
int				ft_draw(t_mlx_data mlx_data);
int				ft_move_space(char *str, int *i);
int				ft_end_identifier(char *str, int *i);
int				ft_get_number(char *str, int *i);
int				ft_get_path(char *str, int *i, t_desc *desc, int path_id);
int				ft_get_identifier(char *str, int *i, t_desc *desc);
int				ft_parse_resolution(char *str, t_desc *desc, int *i);
int				ft_parse_path(char *str, t_desc *desc, int *i);
int				ft_parse_color(char *str, int tab[3], int *color_ok,
					int *desc_color);
void			ft_give_path(t_desc *desc, int path_id, char *path);
int				ft_get_next_line(int fd, char **line);
int				ft_init_texture(t_mlx_data *mlx_data);
int				ft_set_error(t_desc *desc, t_error error);
int				ft_show_error(t_error error, t_mlx_data *mlx_data);
void			ft_freer(t_desc *desc);
int				ft_free_remain(t_remain **remain);
int				ft_free_str(char *str, int r);
int				ft_precise_collision(t_mlx_data *mlx_data, double new_play_x,
					double new_play_y);
int				ft_key_pressed(int key, t_mlx_data *mlx_data);
int				ft_is_path_identifier(char *str, int i);
int				ft_is_description_ready_scene(t_desc *desc);
int				ft_is_space(char c);
int				ft_is_number(char c);
int				ft_is_print(char c);
int				ft_is_scene_element(char c);
int				ft_is_player_start(char c);
int				ft_save(t_mlx_data mlx_data);
char			*ft_strjoin_with_sep(char *str1, char *str2, char sep);
char			*ft_strjoin(char *str1, char *str2);
int				ft_strlen(char *str);
int				ft_strcmp(char *str1, char *str2);
int				ft_atoi_simple(char *str);

#endif
