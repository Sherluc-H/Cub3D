/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:16:26 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/26 14:43:59 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key_pressed(int key, t_mlx_data *mlx_data)
{
	double camera_rot_angle;
	double old_dir_x;
	double old_plane_x;
	double new_play_x = mlx_data->desc->play_pos.x;
	double new_play_y = mlx_data->desc->play_pos.y;

	camera_rot_angle = (M_PI/180) * ROTATION_ANGLE;
	if (key == KEY_ESC)
		ft_exit_hook(mlx_data);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (key == KEY_LEFT)
			camera_rot_angle = -camera_rot_angle;
		old_dir_x = mlx_data->desc->dir_pos.x;
		mlx_data->desc->dir_pos.x = mlx_data->desc->dir_pos.x * cos(camera_rot_angle) - mlx_data->desc->dir_pos.y * sin(camera_rot_angle);
		mlx_data->desc->dir_pos.y = old_dir_x * sin(camera_rot_angle) + mlx_data->desc->dir_pos.y * cos(camera_rot_angle);
		old_plane_x = mlx_data->desc->dir_pos.plane_x;
		mlx_data->desc->dir_pos.plane_x = mlx_data->desc->dir_pos.plane_x * cos(camera_rot_angle) - mlx_data->desc->dir_pos.plane_y * sin(camera_rot_angle);
		mlx_data->desc->dir_pos.plane_y = old_plane_x * sin(camera_rot_angle) + mlx_data->desc->dir_pos.plane_y * cos(camera_rot_angle);
	}
	else if (key == KEY_W || key == KEY_Z)//move up
	{
		if (mlx_data->desc->scene[(int)(float)mlx_data->desc->play_pos.y][(int)(float)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST + MOVE_DIST / 10))] == '0')
		{
			new_play_x =  mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
		if (mlx_data->desc->scene[(int)(float)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * (MOVE_DIST + MOVE_DIST / 10))][(int)(float)(mlx_data->desc->play_pos.x)] == '0')
		{
			new_play_y =  mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
	}
	else if (key == KEY_S)//down
	{
		if (mlx_data->desc->scene[(int)(float)mlx_data->desc->play_pos.y][(int)(float)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST + MOVE_DIST / 10))] == '0')
		{
			new_play_x =  mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
		if (mlx_data->desc->scene[(int)(float)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * (MOVE_DIST + MOVE_DIST / 10))][(int)(float)(mlx_data->desc->play_pos.x)] == '0')
		{
			new_play_y =  mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
	}
	else if (key == KEY_A || key == KEY_Q)//move left
	{
		if (mlx_data->desc->scene[(int)(float)mlx_data->desc->play_pos.y][(int)(float)(mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST + MOVE_DIST / 10))] == '0')
		{
			new_play_x =  mlx_data->desc->play_pos.x + mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
		if (mlx_data->desc->scene[(int)(float)(mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST + MOVE_DIST / 10))][(int)(float)(mlx_data->desc->play_pos.x)] == '0')
		{
			new_play_y =  mlx_data->desc->play_pos.y - mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
	}
	else if (key == KEY_D)//right
	{
		if (mlx_data->desc->scene[(int)(float)mlx_data->desc->play_pos.y][(int)(float)(mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST + MOVE_DIST / 10))] == '0')
		{
			new_play_x =  mlx_data->desc->play_pos.x - mlx_data->desc->dir_pos.y * (MOVE_DIST);
		}
		if (mlx_data->desc->scene[(int)(float)(mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST + MOVE_DIST / 10))][(int)(float)(mlx_data->desc->play_pos.x)] == '0')
		{
			new_play_y =  mlx_data->desc->play_pos.y + mlx_data->desc->dir_pos.x * (MOVE_DIST);
		}
	}
	// printf("x = %f, int x = %d, y = %f, int y = %d|%c|\n", new_play_x, (int)(float)(new_play_x), new_play_y, (int)(float)(new_play_y), mlx_data->desc->scene[(int)(float)(new_play_y)][(int)(float)(new_play_x)]);
	if (fabs((float)new_play_y - (int)(float)new_play_y) < 0.000001 && fabs((float)new_play_x - (int)(float)new_play_x) < 0.000001)
	{
		if (new_play_y < mlx_data->desc->play_pos.y)//monte
		{
			if (mlx_data->desc->scene[(int)(float)(new_play_y) - 1][(int)(float)(new_play_x) - 1] != '0')
			{
				printf("up\n");
				return (0);
			}
		}
		else if (new_play_y > mlx_data->desc->play_pos.y)//descend
		{
			if (mlx_data->desc->scene[(int)(float)(new_play_y)][(int)(float)(new_play_x) - 1] != '0')
			{
				printf("down\n");
				return (0);
			}
		}
		else if (new_play_x > mlx_data->desc->play_pos.x)//droite
		{
			if (mlx_data->desc->scene[(int)(float)(new_play_y) - 1][(int)(float)(new_play_x)] != '0')
			{
				printf("right\n");
				return (0);
			}
		}
		else if (new_play_x < mlx_data->desc->play_pos.x)//gauche
		{
			if (mlx_data->desc->scene[(int)(float)(new_play_y) - 1][(int)(float)(new_play_x) - 1] != '0')
			{
				printf("left\n");
				return (0);
			}
		}
	}
	if (mlx_data->desc->scene[(int)(float)(new_play_y)][(int)(float)(new_play_x)] == '0')
	{
		mlx_data->desc->play_pos.x = new_play_x;
		mlx_data->desc->play_pos.y = new_play_y;
		ft_draw_walls(*mlx_data);
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
		// printf("!x = %f, int x = %d, y = %f, int y = %d|%c|\n", mlx_data->desc->play_pos.x, (int)(float)(mlx_data->desc->play_pos.x), mlx_data->desc->play_pos.y, (int)(float)(mlx_data->desc->play_pos.y), mlx_data->desc->scene[(int)(float)(mlx_data->desc->play_pos.y)][(int)(float)(mlx_data->desc->play_pos.x)]);
	// printf("dir x = %f, int plane x = %f, dir y = %f, int plane y = %f\n", mlx_data->desc->dir_pos.x, mlx_data->desc->dir_pos.plane_x, mlx_data->desc->dir_pos.y, mlx_data->desc->dir_pos.plane_y);
	printf("key pressed = %d\n", key);
	return (0);
}