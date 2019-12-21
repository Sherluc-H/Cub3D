/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:29:35 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/21 19:28:12 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_data.main_img_data[y * mlx_data.main_img_size_line + x * mlx_data.main_img_bpp / 8 + 2] = r;
	mlx_data.main_img_data[y * mlx_data.main_img_size_line + x * mlx_data.main_img_bpp / 8 + 1] = g;
	mlx_data.main_img_data[y * mlx_data.main_img_size_line + x * mlx_data.main_img_bpp / 8 + 0] = b;
	// if (y == 0)
	// {
	// printf("->%d, %d, %d | %d, %d, %d\n", y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 0, y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 1, y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 2, r, g, b);
	// }
	// else if (y == mlx_data.desc->y - 1)
	// {
	// printf("->%d, %d, %d | %d, %d, %d\n", y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 0, y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 1, y * mlx_data.main_image.size_line + x * mlx_data.main_image.bits_per_pixel / 8 + 2, r, g, b);
	// }
}