/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:57:00 by lhuang            #+#    #+#             */
/*   Updated: 2019/11/30 18:15:30 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] != str2[i])
		return (0);
	return (1);
}

int		ft_check_file_extension(char *filename, char *extension)
{
	int i;
	int count;
	int filename_size;
	int extension_size;

	i = 0;
	count = 0;
	filename_size = ft_strlen(filename);
	extension_size = ft_strlen(extension);
	if (filename_size > extension_size)
	{
		while (extension_size - i > 0)
		{
			if (filename[filename_size - i - 1] ==
				extension[extension_size - i - 1])
				count++;
			i++;
		}
		if (count == extension_size)
			return (1);
	}
	return (0);
}

char	*ft_strjoin(char *str1, char *str2, int rd)
{
	int		i;
	int		j;
	int		str1_size;
	char	*str;

	i = 0;
	j = 0;
	str1_size = ft_strlen(str1);
	str = malloc(sizeof(char) * (str1_size + rd + 1));
	while (i < str1_size)
	{
		str[i] = str1[i];
		i++;
	}
	while (j < rd)
	{
		str[i + j] = str2[j];
		j++;
	}
	str[i + j] = '\0';
	free(str1);
	// free(str2);
	return (str);
}

int		ft_is_space(char c)
{
	return (c == ' ');
}

int		ft_is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_is_print(char c)
{
	return (c >= 32 && c <= 126);
}

int		ft_atoi_simple(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (ft_is_number(str[i]))
	{
		nb = nb * 10;
		nb = nb + str[i] - 48;
		i++;
	}
	// printf("nb = %d\n", nb);
	free(str);
	return (nb);
}

int		ft_move_sp(char *str, int *i)
{
	if (ft_is_space(str[*i]))
	{
		while (ft_is_space(str[*i]))
		{
			*i = *i + 1;
		}
	}
	else
		return (0);
	return (1);
}

int		ft_end_identifier(char *str, int *i)
{
	if (ft_is_space(str[*i]) || str[*i] == '\n')
	{
		while (ft_is_space(str[*i]))
			*i = *i + 1;
		if (str[*i] == '\n')
		{
			while (str[*i] == '\n')
				*i = *i + 1;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

int		ft_get_number(char *str, int *i)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	if (ft_is_number(str[*i]))
	{
		j = 0;
		while (ft_is_number(str[*i + j]))
			j++;
		new = malloc(sizeof(char) * (j + 1));
		j = 0;
		while (ft_is_number(str[*i]))
		{
			new[j] = str[*i];
			*i = *i + 1;
			j++;
		}
		new[j] = '\0';
		return (ft_atoi_simple(new));
	}
	else
		return (-1);
}

int		ft_get_path(char *str, int *i, t_desc *desc, int path_id)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	if (ft_is_print(str[*i]))
	{
		j = 0;
		while (ft_is_print(str[*i + j]))
			j++;
		new = malloc(sizeof(char) * (j + 1));
		j = 0;
		while (ft_is_print(str[*i]))
		{
			new[j] = str[*i];
			*i = *i + 1;
			j++;
		}
		new[j] = '\0';
		if (path_id == NORTH)
			desc->north = new;
		else if (path_id == SOUTH)
			desc->south = new;
		else if (path_id == WEST)
			desc->west = new;
		else if (path_id == EAST)
			desc->east = new;
		else if (path_id == SPRITE)
			desc->sprite = new;
		return (1);
	}
	else
		return (0);
}

int		ft_get_identifier(char *str, int *i)
{
	if (str[*i] == 'N' && str[*i + 1] == 'O')
	{
		*i = *i + 2;
		return (NORTH);
	}
	else if (str[*i] == 'S' && str[*i + 1] == 'O')
	{
		*i = *i + 2;
		return (SOUTH);
	}
	else if (str[*i] == 'W' && str[*i + 1] == 'E')
	{
		*i = *i + 2;
		return (WEST);
	}
	else if (str[*i] == 'E' && str[*i + 1] == 'A')
	{
		*i = *i + 2;
		return (EAST);
	}
	else
	{
		*i = *i + 1;
		return (SPRITE);
	}
}

int		ft_check_file_content(char *str, t_desc *desc)
{
	int		i;
	int		j;
	char	*new;
	int		path_id;

	i = 0;
	j = 0;
	new = NULL;
	path_id = 0;
	while (str[i])
	{
		if (str[i] == 'R')
		{
			i++;
			if (!(ft_move_sp(str, &i)))
				return (0);
			if ((desc->x = ft_get_number(str, &i)) == -1)
				return (0);
			if (!(ft_move_sp(str, &i)))
				return (0);
			if ((desc->y = ft_get_number(str, &i)) == -1)
				return (0);
			if (!(ft_end_identifier(str, &i)))
				return (0);
			i--;
		}
		else if ((str[i] == 'N' && str[i + 1] == 'O') ||
			(str[i] == 'S' && str[i + 1] == 'O') ||
			(str[i] == 'W' && str[i + 1] == 'E') ||
			(str[i] == 'E' && str[i + 1] == 'A') ||
			str[i] == 'S')
		{
			path_id = ft_get_identifier(str, &i);
			if (!(ft_move_sp(str, &i)))
				return (0);
			if (!(ft_get_path(str, &i, desc, path_id)))
				return (0);
			if (!(ft_end_identifier(str, &i)))
				return (0);
			i--;
		}
		else if (str[i] == 'F' || str[i] == 'C')
		{
			if (str[i] == 'F')
			{
				i++;
				if (!(ft_move_sp(str, &i)))
					return (0);
				if ((desc->floor_tab[0] = ft_get_number(str, &i)) == -1)
					return (0);
				if (str[i] == ',')
					i++;
				else
					return (0);
				if ((desc->floor_tab[1] = ft_get_number(str, &i)) == -1)
					return (0);
				if (str[i] == ',')
					i++;
				else
					return (0);
				if ((desc->floor_tab[2] = ft_get_number(str, &i)) == -1)
					return (0);
			}
			else
			{
				i++;
				if (!(ft_move_sp(str, &i)))
					return (0);
				if ((desc->ceiling_tab[0] = ft_get_number(str, &i)) == -1)
					return (0);
				if (str[i] == ',')
					i++;
				else
					return (0);
				if ((desc->ceiling_tab[1] = ft_get_number(str, &i)) == -1)
					return (0);
				if (str[i] == ',')
					i++;
				else
					return (0);
				if ((desc->ceiling_tab[2] = ft_get_number(str, &i)) == -1)
					return (0);
			}
			if (!(ft_end_identifier(str, &i)))
				return (0);
			i--;
		}
		// else if (str[i] == '1')
		// {
		// }
		// else
		// 	return (0);
		i++;
	}
	return (1);
}

int		ft_check_description(char *filename, t_desc *desc)
{
	int		fd;
	int		rd;
	char	*b;
	char	*str1;

	if (!(ft_check_file_extension(filename, ".cub")))
		return (0);
	rd = 0;
	fd = open(filename, O_RDONLY);
	str1 = malloc(sizeof(char) * 1);
	str1[0] = '\0';
	b = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((rd = read(fd, b, BUFFER_SIZE)) > 0)
	{
		str1 = ft_strjoin(str1, b, rd);
	}
	free(b);
	if ((!ft_check_file_content(str1, desc)))
		return (0);
	printf("|%s|\n", str1);
	return (1);
}

int		ft_check_args(int argc, char **argv, t_desc *desc)
{
	if (argc <= 1 || argc > 3)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (argc == 3)
	{
		if (!(ft_strcmp(argv[2], "-save")) ||
			!(ft_check_description(argv[1], desc)))
		{
			write(2, "Error\n", 6);
			return (0);
		}
	}
	else if (argc == 2)
	{
		if (!(ft_check_description(argv[1], desc)))
		{
			write(2, "Error\n", 6);
			return (0);
		}
	}
	return (1);
}

t_desc	*ft_init_desc(void)
{
	t_desc *desc;

	if (!(desc = malloc(sizeof(*desc))))
		return (NULL);
	desc->r = NULL;
	desc->x = 0;
	desc->y = 0;
	desc->north = NULL;
	desc->south = NULL;
	desc->west = NULL;
	desc->east = NULL;
	desc->sprite = NULL;
	desc->floor = NULL;
	desc->ceiling = NULL;
	return (desc);
}

int		main(int argc, char **argv)
{
	t_desc	*desc;
	void	*mlx_p;
	void	*mlx_win;

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
	printf("floor color = %d, %d, %d\n", desc->floor_tab[0], desc->floor_tab[1], desc->floor_tab[2]);
	printf("ceiling color = %d, %d, %d\n", desc->ceiling_tab[0], desc->ceiling_tab[1], desc->ceiling_tab[2]);
	mlx_p = mlx_init();
	mlx_win = mlx_new_window(mlx_p, desc->x, desc->y, "Hello world");
	mlx_loop(mlx_p);
	system("leaks Cub3D");
	return (1);
}
