/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/27 17:08:51 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_desc(t_desc *desc)
{
	desc->resolution_ok = 0;
	desc->x = 0;
	desc->y = 0;
	desc->to_save = 0;
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
void	ft_freer(t_desc *desc)
{
	int j;

	j = 0;
	free(desc->north_path);
	free(desc->south_path);
	free(desc->west_path);
	free(desc->east_path);
	free(desc->sprite_path);
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
	printf("north = %s\n", desc->north_path);
	printf("south = %s\n", desc->south_path);
	printf("west = %s\n", desc->west_path);
	printf("east = %s\n", desc->east_path);
	printf("sprite = %s\n", desc->sprite_path);
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

// int ft_dec_to_hex(char c)
// {
// 	unsigned char uc;

// 	uc = (unsigned char)c;
// 	if (uc / 16 < 16)
// 	{
// 		return (nb);
// 	}
// }

void ft_screen_bmp(t_mlx_data mlx_data)
{
	int i;
	int l;
	unsigned char tab[mlx_data.desc->x * 4];
	unsigned char h_tab[54];
	int fd;
	int *int_p;

	fd = open("cub3d.bmp", O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
	i = 0;
	while (i < 54)
	{
		h_tab[i] = 0;
		i++;
	}
	h_tab[0] = 0x42;
	h_tab[1] = 0x4d;
	int_p = (int *)(&h_tab[2]);
	*int_p = (54 + mlx_data.desc->x * mlx_data.desc->y * 4);
	h_tab[10] = 0x36;
	h_tab[14] = 0x28;
	int_p = (int *)(&h_tab[18]);
	*int_p = mlx_data.desc->x;
	int_p = (int *)(&h_tab[22]);
	*int_p = mlx_data.desc->y;
	h_tab[26] = 0x01;
	h_tab[28] = mlx_data.main_img_bpp;
	int_p = (int *)(&h_tab[34]);
	*int_p = mlx_data.desc->x * mlx_data.desc->y * 4;
	int_p = (int *)(&h_tab[38]);
	*int_p = mlx_data.desc->x;
	int_p = (int *)(&h_tab[42]);
	*int_p = mlx_data.desc->y;
	write(fd, h_tab, 54);
	i = 0;
	l = 0;
	while (l < mlx_data.desc->y)
	{
		if (i == mlx_data.desc->x * 4)
		{
			write(fd, tab, mlx_data.desc->x * 4);
			i = 0;
			l++;
		}
		tab[i] = mlx_data.main_img_data[mlx_data.main_img_size_line * (mlx_data.desc->y - 1) - (mlx_data.main_img_size_line * l) + i];
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_desc desc;
	t_mlx_data mlx_data;

	ft_init_desc(&desc);
	if (!ft_check_args(argc, argv, &desc))
		return (0);
	system("leaks Cub3D");
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
	mlx_data.main_img_data = mlx_get_data_addr(mlx_data.img_ptr, &mlx_data.main_img_bpp, &mlx_data.main_img_size_line, &mlx_data.main_img_endian);
	if ((ft_init_texture(&mlx_data)) == -1)
		return (-1);
	ft_draw_walls(mlx_data);
	printf("%d\n", mlx_data.main_img_bpp);
	printf("%d\n", mlx_data.main_img_size_line);
	printf("%d\n", mlx_data.main_img_endian);
	if (desc.to_save)
	{
		ft_screen_bmp(mlx_data);
		return (0);
	}
	if ((ft_draw_map(&desc, mlx_data)) == -1)
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
	mlx_hook(mlx_data.win_ptr, 17, 0, ft_exit_hook, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (1);
}
