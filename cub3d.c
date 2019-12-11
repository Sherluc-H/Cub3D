/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/11 18:38:10 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# define RED 16711680
# define BLUE 255
# define GREEN 65280
# define BLACK 0
# define WHITE 16777215

void	ft_init_desc(t_desc *desc)
{
	desc->resolution_ok = 0;
	desc->x = 0;
	desc->y = 0;
	desc->north = NULL;
	desc->south = NULL;
	desc->west = NULL;
	desc->east = NULL;
	desc->sprite = NULL;
	desc->floor_ok = 0;
	desc->ceiling_ok = 0;
	desc->scene = NULL;
	desc->nb_col = 0;
	desc->nb_l = 0;
	desc->floor_color = 0;
	desc->ceiling_color = 0;
	desc->play_pos.x = 0.;
	desc->play_pos.y = 0.;
	desc->dir_pos.x = 0.;
	desc->dir_pos.y = 0.;
	desc->dir_pos.angle = 0.;
}
void	ft_freer(t_desc *desc)
{
	int j;

	j = 0;
	free(desc->north);
	free(desc->south);
	free(desc->west);
	free(desc->east);
	while (desc->scene[j])
	{
		free(desc->scene[j]);
		j++;
	}
	free(desc->scene);
}

int ft_exit_hook(t_mlx_data *mlx_data)
{
	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	ft_freer(mlx_data->desc);
	system("leaks Cub3D");
	exit(0);
	return(0);
}

void ft_print_desc(t_desc *desc)
{
	printf("x = %d\n", desc->x);
	printf("y = %d\n", desc->y);
	printf("north = %s\n", desc->north);
	printf("south = %s\n", desc->south);
	printf("west = %s\n", desc->west);
	printf("east = %s\n", desc->east);
	printf("sprite = %s\n", desc->sprite);
	printf("resolution_ok = %d\n", desc->resolution_ok);
	printf("floor_ok = %d\n", desc->floor_ok);
	printf("ceiling_ok = %d\n", desc->ceiling_ok);
	printf("floor color = %d, %d, %d\n", desc->floor_tab[0], desc->floor_tab[1], desc->floor_tab[2]);
	printf("ceiling color = %d, %d, %d\n", desc->ceiling_tab[0], desc->ceiling_tab[1], desc->ceiling_tab[2]);
	printf("col = %d\n", desc->nb_col);
	printf("lines = %d\n", desc->nb_l);
	printf("floor color = %d\n", desc->floor_color);
	printf("ceiling color = %d\n", desc->ceiling_color);
	printf("play x = %f\n", desc->play_pos.x);
	printf("play y = %f\n", desc->play_pos.y);
	printf("dir x = %f\n", desc->dir_pos.x);
	printf("dir y = %f\n", desc->dir_pos.y);
}

void ft_print_map(t_desc *desc)
{
	int i;
	int j;

	j = 0;
	printf("---MAP---\n");
	while (desc->scene[j])
	{
		i = 0;
		while (desc->scene[j][i])
		{
			printf("%c", desc->scene[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("---END---\n");
}

void	ft_put_pixel_to_image(t_desc desc, char *data, int bits_per_pixel, int size_line, int x, int y, int color_tab[3])
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (unsigned char)(color_tab[0]);
	g = (unsigned char)(color_tab[1]);
	b = (unsigned char)(color_tab[2]);
	data[y * size_line + x * bits_per_pixel / 8 + 2] = r;
	data[y * size_line + x * bits_per_pixel / 8 + 1] = g;
	data[y * size_line + x * bits_per_pixel / 8 + 0] = b;
	// if (y == 0)
	// {
	// printf("->%d, %d, %d | %d, %d, %d\n", y * size_line + x * bits_per_pixel / 8, y * size_line + x * bits_per_pixel / 8 + 1, y * size_line + x * bits_per_pixel / 8 + 2, r, g, b);
	// }
	// else if (y == desc.y - 1)
	// {
	// printf("->%d, %d, %d | %d, %d, %d\n", y * size_line + x * bits_per_pixel / 8, y * size_line + x * bits_per_pixel / 8 + 1, y * size_line + x * bits_per_pixel / 8 + 2, r, g, b);

	// }
}

// int ft_display_map(t_desc *desc, t_mlx_data mlx_data)
// {
// 	int x;
// 	int y;
// 	int j;
// 	int k;
// 	int m;
// 	int l;
// 	int draw_size_fixed;
// 	int draw_size;

// 	x = 0;
// 	y = 0;
// 	j = 0;
// 	k = 0;
// 	draw_size = (desc->x/3)/desc->nb_l < (desc->x/3)/desc->nb_col ? (desc->x/3)/desc->nb_l : (desc->x/3)/desc->nb_col;
// 	draw_size_fixed = draw_size;
// 	while (j < desc->y)
// 	{
// 		k = 0;
// 		while (k < desc->x)
// 		{ 
// 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, k, j, desc->ceiling_color);
// 			k++;
// 		}
// 		j++;
// 	}
// 	j = 0;
// 	k = 0;
// 	while (desc->scene[j])
// 	{
// 		k = 0;
// 		while (desc->scene[j][k])
// 		{
// 			if (desc->scene[j][k] == '1')
// 			{
// 				l = 0;
// 				// y = j * draw_size_fixed;
// 				// while (y + l < y + draw_size_fixed)
// 				// {
// 				// 	x = k*draw_size_fixed;
// 				// 	m = 0;
// 				// 	while (x + m < x + draw_size_fixed)
// 				// 	{
// 				// 		mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m, y + l, desc->floor_color);
// 				// 		m++;
// 				// 	}
// 				// 	l++;
// 				// }
// 			}
// 			else if(ft_is_player_start(desc->scene[j][k]))
// 			{
// 				l = 0;
// 				// y = j * draw_size_fixed;
// 				// desc->play_pos.x = k*draw_size_fixed;
// 				desc->play_pos.x = k;
// 				// printf("here %f\n", desc->play_pos.y);
// 				// desc->play_pos.y = j*draw_size_fixed;
// 				desc->play_pos.y = j;
// 				// printf("here %f\n", desc->play_pos.y);
// 				// while (y + l < y + draw_size_fixed / 2)
// 				// {
// 				// 	x = k*draw_size_fixed;
// 				// 	m = 0;
// 				// 	// printf("%d, %d, %d, %d, %d\n", y + draw_size_fixed / 2, x + draw_size_fixed / 2,draw_size_fixed / 2, draw_size_fixed, draw_size_fixed/4);
// 				// 	while (x + m < x + draw_size_fixed / 2)
// 				// 	{
// 				// 		mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 0);
// 				// 		m++;
// 				// 	}
// 				// 	l++;
// 				// }
// 			}
// 			else if(desc->scene[j][k] != '\0')
// 			{
// 				l = 0;
// 				// y = j * draw_size_fixed;
// 				// while (y + l < y + draw_size_fixed)
// 				// {
// 				// 	x = k*draw_size_fixed;
// 				// 	m = 0;
// 				// 	while (x + m < x + draw_size_fixed)
// 				// 	{
// 				// 		mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m, y + l, desc->ceiling_color);
// 				// 		m++;
// 				// 	}
// 				// 	l++;
// 				// }
// 			}
// 			k++;
// 		}
// 		j++;
// 	}
// 	l = 0;
// 	y = desc->play_pos.y + 10 * desc->dir_pos.y;
// 	// desc->dir_pos.y = y;
// 	// desc->dir_pos.x = desc->play_pos.x + 10 * desc->dir_pos.x;
// 	while (y + l < y + draw_size_fixed / 2)
// 	{
// 		// x = desc->dir_pos.x;
// 		x = desc->play_pos.x + 10 * desc->dir_pos.x;
// 		// desc->dir_pos.x = x;
// 		m = 0;
// 		// printf("%d, %d, %d, %d, %d\n", y + draw_size_fixed / 2, x + draw_size_fixed / 2,draw_size_fixed / 2, draw_size_fixed, draw_size_fixed/4);
// 		while (x + m < x + draw_size_fixed / 2)
// 		{
// 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 16711680);
// 			m++;
// 		}
// 		l++;
// 	}
// 	return (1);
// }

// int ft_redraw_map(t_desc *desc, t_mlx_data mlx_data)
// {
// 	int x;
// 	int y;
// 	int j;
// 	int k;
// 	int m;
// 	int l;
// 	int draw_size_fixed;
// 	int draw_size;

// 	x = 0;
// 	y = 0;
// 	j = 0;
// 	k = 0;
// 	draw_size = (desc->y/3)/desc->nb_l < (desc->y/3)/desc->nb_col ? (desc->y/3)/desc->nb_l : (desc->y/3)/desc->nb_col;
// 	draw_size_fixed = draw_size;
// 	j = 0;
// 	k = 0;
// 	while (desc->scene[j])
// 	{
// 		k = 0;
// 		while (desc->scene[j][k])
// 		{
// 			if (desc->scene[j][k] == '1')
// 			{
// 				l = 0;
// 				y = j * draw_size_fixed;
// 				while (y + l < y + draw_size_fixed)
// 				{
// 					x = k*draw_size_fixed;
// 					m = 0;
// 					while (x + m < x + draw_size_fixed)
// 					{
// 						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m, y + l, desc->floor_color);
// 						m++;
// 					}
// 					l++;
// 				}
// 			}
// 			else if(desc->scene[j][k] != '\0')
// 			{
// 				l = 0;
// 				y = j * draw_size_fixed;
// 				while (y + l < y + draw_size_fixed)
// 				{
// 					x = k*draw_size_fixed;
// 					m = 0;
// 					while (x + m < x + draw_size_fixed)
// 					{
// 						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m, y + l, desc->ceiling_color);
// 						m++;
// 					}
// 					l++;
// 				}
// 			}
// 			k++;
// 		}
// 		j++;
// 	}
// 	//draw player
// 	l = 0;
// 	y = desc->play_pos.y;
// 	while (y + l < y + draw_size_fixed / 2)
// 	{
// 		x = desc->play_pos.x;
// 		m = 0;
// 		while (x + m < x + draw_size_fixed / 2)
// 		{
// 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 0);
// 			m++;
// 		}
// 		l++;
// 	}
// 	//draw dir
// 	l = 0;
// 	y = desc->dir_pos.y;
// 	while (y + l < y + draw_size_fixed / 2)
// 	{
// 		x = desc->dir_pos.x;
// 		m = 0;
// 		while (x + m < x + draw_size_fixed / 2)
// 		{
// 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 16711680);
// 			m++;
// 		}
// 		l++;
// 	}
// 	return (1);
// }

void ft_draw_walls(t_desc desc, t_mlx_data mlx_data, char *data, int bits_per_pixel, int size_line, int endian)
{
	int j;
	int x;
	double pos_y = mlx_data.desc->play_pos.y;
	double pos_x = mlx_data.desc->play_pos.x;
	int color_tab[3];
	
	j = 0;
	x = 0;
	while (x < desc.x)
	{
		double camera_x = 2 * x / (double)desc.x - 1;
		double raydir_x = mlx_data.desc->dir_pos.x + mlx_data.desc->dir_pos.plane_x * camera_x;
		double raydir_y = mlx_data.desc->dir_pos.y + mlx_data.desc->dir_pos.plane_y * camera_x;
		int map_x = (int)pos_x;
		int map_y = (int)pos_y;
		double sidedist_x;
		double sidedist_y;
		double deltadist_x = fabs(1.0/raydir_x);
		double deltadist_y = fabs(1.0/raydir_y);
		double perpwalldist;
		int step_x;
		int step_y;
		int hit = 0;
		int side;
		if (raydir_x < 0)
		{
			step_x = -1;
			sidedist_x = (pos_x - map_x) * deltadist_x;
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - pos_x) * deltadist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (pos_y - map_y) * deltadist_y;
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - pos_y) * deltadist_y;
		}
		while (hit == 0)
		{		
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				sidedist_y += deltadist_y;
				map_y += step_y;
				side = 1;				
			}
			if (mlx_data.desc->scene[map_x][map_y] > '0')
				hit = 1;
		}
		if (side == 0)
			perpwalldist = (map_x - pos_x + (1 - step_x) / 2) / raydir_x;
		else
			perpwalldist = (map_y - pos_y + (1 - step_y) / 2) / raydir_y;
		int line_height = (int)(desc.y / perpwalldist);
		int draw_start = -line_height / 2 + desc.y/2;
		if(draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + desc.y /2;
		if (draw_end >= desc.y)
			draw_end = desc.y - 1;
		int color = 0;
		if (desc.scene[map_x][map_y] == '1')
			color = RED;
		else if (desc.scene[map_x][map_y] == '2')
			color = GREEN;
		else
			color = WHITE;
		if (side == 1)
			color = color / 2;
		color_tab[0] = color / 65536;
		// printf("%d,", color / 65536);
		color = color - (color / 65536) * 65536;//sans red
		color_tab[1] = color / 256;
		// printf("%d,", color / 256);
		color = color - (color / 256) * 256; // sans vert
		color_tab[2] = color;
		// printf("%d\n", color);
		j = 0;
		while (j < draw_start)
		{
			ft_put_pixel_to_image(desc, data, bits_per_pixel, size_line, x, j, desc.ceiling_tab);
			j++;
		}
		while (j < draw_end)
		{
			ft_put_pixel_to_image(desc, data, bits_per_pixel, size_line, x, j, color_tab);
			j++;
		}
		while (j < desc.y)
		{
			ft_put_pixel_to_image(desc, data, bits_per_pixel, size_line, x, j, desc.floor_tab);
			j++;
		}
		x++;
	}
}

int ft_key_pressed(int key, t_mlx_data *mlx_data)
{
	double x;
	double y;
	double play_x;
	double play_y;
	double decalage_x;
	double decalage_y;
	double camera_move_angle;
	if (key == 53)
		ft_exit_hook(mlx_data);
	else if(key == 123)//arrow left
	{
		camera_move_angle = (M_PI/180) * 10;
		// play_x = mlx_data->desc->play_pos.x;
		// play_y = mlx_data->desc->play_pos.y;
		// x = mlx_data->desc->dir_pos.x + play_x;
		// y = mlx_data->desc->dir_pos.y + play_y;
		// // printf("angle %f\n", mlx_data->desc->dir_pos.angle);
		// decalage_x = ((x - play_x) * cos(-0.1)) - ((y - play_y) * sin(-0.1));
		// decalage_y = ((x - play_x) * sin(-0.1)) + ((y - play_y) * cos(-0.1));
		// // mlx_data->desc->dir_pos.x = decalage_x + play_x;
		// // mlx_data->desc->dir_pos.y = decalage_y + play_y;
		// mlx_data->desc->dir_pos.x = decalage_x;
		// mlx_data->desc->dir_pos.y = decalage_y;
		// // printf("%f\n", mlx_data->desc->play_pos.x);
		// // printf("%f\n", mlx_data->desc->play_pos.y);
		// // printf("%f\n", mlx_data->desc->dir_pos.x);
		// // printf("%f\n", mlx_data->desc->dir_pos.y);
		// // ft_redraw_map(mlx_data->desc, *mlx_data);
		// ft_draw_base(*mlx_data);
		double old_dir_x = mlx_data->desc->dir_pos.x;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x * cos(camera_move_angle) - mlx_data->desc->dir_pos.y * sin(camera_move_angle);
		mlx_data->desc->dir_pos.y = old_dir_x * sin(camera_move_angle) + mlx_data->desc->dir_pos.y * cos(camera_move_angle);
		double old_plane_x = mlx_data->desc->dir_pos.plane_x;
		mlx_data->desc->dir_pos.plane_x = mlx_data->desc->dir_pos.plane_x * cos(camera_move_angle) - mlx_data->desc->dir_pos.plane_y * sin(camera_move_angle);
		mlx_data->desc->dir_pos.plane_y = old_plane_x * sin(camera_move_angle) + mlx_data->desc->dir_pos.plane_y * cos(camera_move_angle);
		ft_draw_walls(*(mlx_data->desc), *mlx_data, mlx_data->data, mlx_data->bits_per_pixel, mlx_data->size_line, mlx_data->endian);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	}
	else if(key == 124)//arrow right
	{
		camera_move_angle = (M_PI/180) * 10;
		// play_x = mlx_data->desc->play_pos.x;
		// play_y = mlx_data->desc->play_pos.y;
		// x = mlx_data->desc->dir_pos.x + play_x;
		// y = mlx_data->desc->dir_pos.y + play_y;
		// // printf("angle %f\n", mlx_data->desc->dir_pos.angle);
		// decalage_x = ((x - play_x) * cos(0.1)) - ((y - play_y) * sin(0.1));
		// decalage_y = ((x - play_x) * sin(0.1)) + ((y - play_y) * cos(0.1));
		// // mlx_data->desc->dir_pos.x = decalage_x + play_x;
		// // mlx_data->desc->dir_pos.y = decalage_y + play_y;
		// mlx_data->desc->dir_pos.x = decalage_x;
		// mlx_data->desc->dir_pos.y = decalage_y;
		// // printf("%f\n", mlx_data->desc->play_pos.x);
		// // printf("%f\n", mlx_data->desc->play_pos.y);
		// // printf("%f\n", mlx_data->desc->dir_pos.x);
		// // printf("%f\n", mlx_data->desc->dir_pos.y);
		// // ft_redraw_map(mlx_data->desc, *mlx_data);
		// ft_draw_base(*mlx_data);
		double old_dir_x = mlx_data->desc->dir_pos.x;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x * cos(-camera_move_angle) - mlx_data->desc->dir_pos.y * sin(-camera_move_angle);
		mlx_data->desc->dir_pos.y = old_dir_x * sin(-camera_move_angle) + mlx_data->desc->dir_pos.y * cos(-camera_move_angle);
		double old_plane_x = mlx_data->desc->dir_pos.plane_x;
		mlx_data->desc->dir_pos.plane_x = mlx_data->desc->dir_pos.plane_x * cos(-camera_move_angle) - mlx_data->desc->dir_pos.plane_y * sin(-camera_move_angle);
		mlx_data->desc->dir_pos.plane_y = old_plane_x * sin(-camera_move_angle) + mlx_data->desc->dir_pos.plane_y * cos(-camera_move_angle);
		ft_draw_walls(*(mlx_data->desc), *mlx_data, mlx_data->data, mlx_data->bits_per_pixel, mlx_data->size_line, mlx_data->endian);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	}
	else if (key == 6 || key == 13)//move up
	{
		// mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - 2;
		// mlx_data->desc->dir_pos.y = mlx_data->desc->dir_pos.y - 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		// ft_draw_base(*mlx_data);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x, mlx_data->desc->play_pos.y, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y)]);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * 0.5, mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * 0.5, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * 0.5)][(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * 0.5)]);
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * 0.5)][(int)mlx_data->desc->play_pos.y] == '0')
			mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * 0.5;
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * 0.5)] == '0')
			mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * 0.5;
		ft_draw_walls(*(mlx_data->desc), *mlx_data, mlx_data->data, mlx_data->bits_per_pixel, mlx_data->size_line, mlx_data->endian);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	}
	else if (key == 1)//down
	{
		// mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + 2;
		// mlx_data->desc->dir_pos.y = mlx_data->desc->dir_pos.y + 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		// ft_draw_base(*mlx_data);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x, mlx_data->desc->play_pos.y, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y)]);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * 0.5, mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * 0.5, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * 0.5)][(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * 0.5)]);
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * 0.5)][(int)mlx_data->desc->play_pos.y] == '0')
			mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * 0.5;
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * 0.5)] == '0')
			mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * 0.5;
		ft_draw_walls(*(mlx_data->desc), *mlx_data, mlx_data->data, mlx_data->bits_per_pixel, mlx_data->size_line, mlx_data->endian);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	}
	else if (key == 0 || key == 12)//move left
	{
		// mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - 2;
		// mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x - 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		// ft_draw_walls(*(mlx_data->desc), *mlx_data);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x, mlx_data->desc->play_pos.y, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y)]);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * 0.5, mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * 0.5, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * 0.5)][(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * 0.5)]);
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * 0.5)][(int)mlx_data->desc->play_pos.y] == '0')
			mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * 0.5;
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * 0.5)] == '0')
			mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * 0.5;
		ft_draw_walls(*(mlx_data->desc), *mlx_data, mlx_data->data, mlx_data->bits_per_pixel, mlx_data->size_line, mlx_data->endian);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	}
	else if (key == 2)//right
	{
		// mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + 2;
		// mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x + 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		// ft_draw_walls(*(mlx_data->desc), *mlx_data);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x, mlx_data->desc->play_pos.y, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y)]);
		printf("x = %f, y = %f, |%c|\n", mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * 0.5, mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * 0.5, mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * 0.5)][(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * 0.5)]);
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * 0.5)][(int)mlx_data->desc->play_pos.y] == '0')
			mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * 0.5;
		if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.x)][(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * 0.5)] == '0')
			mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * 0.5;
		ft_draw_walls(*(mlx_data->desc), *mlx_data, mlx_data->data, mlx_data->bits_per_pixel, mlx_data->size_line, mlx_data->endian);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
	}
	// printf("%d\n", key);
	return (0);
}

int		main(int argc, char **argv)
{
	t_desc desc;
	t_mlx_data mlx_data;

	ft_init_desc(&desc);
	if (!ft_check_args(argc, argv, &desc))
		return (0);
	ft_print_desc(&desc);
	ft_print_map(&desc);
	mlx_data.desc = &desc;
	if (!(mlx_data.mlx_ptr = mlx_init()) || !(mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, desc.x, desc.y, "Cub3D")))
	{
		write(1, "error\n", 6);
		return (-1);		
	}
	// if ((mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, desc.x, desc.y, "Cub3D")) == NULL)
	// {
	// 	write(1, "error\n", 6);
	// 	return (-1);
	// }
	mlx_key_hook(mlx_data.win_ptr, ft_key_pressed, &mlx_data);
	// if ((ft_display_map(&desc, mlx_data)) == -1)
	// 	return (-1);
	ft_print_desc(&desc);
	mlx_data.img_ptr = mlx_new_image(mlx_data.mlx_ptr, desc.x, desc.y);
	mlx_data.data = mlx_get_data_addr(mlx_data.img_ptr, &mlx_data.bits_per_pixel, &mlx_data.size_line, &mlx_data.endian);
	ft_draw_walls(desc, mlx_data, mlx_data.data, mlx_data.bits_per_pixel, mlx_data.size_line, mlx_data.endian);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.img_ptr, 0, 0);
	mlx_hook(mlx_data.win_ptr, 17, 0, ft_exit_hook, &mlx_data);//bouton X pour quitter
	mlx_loop(mlx_data.mlx_ptr);
	return (1);
}
