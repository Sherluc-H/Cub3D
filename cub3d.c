/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/01 19:40:13 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_desc	*ft_init_desc(void)
{
	t_desc *desc;

	if (!(desc = malloc(sizeof(*desc))))
		return (NULL);
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
	return (desc);
}

int		main(int argc, char **argv)
{
	t_desc	*desc;
	void	*mlx_p;
	void	*mlx_win;
	int		j;
	int		k;

	k = 0;
	j = 0;
	mlx_p = NULL;
	desc = NULL;
	if (!(desc = ft_init_desc()))
		return (0);
	printf("y = %d\n", desc->y);
	printf("x = %d\n", desc->x);
	if (!ft_check_args(argc, argv, desc))
		return (0);
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
	j = 0;
	printf("---MAP---\n");
	while (desc->scene[j])
	{
		k = 0;
		while (desc->scene[j][k])
		{
			printf("%c", desc->scene[j][k]);
			k++;
		}
		printf("\n");
		j++;
	}
	printf("---END---\n");
	// mlx_p = mlx_init();
	// mlx_win = mlx_new_window(mlx_p, desc->x, desc->y, "Hello world");
	// mlx_loop(mlx_p);
	system("leaks Cub3D");
	return (1);
}
