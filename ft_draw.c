/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:30:30 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/21 20:54:54 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_draw_map(t_desc *desc, t_mlx_data mlx_data)
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
	// printf("->%d, \n", draw_size_fixed);
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
		int top = 1;
		int left = 1;

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
		//texture
		double wall_x;

		if (side == 0)
		{
			wall_x = pos_x + perpwalldist * raydir_x;
		}
		else
		{
			wall_x = pos_y + perpwalldist * raydir_y;
		}
		wall_x -= floor(wall_x);
		int texture_x = (int)(wall_x * (double)64);
		if (side == 0 && raydir_y > 0)
			texture_x = 64 - texture_x - 1;
		if (side == 1 && raydir_x < 0)
			texture_x = 64 - texture_x - 1;
		t_texture_datas texture;
		texture = mlx_data.t_north;

		if (mlx_data.desc->scene[map_y][map_x] == '1' && left == 1 && side)//left-EAST
		{
			// color = DARK_YELLOW;
			texture = mlx_data.t_east;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '1' && left == -1 && side)//right-WEST
		{
			// color = DARK_GREEN;
			texture = mlx_data.t_west;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '1' && top == 1 && !side)//top-NORTH
		{
			// color = RED;
			texture = mlx_data.t_north;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '1' && top == -1 && !side)//bottom-SOUTH
		{
			// color = BLACK;
			texture = mlx_data.t_south;

		}
		else if (mlx_data.desc->scene[map_y][map_x] == '2')
		{
			// color = GREEN;
			texture = mlx_data.t_sprite;
		}
		else
			color = WHITE;
		ft_get_color_tab(color, color_tab);
		j = 0;
		// printf("draw_start = %d, draw_end = %d\n", draw_start, draw_end);
		// 		printf("x = %d, j = %d\n", x, j);

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
			int d = (j+draw_start) * 256 - mlx_data.desc->y * 128 + line_height * 128;
			int texture_y = ((d*64) / line_height) / 256;
			// if (texture.data[texture_y * texture.size_line + texture_x * texture.bpp / 8 + 3] != -1)
			// {
				color_tab[0] = texture.data[texture_y * texture.size_line + texture_x * texture.bpp / 8 + 2];//same for each normalement
				color_tab[1] = texture.data[texture_y * texture.size_line + texture_x * texture.bpp / 8 + 1];
				color_tab[2] = texture.data[texture_y * texture.size_line + texture_x * texture.bpp / 8 + 0];
				ft_put_pixel_to_image(mlx_data, x, draw_start + j, color_tab);
			// }
			j++;
		}
		x++;
	}
}