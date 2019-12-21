/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:16:26 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/21 20:42:48 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key_pressed(int key, t_mlx_data *mlx_data)
{
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
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
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
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
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
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
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
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
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
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
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
		if ((ft_draw_map(mlx_data->desc, *mlx_data)) == -1)
			return (-1);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
	// printf("x = %f, int x = %d, y = %f, int y = %d|%c|\n", mlx_data->desc->play_pos.x, (int)(mlx_data->desc->play_pos.x), mlx_data->desc->play_pos.y, (int)(mlx_data->desc->play_pos.y), mlx_data->desc->scene[(int)(mlx_data->desc->play_pos.y)][(int)(mlx_data->desc->play_pos.x)]);
	// printf("dir x = %f, int plane x = %f, dir y = %f, int plane y = %f\n", mlx_data->desc->dir_pos.x, mlx_data->desc->dir_pos.plane_x, mlx_data->desc->dir_pos.y, mlx_data->desc->dir_pos.plane_y);
	printf("key pressed = %d\n", key);
	return (0);
}