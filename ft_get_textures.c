/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:27:23 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/28 16:05:21 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_texture(t_mlx_data *mlx_data)
{
	if (!(mlx_data->t_north.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->north_path, &(mlx_data->t_north.width), &(mlx_data->t_north.height))) ||
	!(mlx_data->t_south.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->south_path, &(mlx_data->t_south.width), &(mlx_data->t_south.height))) ||
	!(mlx_data->t_west.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->west_path, &(mlx_data->t_west.width), &(mlx_data->t_west.height))) ||
	!(mlx_data->t_east.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->east_path, &(mlx_data->t_east.width), &(mlx_data->t_east.height))) ||
	!(mlx_data->t_sprite.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, mlx_data->desc->sprite_path, &(mlx_data->t_sprite.width), &(mlx_data->t_sprite.height))))
	{
		perror(strerror(errno));
		return (-1);
	}
	mlx_data->t_north.data = mlx_get_data_addr(mlx_data->t_north.img_ptr, &(mlx_data->t_north.bpp), &(mlx_data->t_north.size_line), &(mlx_data->t_north.endian));
	mlx_data->t_south.data = mlx_get_data_addr(mlx_data->t_south.img_ptr, &(mlx_data->t_south.bpp), &(mlx_data->t_south.size_line), &(mlx_data->t_south.endian));
	mlx_data->t_west.data = mlx_get_data_addr(mlx_data->t_west.img_ptr, &(mlx_data->t_west.bpp), &(mlx_data->t_west.size_line), &(mlx_data->t_west.endian));
	mlx_data->t_east.data = mlx_get_data_addr(mlx_data->t_east.img_ptr, &(mlx_data->t_east.bpp), &(mlx_data->t_east.size_line), &(mlx_data->t_east.endian));
	mlx_data->t_sprite.data = mlx_get_data_addr(mlx_data->t_sprite.img_ptr, &(mlx_data->t_sprite.bpp), &(mlx_data->t_sprite.size_line), &(mlx_data->t_sprite.endian));
	return (1);
}

int	ft_display_texture_top(t_mlx_data mlx_data)
{
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_north.img_ptr, 0, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_south.img_ptr, mlx_data.t_north.width, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_west.img_ptr, mlx_data.t_north.width + mlx_data.t_south.width, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_east.img_ptr, mlx_data.t_north.width + mlx_data.t_south.width + mlx_data.t_west.width, mlx_data.desc->y - 64);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, mlx_data.t_sprite.img_ptr, mlx_data.t_north.width + mlx_data.t_south.width + mlx_data.t_west.width + mlx_data.t_east.width, mlx_data.desc->y - 64);
	return (1);
}
