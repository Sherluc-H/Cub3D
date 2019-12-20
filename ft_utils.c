/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:35:03 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/20 19:19:41 by lhuang           ###   ########.fr       */
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
	while (str1[i] && str2[i] && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] != str2[i])
		return (0);
	return (1);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	int		str1_size;
	int		str2_size;
	char	*str;

	i = 0;
	j = 0;
	str1_size = ft_strlen(str1);
	str2_size = ft_strlen(str2);
	str = malloc(sizeof(char) * (str1_size + str2_size + 1));
	while (i < str1_size)
	{
		str[i] = str1[i];
		i++;
	}
	while (j < str2_size)
	{
		str[i + j] = str2[j];
		j++;
	}
	str[i + j] = '\0';
	free(str1);
	free(str2);
	return (str);
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
