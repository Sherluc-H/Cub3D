/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:48:30 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/07 10:54:16 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		ft_check_description(char *filename, t_desc *desc)
{
	int		fd;
	int		rd;
	char	*b;
	char	*str1;

	if (!(ft_check_file_extension(filename, ".cub")))
		return (0);
	rd = 0;
	if((fd = open(filename, O_RDONLY)) == -1)
		return (0);
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
	// printf("|%s|\n", str1);
	return (1);
}

int		ft_check_args(int argc, char **argv, t_desc *desc)
{
	char *desc_file;

	desc_file = NULL;
	if (argc <= 1 || argc > 3)
	{
		write(2, "Error\n", 6);
		write(2, "Wrong number of argument\n", 25);
		return (0);
	}
	if (argc == 3)
	{
		if (!(ft_strcmp(argv[1], "-save")))
		{
			write(2, "Error\n", 6);
			write(2, "Second argument is wrong\n", 25);
			return (0);
		}
	}
	desc_file = argc == 3 ? argv[2] : argv[1];
	if (!(ft_check_description(desc_file, desc)))
	{
		write(2, "Error\n", 6);
		write(2, "Problem in description file\n", 28);
		return (0);
	}
	return (1);
}
