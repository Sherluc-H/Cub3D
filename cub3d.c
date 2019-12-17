/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/17 15:42:09 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# define ROTATION_ANGLE 10
# define MOVE_DIST 0.06

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
	// desc->dir_pos.angle = 0;
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

void ft_get_color_tab(int color, int color_tab[3])
{
	color_tab[0] = color / 65536;
	color = color - (color / 65536) * 65536;//sans red
	color_tab[1] = color / 256;
	color = color - (color / 256) * 256; // sans vert
	color_tab[2] = color;
}

void	ft_put_pixel_to_image(t_mlx_data mlx_data, int x, int y, int color_tab[3])
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (unsigned char)(color_tab[0]);
	g = (unsigned char)(color_tab[1]);
	b = (unsigned char)(color_tab[2]);
	mlx_data.main_image.data[y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 2] = r;
	mlx_data.main_image.data[y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 1] = g;
	mlx_data.main_image.data[y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 0] = b;
	// if (y == 0)
	// {
	// printf("->%d, %d, %d | %d, %d, %d\n", y * size_line + x * bits_per_pixel / 8, y * size_line + x * bits_per_pixel / 8 + 1, y * size_line + x * bits_per_pixel / 8 + 2, r, g, b);
	// }
	// else if (y == desc.y - 1)
	// {
	// printf("->%d, %d, %d | %d, %d, %d\n", y * size_line + x * bits_per_pixel / 8, y * size_line + x * bits_per_pixel / 8 + 1, y * size_line + x * bits_per_pixel / 8 + 2, r, g, b);
	// }
}

int ft_init_texture(t_mlx_data *mlx_data)
{
	if (!(mlx_data->t_north.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->north, &(mlx_data->t_north.width), &(mlx_data->t_north.height))))
		return (-1);
	if (!(mlx_data->t_south.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->south, &(mlx_data->t_south.width), &(mlx_data->t_south.height))))
		return (-1);
	if (!(mlx_data->t_west.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->west, &(mlx_data->t_west.width), &(mlx_data->t_west.height))))
		return (-1);
	if (!(mlx_data->t_east.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->east, &(mlx_data->t_east.width), &(mlx_data->t_east.height))))
		return (-1);
	if (!(mlx_data->t_sprite.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->sprite, &(mlx_data->t_sprite.width), &(mlx_data->t_sprite.height))))
		return (-1);
	mlx_data->t_north.image_data.data = mlx_get_data_addr(mlx_data->img_ptr, &(mlx_data->t_north.image_data.bits_per_pixel), &(mlx_data->t_north.image_data.size_line), &(mlx_data->t_north.image_data.endian));
	mlx_data->t_south.image_data.data = mlx_get_data_addr(mlx_data->img_ptr, &(mlx_data->t_south.image_data.bits_per_pixel), &(mlx_data->t_south.image_data.size_line), &(mlx_data->t_south.image_data.endian));
	mlx_data->t_west.image_data.data = mlx_get_data_addr(mlx_data->img_ptr, &(mlx_data->t_west.image_data.bits_per_pixel), &(mlx_data->t_west.image_data.size_line), &(mlx_data->t_west.image_data.endian));
	mlx_data->t_east.image_data.data = mlx_get_data_addr(mlx_data->img_ptr, &(mlx_data->t_east.image_data.bits_per_pixel), &(mlx_data->t_east.image_data.size_line), &(mlx_data->t_east.image_data.endian));
	mlx_data->t_sprite.image_data.data = mlx_get_data_addr(mlx_data->img_ptr, &(mlx_data->t_sprite.image_data.bits_per_pixel), &(mlx_data->t_sprite.image_data.size_line), &(mlx_data->t_sprite.image_data.endian));
	return (1);
}

int ft_display_texture_top(t_mlx_data mlx_data)
{
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_north.img_ptr, 0, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_south.img_ptr, mlx_data.t_north.width, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_west.img_ptr, mlx_data.t_north.width + mlx_data.t_south.width, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_east.img_ptr, mlx_data.t_north.width + mlx_data.t_south.width + mlx_data.t_west.width, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_sprite.img_ptr, mlx_data.t_north.width + mlx_data.t_south.width + mlx_data.t_west.width + mlx_data.t_east.width, mlx_data.desc->y - 64);
	return (1);
}

int ft_display_map(t_desc *desc, t_mlx_data mlx_data)
{
	int x;
	int y;
	int j;
	int k;
	int m;
	int l;
	int draw_size_fixed;
	int draw_size;
	int color_tab[3];
	int color;
	double angle_degre = 0.66;

	x = 0;
	y = 0;
	j = 0;
	k = 0;
	draw_size = (desc->y/5)/desc->nb_l < (desc->x/5)/desc->nb_col ? (desc->y/5)/desc->nb_l : (desc->x/5)/desc->nb_col;
	draw_size_fixed = draw_size;
	while (desc->scene[j])
	{
		k = 0;
		while (desc->scene[j][k])
		{
			if (desc->scene[j][k] == '1')
			{
				l = 0;
				y = j * draw_size_fixed;
				while (y + l < y + draw_size_fixed)
				{
					x = k*draw_size_fixed;
					m = 0;
					while (x + m < x + draw_size_fixed)
					{
						ft_put_pixel_to_image(mlx_data, x + m, y + l, desc->floor_tab);
						m++;
					}
					l++;
				}
			}
			else if(desc->scene[j][k] == '2')
			{
				l = 0;
				ft_get_color_tab(GREEN, color_tab);
				while (y + l < y + draw_size_fixed)
				{
					x = k*draw_size_fixed;
					m = 0;
					while (x + m < x + draw_size_fixed)
					{
						ft_put_pixel_to_image(mlx_data, x + m, y + l, color_tab);
						m++;
					}
					l++;
				}
			}
			else if(desc->scene[j][k] != '\0')
			{
				l = 0;
				y = j * draw_size_fixed;
				while (y + l < y + draw_size_fixed)
				{
					x = k*draw_size_fixed;
					m = 0;
					while (x + m < x + draw_size_fixed)
					{
						ft_put_pixel_to_image(mlx_data, x + m, y + l, desc->ceiling_tab);
						m++;
					}
					l++;
				}
			}
			k++;
		}
		j++;
	}
	//player
	l = 0;
	ft_get_color_tab(RED, color_tab);
	y = draw_size_fixed * desc->play_pos.y;
	x = draw_size_fixed * desc->play_pos.x;
	ft_put_pixel_to_image(mlx_data, x, y, color_tab);
	ft_put_pixel_to_image(mlx_data, x + 1, y + 1, color_tab);
	ft_put_pixel_to_image(mlx_data, x - 1, y - 1, color_tab);
	ft_put_pixel_to_image(mlx_data, x + 1, y - 1, color_tab);
	ft_put_pixel_to_image(mlx_data, x - 1, y + 1, color_tab);
	ft_put_pixel_to_image(mlx_data, x, y + 1, color_tab);
	ft_put_pixel_to_image(mlx_data, x, y - 1, color_tab);
	ft_put_pixel_to_image(mlx_data, x + 1, y, color_tab);
	ft_put_pixel_to_image(mlx_data, x - 1, y, color_tab);
	//camera
	// double x1, y1;
	// double x2, y2;
	// double dx, dy;
	// double a;
	// double b;
	// double c;

	// b = 0;
	// a = 0.;
	// x1 = desc->play_pos.x * draw_size_fixed;
	// y1 = desc->play_pos.y * draw_size_fixed;
	// x2 = x1 + desc->dir_pos.x * draw_size_fixed;
	// y2 = y1 + desc->dir_pos.y * draw_size_fixed;
	// if ( x1 != x2 )
	// {
	// 	dx = fabs(x2 - x1);
	// 	dy = fabs(y2 - y1);
	// 	printf("%f, %f    !\n", dx, dy);
	// 	a = dy / dx;
		color = YELLOW;
		ft_get_color_tab(YELLOW, color_tab);
	// 			printf("x1 = %f, y1 = %f", x1, y1);

	// 		printf("x2 = %f, y2 = %f\n", x2, y2);
	// 	printf("%f\n", a);
	// 	while (b < 11)
	// 	{
	// 		// c = a*x1+y1;
	// 		// printf("%f, %f, %f, %f\n", a, x1, y1, c);
	// 		// printf("->>>x1 = %f, y1 = %f\n", x1, y1);
	// 		// ft_put_pixel_to_image(mlx_data, x1, c, color_tab);
	// 		// x1+= 0.1;
	// 		// b++;
	// 		c = a*(b*10)+y1;
	// 		printf("%f, %f, %f, %f\n", a, x1, y1, c);
	// 		printf("->>>x1 = %f, y1 = %f\n", x1, y1);
	// 		ft_put_pixel_to_image(mlx_data, x1+(b*10), c, color_tab);
	// 		x1+= 0.1;
	// 		b += 0.1;
	// 	}
	// }
	x = desc->play_pos.x * draw_size_fixed + 10/2 * desc->dir_pos.x - draw_size_fixed/4;
	m = 0;
	printf("->%d, \n", draw_size_fixed);
	while (x + m < x + draw_size_fixed / 2)
	{
		l = 0;
		y = desc->play_pos.y * draw_size_fixed + 10/2 * desc->dir_pos.y - draw_size_fixed/4;
		while (y + l < y + draw_size_fixed / 2)
		{
			// if ((m == l) || (draw_size_fixed - m == l))
				ft_put_pixel_to_image(mlx_data, x + m, y + l, color_tab);
			l++;
		}
		m++;
	}
	return (1);
}

void ft_draw_walls(t_mlx_data mlx_data)
{
	int j;
	int x;
	int i;
	double pos_y = mlx_data.desc->play_pos.y;
	double pos_x = mlx_data.desc->play_pos.x;
	int color_tab[3];
	
	j = 0;
	x = 0;
	i = 0;
	while (x < mlx_data.desc->x)
	{
		double camera_x = 2 * x / (double)mlx_data.desc->x - 1.;
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
		int side_left = 0;
		int side_right = 0;
		int top = 1;
		int left = 1;
		if (raydir_x < 0)
		{
			step_x = -1;
			sidedist_x = (pos_x - map_x) * deltadist_x;
		}
		else if ( raydir_x != 0)
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - pos_x) * deltadist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (pos_y - map_y) * deltadist_y;
		}
		else if (raydir_y != 0)
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - pos_y) * deltadist_y;
		}
		if (raydir_y > 0)
		{
			top = -1;
		}
		if (raydir_x > 0)
		{
			left = -1;
		}
		while (hit == 0)
		{		
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				map_x += step_x;
				side = 1;
			}
			else
			{
				sidedist_y += deltadist_y;
				map_y += step_y;
				side = 0;
			}
			if (mlx_data.desc->scene[map_y][map_x] > '0')
				hit = 1;
		}

		if (side == 0)
			perpwalldist = (map_y - pos_y + (1 - step_y) / 2) / (double)raydir_y;
		else
			perpwalldist = (map_x - pos_x + (1 - step_x) / 2) / (double)raydir_x;
		int line_height;
		// if (floor(perpwalldist) != 0)
		if (fabs(perpwalldist) > 0.00001)
			line_height = (int)(mlx_data.desc->y / perpwalldist);
		else
			line_height = (int)(mlx_data.desc->y / 1);
		// printf("%d, %f \n", line_height, perpwalldist);
		int draw_start = -line_height / 2 + mlx_data.desc->y/2;
		if(draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + mlx_data.desc->y /2;
		if (draw_end >= mlx_data.desc->y)
			draw_end = mlx_data.desc->y - 1;
		int color = 0;
		if (mlx_data.desc->scene[map_y][map_x] == '1' && left == 1 && side)//left-EAST
		{
			color = DARK_YELLOW;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '1' && left == -1 && side)//right-WEST
		{
			color = DARK_GREEN;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '1' && top == 1 && !side)//top-NORTH
		{
			color = RED;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '1' && top == -1 && !side)//bottom-SOUTH
		{
			color = BLACK;
		}
		else if (mlx_data.desc->scene[map_y][map_x] == '2')
		{
			color = GREEN;
		}
		else
			color = WHITE;
		ft_get_color_tab(color, color_tab);
		j = 0;
		i = 0;
			// printf("start:%d, end%d\n ", draw_start, draw_end);
		while (j < draw_start)
		{
			ft_put_pixel_to_image(mlx_data, x, j, mlx_data.desc->ceiling_tab);
			j++;
		}
		j = 0;
		while (draw_end + j < mlx_data.desc->y)
		{
			ft_put_pixel_to_image(mlx_data, x, draw_end + j, mlx_data.desc->floor_tab);
			j++;
		}
		j = 0;
		while (draw_start + j < draw_end)
		{
			ft_put_pixel_to_image(mlx_data, x, draw_start + j, color_tab);
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
	double camera_rot_angle;
	if (key == KEY_ESC)
		ft_exit_hook(mlx_data);
	else if(key == KEY_LEFT)//arrow left
	{
		camera_rot_angle = (M_PI/180) * ROTATION_ANGLE;
		double old_dir_x = mlx_data->desc->dir_pos.x;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x * cos(-camera_rot_angle) - mlx_data->desc->dir_pos.y * sin(-camera_rot_angle);
		mlx_data->desc->dir_pos.y = old_dir_x * sin(-camera_rot_angle) + mlx_data->desc->dir_pos.y * cos(-camera_rot_angle);
		double old_plane_x = mlx_data->desc->dir_pos.plane_x;
		mlx_data->desc->dir_pos.plane_x = mlx_data->desc->dir_pos.plane_x * cos(-camera_rot_angle) - mlx_data->desc->dir_pos.plane_y * sin(-camera_rot_angle);
		mlx_data->desc->dir_pos.plane_y = old_plane_x * sin(-camera_rot_angle) + mlx_data->desc->dir_pos.plane_y * cos(-camera_rot_angle);
		ft_draw_walls(*mlx_data);
		if ((ft_display_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	else if(key == KEY_RIGHT)//arrow right
	{
		camera_rot_angle = (M_PI/180) * ROTATION_ANGLE;
		double old_dir_x = mlx_data->desc->dir_pos.x;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x * cos(camera_rot_angle) - mlx_data->desc->dir_pos.y * sin(camera_rot_angle);
		mlx_data->desc->dir_pos.y = old_dir_x * sin(camera_rot_angle) + mlx_data->desc->dir_pos.y * cos(camera_rot_angle);
		double old_plane_x = mlx_data->desc->dir_pos.plane_x;
		mlx_data->desc->dir_pos.plane_x = mlx_data->desc->dir_pos.plane_x * cos(camera_rot_angle) - mlx_data->desc->dir_pos.plane_y * sin(camera_rot_angle);
		mlx_data->desc->dir_pos.plane_y = old_plane_x * sin(camera_rot_angle) + mlx_data->desc->dir_pos.plane_y * cos(camera_rot_angle);
		ft_draw_walls(*mlx_data);
		if ((ft_display_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	else if (key == KEY_W || key == KEY_Z)//move up
	{//need improvement right box for example
		if (fabs(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST) - (int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST))) < 0.000001)
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST) - 1)] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * MOVE_DIST;
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * (MOVE_DIST))][(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST) - 1)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * MOVE_DIST;
		}
		else
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST))] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST);
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * (MOVE_DIST))][(int)(mlx_data->desc->play_pos.x)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
		ft_draw_walls(*mlx_data);
		if ((ft_display_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	else if (key == KEY_S)//down
	{
		if (fabs(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST) - (int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST))) < 0.000001)
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST) - 1)] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * MOVE_DIST;
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * (MOVE_DIST))][(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST) - 1)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * MOVE_DIST;
		}
		else
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST))] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * MOVE_DIST;
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * (MOVE_DIST))][(int)(mlx_data->desc->play_pos.x)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * MOVE_DIST;
		}
		ft_draw_walls(*mlx_data);
		if ((ft_display_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	else if (key == KEY_A || key == KEY_Q)//move left
	{
		if (fabs(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST) - (int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST))) < 0.000001)
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST + MOVE_DIST/10))] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
		else
		{

			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST))] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST);			
		}
		if (fabs(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST) - (int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST))) < 0.000001)
		{
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST + MOVE_DIST/10))][(int)(mlx_data->desc->play_pos.x)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
		else
		{
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST))][(int)(mlx_data->desc->play_pos.x)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
		ft_draw_walls(*mlx_data);
		if ((ft_display_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	else if (key == KEY_D)//right
	{
		if (fabs(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST) - (int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST))) < 0.000001)
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST + MOVE_DIST / 10))] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST);			
		}
		else
		{
			if (mlx_data->desc->scene[(int)mlx_data->desc->play_pos.y][(int)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST))] == '0')
				mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
		if (fabs(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST) - (int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST))) < 0.000001)
		{
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST + MOVE_DIST / 10))][(int)(mlx_data->desc->play_pos.x)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
		else
		{
			if (mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST))][(int)(mlx_data->desc->play_pos.x)] == '0')
				mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
		ft_draw_walls(*mlx_data);
		if ((ft_display_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	// printf("x = %f, int x = %d, y = %f, int y = %d|%c|\n", mlx_data->desc->play_pos.x, (int)(mlx_data->desc->play_pos.x), mlx_data->desc->play_pos.y, (int)(mlx_data->desc->play_pos.y), mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y)][(int)(mlx_data->desc->play_pos.x)]);
	// printf("dir x = %f, int plane x = %f, dir y = %f, int plane y = %f\n", mlx_data->desc->dir_pos.x, mlx_data->desc->dir_pos.plane_x, mlx_data->desc->dir_pos.y, mlx_data->desc->dir_pos.plane_y);
	printf("key pressed = %d\n", key);
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
	ft_print_desc(&desc);
	mlx_data.img_ptr = mlx_new_image(mlx_data.mlx_ptr, desc.x, desc.y);
	mlx_data.main_image.data = mlx_get_data_addr(mlx_data.img_ptr, &mlx_data.main_image.bits_per_pixel, &mlx_data.main_image.size_line, &mlx_data.main_image.endian);
	ft_init_texture(&mlx_data);
	ft_draw_walls(mlx_data);
	if ((ft_display_map(&desc, mlx_data)) == -1)
		return (-1);
	mlx_do_key_autorepeaton(mlx_data.mlx_ptr);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.img_ptr, 0, 0);
	if ((ft_display_texture_top(mlx_data)) == -1)
	{
		write(1, "problem with texture\n", 21);
		ft_exit_hook(&mlx_data);
		return (-1);
	}
	mlx_hook(mlx_data.win_ptr, 2, 0, ft_key_pressed, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 17, 0, ft_exit_hook, &mlx_data);//bouton X pour quitter
	mlx_loop(mlx_data.mlx_ptr);
	return (1);
}
