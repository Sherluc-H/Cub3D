/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:29:35 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/03 16:46:03 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_put_pixel_to_image(t_mlx_data mlx_data, int x, int y, int color)
{
	int	*p;

	p = (int*)&(mlx_data.main_img_data[y * mlx_data.main_img_size_line +
		x * mlx_data.main_img_bpp / 8 + 0]);
	*p = color;
}

int			ft_get_color_from_texture(t_texture_data texture, int texture_x,
	int texture_y)
{
	int color;

	color = 0;
	color += (unsigned char)texture.data[texture_y * texture.size_line +
		texture_x * texture.bpp / 8 + 2] * 65536;
	color += (unsigned char)texture.data[texture_y * texture.size_line +
		texture_x * texture.bpp / 8 + 1] * 256;
	color += (unsigned char)texture.data[texture_y * texture.size_line +
		texture_x * texture.bpp / 8 + 0];
	return (color);
}

void		ft_draw_wall_loop(t_mlx_data mlx_data, t_draw_wall_data draw_data,
	int x, int j)
{
	int d;

	while (j < draw_data.draw_start_y)
	{
		ft_put_pixel_to_image(mlx_data, x, j, mlx_data.desc->ceiling_color);
		j++;
	}
	j = 0;
	while (draw_data.draw_end_y + j < mlx_data.desc->y)
	{
		ft_put_pixel_to_image(mlx_data, x, draw_data.draw_end_y + j,
			mlx_data.desc->floor_color);
		j++;
	}
	while (draw_data.draw_start_y < draw_data.draw_end_y)
	{
		d = (draw_data.draw_start_y) * 256 - mlx_data.desc->y * 128 +
			draw_data.line_height * 128;
		draw_data.texture_y = ((d * draw_data.texture.height) /
			draw_data.line_height) / 256;
		ft_put_pixel_to_image(mlx_data, x, draw_data.draw_start_y,
			ft_get_color_from_texture(draw_data.texture, draw_data.texture_x,
				draw_data.texture_y));
		draw_data.draw_start_y++;
	}
}

static void	ft_sprite_put_pixel_loop(t_mlx_data mlx_data,
	t_draw_spt_data draw_dt, int y)
{
	int d;

	d = y * 256 - mlx_data.desc->y * 128 + draw_dt.sprite_height * 128;
	draw_dt.texture_y = ((d * draw_dt.texture.height) /
		draw_dt.sprite_height) / 256;
	if (draw_dt.texture.data[draw_dt.texture_y * draw_dt.texture.size_line +
			draw_dt.texture_x * draw_dt.texture.bpp / 8 + 3] != -1)
		ft_put_pixel_to_image(mlx_data, draw_dt.draw_start_x, y,
			ft_get_color_from_texture(draw_dt.texture, draw_dt.texture_x,
				draw_dt.texture_y));
}

void		ft_draw_sprite_loop(t_mlx_data mlx_data, t_draw_spt_data draw_dt,
			double *perp_dist_buffer)
{
	int y;

	while (draw_dt.draw_start_x < draw_dt.draw_end_x)
	{
		draw_dt.texture_x = (int)(256 * (draw_dt.draw_start_x -
			(-draw_dt.sprite_width / 2 + draw_dt.sprite_screen_x)) *
				draw_dt.texture.width / draw_dt.sprite_width) / 256;
		if (draw_dt.transform_y > 0 && draw_dt.draw_start_x > 0 &&
			draw_dt.draw_start_x < mlx_data.desc->x && draw_dt.transform_y <
				perp_dist_buffer[draw_dt.draw_start_x])
		{
			y = draw_dt.draw_start_y;
			while (y < draw_dt.draw_end_y)
			{
				ft_sprite_put_pixel_loop(mlx_data, draw_dt, y);
				y++;
			}
		}
		draw_dt.draw_start_x++;
	}
}
