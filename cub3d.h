/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:56:34 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/10 17:32:10 by lhuang           ###   ########.fr       */
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

typedef struct	s_dir_pos
{
	double x;
	double y;
	double plane_x;
	double plane_y;
	double angle;
}				t_dir_pos;

typedef struct	s_player_pos
{
	double x;
	double y;
}				t_player_pos;

typedef struct	s_desc
{
	int		resolution_ok;
	int		x;
	int		y;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		floor_ok;
	int		ceiling_ok;
	int		floor_tab[3];
	int		ceiling_tab[3];
	char	**scene;
	int		nb_col;
	int		nb_l;
	int		floor_color;
	int		ceiling_color;
	t_player_pos play_pos;
	t_dir_pos dir_pos;
}				t_desc;

typedef struct	s_mlx_data
{
	void *mlx_ptr;
	void *mlx_win;
	void *img_ptr;
	char *data;
	int bits_per_pixel;
	int size_line;
	int endian;
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

//ft_is.c
int		ft_is_space(char c);
int		ft_is_number(char c);
int		ft_is_print(char c);
int		ft_is_scene_element(char c);
int		ft_is_player_start(char c);

//ft_utils.c
int		ft_strlen(char *str);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strjoin(char *str1, char *str2, int rd);
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
int		ft_check_file_content(char *str, t_desc *desc);


#endif
