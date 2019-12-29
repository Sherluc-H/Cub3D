/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:35:03 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 11:42:13 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
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
	free(str);
	return (nb);
}
