/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:27:23 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/03 16:56:55 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_init_tex_data(t_mlx_data *mlx_data)
{
	if (!(mlx_data->tex_north.data = mlx_get_data_addr(mlx_data->
		tex_north.img_ptr, &(mlx_data->tex_north.bpp), &(mlx_data->
			tex_north.size_line), &(mlx_data->tex_north.endian))))
		return (-1);
	if (!(mlx_data->tex_south.data = mlx_get_data_addr(mlx_data->
		tex_south.img_ptr, &(mlx_data->tex_south.bpp), &(mlx_data->
			tex_south.size_line), &(mlx_data->tex_south.endian))))
		return (-1);
	if (!(mlx_data->tex_west.data = mlx_get_data_addr(mlx_data->
		tex_west.img_ptr, &(mlx_data->tex_west.bpp), &(mlx_data->
			tex_west.size_line), &(mlx_data->tex_west.endian))))
		return (-1);
	if (!(mlx_data->tex_east.data = mlx_get_data_addr(mlx_data->
		tex_east.img_ptr, &(mlx_data->tex_east.bpp), &(mlx_data->
			tex_east.size_line), &(mlx_data->tex_east.endian))))
		return (-1);
	if (!(mlx_data->tex_sprite.data = mlx_get_data_addr(mlx_data->
		tex_sprite.img_ptr, &(mlx_data->tex_sprite.bpp), &(mlx_data->
			tex_sprite.size_line), &(mlx_data->tex_sprite.endian))))
		return (-1);
	return (1);
}

int			ft_init_texture(t_mlx_data *mlx_data)
{
	if (!(mlx_data->tex_north.img_ptr = mlx_xpm_file_to_image(mlx_data->
		mlx_ptr, mlx_data->desc->north_path, &(mlx_data->tex_north.width),
			&(mlx_data->tex_north.height))))
		return (-1);
	if (!(mlx_data->tex_south.img_ptr = mlx_xpm_file_to_image(mlx_data->
		mlx_ptr, mlx_data->desc->south_path, &(mlx_data->tex_south.width),
			&(mlx_data->tex_south.height))))
		return (-1);
	if (!(mlx_data->tex_west.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
		mlx_data->desc->west_path, &(mlx_data->tex_west.width),
			&(mlx_data->tex_west.height))))
		return (-1);
	if (!(mlx_data->tex_east.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
		mlx_data->desc->east_path, &(mlx_data->tex_east.width),
			&(mlx_data->tex_east.height))))
		return (-1);
	if (!(mlx_data->tex_sprite.img_ptr = mlx_xpm_file_to_image(mlx_data->
		mlx_ptr, mlx_data->desc->sprite_path, &(mlx_data->tex_sprite.width),
			&(mlx_data->tex_sprite.height))))
		return (-1);
	return (ft_init_tex_data(mlx_data));
}
