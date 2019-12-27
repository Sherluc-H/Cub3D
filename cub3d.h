/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:56:34 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/27 17:05:00 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define ROTATION_ANGLE 10
# define MOVE_DIST 0.05

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

typedef struct	s_remain
{
	char *str;
	int size;
}				t_remain;

typedef struct	s_dir_pos
{
	double x;
	double y;
	double plane_x;
	double plane_y;
	// int		angle;
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

// typedef struct	s_image_datas
// {
// 	char *data;
// 	int bpp;
// 	int size_line;
// 	int endian;
// }				t_image_datas;

typedef struct	s_texture_datas
{
	void *img_ptr;
	int height;
	int width;
	char *data;
	int bpp;
	int size_line;
	int endian;
}				t_texture_datas;

typedef struct	s_desc
{
	int		resolution_ok;
	int		x;
	int		y;
	int		to_save;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	char	*sprite_path;
	int		floor_ok;
	int		ceiling_ok;
	int		floor_tab[3];
	int		ceiling_tab[3];
	int		player_found;
	int		start_parse_scene;
	char	*scene_str;
	char	**scene;
	int		nb_col;
	int		nb_l;
	int		floor_color;
	int		ceiling_color;
	t_player_pos play_pos;
	t_dir_pos dir_pos;
	t_sprite *sprite_tab;
	int		nb_sprite;
}				t_desc;

typedef struct	s_mlx_data
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	t_texture_datas t_north;
	t_texture_datas t_south;
	t_texture_datas t_west;
	t_texture_datas t_east;
	t_texture_datas t_sprite;
	char *main_img_data;
	// t_image_datas main_image;
	int main_img_bpp;
	int main_img_size_line;
	int main_img_endian;
	t_desc *desc;
}				t_mlx_data;

typedef enum	e_path
{
	NORTH = 1,
	SOUTH,
	WEST,
	EAST,
	SPRITE
}				t_path;

//ft_get_next_line.c
int ft_get_next_line(int fd, char **line);


//ft_is.c
int		ft_is_space(char c);
int		ft_is_number(char c);
int		ft_is_print(char c);
int		ft_is_scene_element(char c);
int		ft_is_player_start(char c);

//ft_utils.c
int		ft_strlen(char *str);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strjoin(char *str1, char *str2);
int		ft_atoi_simple(char *str);

//ft_check_args.c
int		ft_check_file_extension(char *filename, char *extension);
int		ft_check_description(char *filename, t_desc *desc);
int		ft_check_args(int argc, char **argv, t_desc *desc);

//ft_get_description_utils.c
int		ft_move_space(char *str, int *i);
int		ft_end_identifier(char *str, int *i);
int		ft_get_number(char *str, int *i);
int		ft_get_path(char *str, int *i, t_desc *desc, int path_id);
int		ft_get_identifier(char *str, int *i, t_desc *desc);

//ft_get_description.c
int		ft_parse_resolution(char *str, t_desc *desc, int *i);
int		ft_parse_path(char *str, t_desc *desc, int *i);
int		ft_parse_color(char *str, int tab[3], int *color_ok, int *desc_color);
int		ft_is_path_identifier(char *str, int i);
int		ft_is_description_ready_scene(t_desc *desc);

//ft_get_textures.c
int 	ft_init_texture(t_mlx_data *mlx_data);
int 	ft_display_texture_top(t_mlx_data mlx_data);

//ft_draw_utils.c
void 	ft_get_color_tab(int color, int color_tab[3]);
void	ft_put_pixel_to_image(t_mlx_data mlx_data, int x, int y, int color_tab[3]);

//ft_draw.c
int		ft_draw_map(t_desc *desc, t_mlx_data mlx_data);
void	ft_draw_walls(t_mlx_data mlx_data);

//ft_handle_keys.c
int		ft_key_pressed(int key, t_mlx_data *mlx_data);

//ft_cub3d.c
void	ft_freer(t_desc *desc);
int ft_exit_hook(t_mlx_data *mlx_data);

#endif
