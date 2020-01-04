/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/04 11:13:59 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_desc(t_desc *desc)
{
	desc->error = 0;
	desc->resolution_ok = 0;
	desc->x = 0;
	desc->y = 0;
	desc->north_path = NULL;
	desc->south_path = NULL;
	desc->west_path = NULL;
	desc->east_path = NULL;
	desc->sprite_path = NULL;
	desc->floor_ok = 0;
	desc->ceiling_ok = 0;
	desc->player_found = 0;
	desc->start_parse_scene = 0;
	desc->scene_str = NULL;
	desc->scene = NULL;
	desc->nb_col = 0;
	desc->nb_l = 0;
	desc->floor_color = 0;
	desc->ceiling_color = 0;
	desc->play_pos.x = 0.;
	desc->play_pos.y = 0.;
	desc->dir_pos.x = 0.;
	desc->dir_pos.y = 0.;
	desc->sprite_tab = NULL;
	desc->nb_sprite = 0;
}

int			ft_exit_hook(t_mlx_data *mlx_data)
{
	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	ft_freer(mlx_data->desc);
	exit(0);
	return (0);
}

static int	ft_init_mlx(t_mlx_data *mlx_data, t_desc desc)
{
	if (!(mlx_data->mlx_ptr = mlx_init()))
		return (-1);
	if (!(mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, desc.x, desc.y,
			"Cub3D")))
		return (-1);
	if (!(mlx_data->img_ptr = mlx_new_image(mlx_data->mlx_ptr, desc.x, desc.y)))
		return (-1);
	if (!(mlx_data->main_img_data = mlx_get_data_addr(mlx_data->img_ptr,
			&mlx_data->main_img_bpp, &mlx_data->main_img_size_line,
				&mlx_data->main_img_endian)))
		return (-1);
	if ((ft_init_texture(mlx_data)) == -1)
		return (-1);
	return (1);
}

int			main(int argc, char **argv)
{
	t_desc		desc;
	t_mlx_data	mlx_data;

	ft_init_desc(&desc);
	desc.to_save = 0;
	mlx_data.desc = &desc;
	mlx_data.map_on = 0;
	if (!ft_check_args(argc, argv, &desc))
		return (ft_show_error(desc.error, &mlx_data));
	if ((ft_init_mlx(&mlx_data, desc)) == -1)
		return (ft_show_error(MLX, &mlx_data));
	if ((ft_draw(mlx_data)) == -1)
		return (ft_show_error(MALLOC, &mlx_data));
	if (desc.to_save)
		return (ft_save(mlx_data));
	mlx_do_key_autorepeaton(mlx_data.mlx_ptr);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr,
		mlx_data.img_ptr, 0, 0);
	mlx_hook(mlx_data.win_ptr, 2, 0, ft_key_pressed, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 17, 0, ft_exit_hook, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (1);
}
