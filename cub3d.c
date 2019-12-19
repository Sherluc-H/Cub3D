/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/19 16:19:45 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	desc->play_pos.x = 0.;
	desc->play_pos.y = 0.;
	desc->dir_pos.x = 0.;
	desc->dir_pos.y = 0.;
	// desc->dir_pos.angle = 0;
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
	if (!(mlx_data.mlx_ptr = mlx_init()) || !(mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, desc.x, desc.y, "Cub3D")))
	{
		write(1, "error\n", 6);
		return (-1);
	}
	ft_print_desc(&desc);
	mlx_data.img_ptr = mlx_new_image(mlx_data.mlx_ptr, desc.x, desc.y);
	mlx_data.main_img_data = mlx_get_data_addr(mlx_data.img_ptr, &mlx_data.main_img_bpp, &mlx_data.main_img_size_line, &mlx_data.main_img_endian);
	ft_init_texture(&mlx_data);
	ft_draw_walls(mlx_data);
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
	mlx_hook(mlx_data.win_ptr, 17, 0, ft_exit_hook, &mlx_data);//bouton X pour quitter
	mlx_loop(mlx_data.mlx_ptr);
	return (1);
}
