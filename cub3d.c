/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/08 17:36:02 by lhuang           ###   ########.fr       */
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
	// desc->play_pos = malloc(sizeof(t_player_pos));
	desc->play_pos.x = 0.;
	desc->play_pos.y = 0.;
	// desc->pos_x = 0;
	// desc->pos_y = 0;
	// desc->dir_pos = malloc(sizeof(t_dir_pos));
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

	x = 0;
	y = 0;
	j = 0;
	k = 0;
	draw_size = (desc->x/3)/desc->nb_l < (desc->x/3)/desc->nb_col ? (desc->x/3)/desc->nb_l : (desc->x/3)/desc->nb_col;
	draw_size_fixed = draw_size;
	while (j < desc->y)
	{
		k = 0;
		while (k < desc->x)
		{ 
			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, k, j, desc->ceiling_color);
			k++;
		}
		j++;
	}
	j = 0;
	k = 0;
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
						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m, y + l, desc->floor_color);
						m++;
					}
					l++;
				}
			}
			else if(ft_is_player_start(desc->scene[j][k]))
			{
				l = 0;
				// y = j * draw_size_fixed;
				// desc->play_pos.x = k*draw_size_fixed;
				desc->play_pos.x = k;
				// printf("here %f\n", desc->play_pos.y);
				// desc->play_pos.y = j*draw_size_fixed;
				desc->play_pos.y = j;
				// printf("here %f\n", desc->play_pos.y);
				while (y + l < y + draw_size_fixed / 2)
				{
					x = k*draw_size_fixed;
					m = 0;
					// printf("%d, %d, %d, %d, %d\n", y + draw_size_fixed / 2, x + draw_size_fixed / 2,draw_size_fixed / 2, draw_size_fixed, draw_size_fixed/4);
					while (x + m < x + draw_size_fixed / 2)
					{
						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 0);
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
						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m, y + l, desc->ceiling_color);
						m++;
					}
					l++;
				}
			}
			k++;
		}
		j++;
	}
	l = 0;
	y = desc->play_pos.y + 10 * desc->dir_pos.y;
	// desc->dir_pos.y = y;
	// desc->dir_pos.x = desc->play_pos.x + 10 * desc->dir_pos.x;
	while (y + l < y + draw_size_fixed / 2)
	{
		// x = desc->dir_pos.x;
		x = desc->play_pos.x + 10 * desc->dir_pos.x;
		// desc->dir_pos.x = x;
		m = 0;
		// printf("%d, %d, %d, %d, %d\n", y + draw_size_fixed / 2, x + draw_size_fixed / 2,draw_size_fixed / 2, draw_size_fixed, draw_size_fixed/4);
		while (x + m < x + draw_size_fixed / 2)
		{
			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 16711680);
			m++;
		}
		l++;
	}
	return (1);
}

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
// 						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m, y + l, desc->floor_color);
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
// 						mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m, y + l, desc->ceiling_color);
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
// 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 0);
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
// 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, x + m + draw_size_fixed / 4, y + l + draw_size_fixed / 4, 16711680);
// 			m++;
// 		}
// 		l++;
// 	}
// 	return (1);
// }

void ft_draw_walls(t_desc desc, t_mlx_data mlx_data)
{
	//testing draw the walls
	double plane_x;
	double plane_y;
	double camera_x;
	double raydir_x;
	double raydir_y;
	int map_x;
	int map_y;
	double sidedist_x;
	double sidedist_y;
	double deltadist_x;
	double deltadist_y;
	double perpwalldist;
	int step_x;
	int step_y;
	int hit;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
	int color;
	int j;
	int i;

	i = 0;
	j = 0;
	// w = plane_y * 100;
	while (i <= desc.x)
	{
		j = 0;
		plane_x = 0.;
		plane_y = 0.80;
		perpwalldist = 0.;
		step_x = 0;
		step_y = 0;
		hit = 0;
		side = 0;
		camera_x = 2 * i / (double)desc.x - 1;
		// printf("|%f\n", camera_x);
		raydir_x = mlx_data.desc->dir_pos.x + plane_x * camera_x;
		raydir_y = mlx_data.desc->dir_pos.y + plane_y * camera_x;
		// printf("%f\n", raydir_x);
		// printf("%f|\n", raydir_y);
		map_x = (int)mlx_data.desc->play_pos.x;
		map_y = (int)mlx_data.desc->play_pos.y;
		deltadist_x = fabs(1/raydir_x);
		deltadist_y = fabs(1/raydir_y);
		if (raydir_x < 0)
		{
			step_x = -1;
			sidedist_x = (mlx_data.desc->play_pos.x - map_x) * deltadist_x;
			// printf("sidex -1 : %f\n", sidedist_x);
		}
		else
		{
			step_x = 1;
			sidedist_x = (map_x + 1.0 - mlx_data.desc->play_pos.x) * deltadist_x;
			// printf("sidex 1 : %f\n", sidedist_x);
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			sidedist_y = (mlx_data.desc->play_pos.y - map_y) * deltadist_y;
			// printf("sidey -1 : %f\n", sidedist_y);
		}
		else
		{
			step_y = 1;
			sidedist_y = (map_y + 1.0 - mlx_data.desc->play_pos.y) * deltadist_y;
			// printf("sidey 1 : %f\n", sidedist_y);
		}
		hit = 0;
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
			if (mlx_data.desc->scene[map_y][map_x] > '0')
				hit = 1;
			else 
				hit = 0;
		}
		if (side == 0)
			perpwalldist = (map_x - mlx_data.desc->play_pos.x + (1 - step_x) / 2) / raydir_x;
		else
			perpwalldist = (map_y - mlx_data.desc->play_pos.y + (1 - step_y) / 2) / raydir_y;
		printf("||%f\n", perpwalldist);
		line_height = (int)(desc.y / perpwalldist);
		printf("line %d\n", line_height);
		draw_start = -line_height / 2 + desc.y/2;
		// printf("start %d\n", draw_start);
		if(draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + desc.y /2;
		// printf("end %d\n", draw_end);
		if (draw_end >= desc.y)
			draw_end = desc.y - 1;
		if (desc.scene[map_y][map_x] == '1')
			color = RED;
		else if (desc.scene[map_y][map_x] == '2')
			color = GREEN;
		if (side == 1)
			color = color / 2;
		j = 0;
		printf("start %d\n", draw_start);
		printf("end %d\n", draw_end);
		while (j + draw_start < draw_end)
		{
			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.mlx_win, i, j + draw_start, color);
			j++;
		}
		i++;
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
	if (key == 53)
	{
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->mlx_win);
		ft_freer(mlx_data->desc);
		system("leaks Cub3D");
		exit(0);
	}
	else if(key == 123)//arrow left
	{
		play_x = mlx_data->desc->play_pos.x;
		play_y = mlx_data->desc->play_pos.y;
		x = mlx_data->desc->dir_pos.x + play_x;
		y = mlx_data->desc->dir_pos.y + play_y;
		// printf("angle %f\n", mlx_data->desc->dir_pos.angle);
		decalage_x = ((x - play_x) * cos(-0.1)) - ((y - play_y) * sin(-0.1));
		decalage_y = ((x - play_x) * sin(-0.1)) + ((y - play_y) * cos(-0.1));
		// mlx_data->desc->dir_pos.x = decalage_x + play_x;
		// mlx_data->desc->dir_pos.y = decalage_y + play_y;
		mlx_data->desc->dir_pos.x = decalage_x;
		mlx_data->desc->dir_pos.y = decalage_y;
		// printf("%f\n", mlx_data->desc->play_pos.x);
		// printf("%f\n", mlx_data->desc->play_pos.y);
		// printf("%f\n", mlx_data->desc->dir_pos.x);
		// printf("%f\n", mlx_data->desc->dir_pos.y);
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		ft_draw_walls(*(mlx_data->desc), *mlx_data);
	}
	else if(key == 124)//arrow right
	{
		play_x = mlx_data->desc->play_pos.x;
		play_y = mlx_data->desc->play_pos.y;
		x = mlx_data->desc->dir_pos.x + play_x;
		y = mlx_data->desc->dir_pos.y + play_y;
		// printf("angle %f\n", mlx_data->desc->dir_pos.angle);
		decalage_x = ((x - play_x) * cos(0.1)) - ((y - play_y) * sin(0.1));
		decalage_y = ((x - play_x) * sin(0.1)) + ((y - play_y) * cos(0.1));
		// mlx_data->desc->dir_pos.x = decalage_x + play_x;
		// mlx_data->desc->dir_pos.y = decalage_y + play_y;
		mlx_data->desc->dir_pos.x = decalage_x;
		mlx_data->desc->dir_pos.y = decalage_y;
		// printf("%f\n", mlx_data->desc->play_pos.x);
		// printf("%f\n", mlx_data->desc->play_pos.y);
		// printf("%f\n", mlx_data->desc->dir_pos.x);
		// printf("%f\n", mlx_data->desc->dir_pos.y);
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		ft_draw_walls(*(mlx_data->desc), *mlx_data);
	}
	else if (key == 0 || key == 12)//move left
	{
		mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x - 2;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x - 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		ft_draw_walls(*(mlx_data->desc), *mlx_data);
	}
	else if (key == 6 || key == 13)//move up
	{
		mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y - 2;
		mlx_data->desc->dir_pos.y = mlx_data->desc->dir_pos.y - 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		ft_draw_walls(*(mlx_data->desc), *mlx_data);
	}
	else if (key == 1)//down
	{
		mlx_data->desc->play_pos.y = mlx_data->desc->play_pos.y + 2;
		mlx_data->desc->dir_pos.y = mlx_data->desc->dir_pos.y + 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		ft_draw_walls(*(mlx_data->desc), *mlx_data);
	}
	else if (key == 2)//right
	{
		mlx_data->desc->play_pos.x = mlx_data->desc->play_pos.x + 2;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x + 2;
		// ft_redraw_map(mlx_data->desc, *mlx_data);
		ft_draw_walls(*(mlx_data->desc), *mlx_data);
	}
	printf("%d\n", key);
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
	mlx_data.mlx_ptr = mlx_init();
	if ((mlx_data.mlx_win = mlx_new_window(mlx_data.mlx_ptr, desc.x, desc.y, "Cub3D")) == NULL)
	{
		write(1, "error\n", 6);
		return (-1);
	}
	mlx_key_hook(mlx_data.mlx_win, ft_key_pressed, &mlx_data);
	// mlx_mouse_hook(mlx_data.mlx_win, ft_mouse_pressed, (void *)0);
	// mlx_expose_hook(mlx_data.mlx_win, ft_pressed, &mlx_data);
	// mlx_expose_hook(mlx_data.mlx_win, ft_pressed, &mlx_data);
	if ((ft_display_map(&desc, mlx_data)) == -1)
		return (-1);
	ft_print_desc(&desc);
	ft_draw_walls(desc, mlx_data);
	// mlx_string_put(mlx_data.mlx_ptr, mlx_data.mlx_win, 1000, 20, 16777215, "Hello World");
	mlx_loop(mlx_data.mlx_ptr);
	return (1);
}
