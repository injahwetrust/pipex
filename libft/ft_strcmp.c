/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:36:29 by bvaujour          #+#    #+#             */
/*   Updated: 2023/03/30 09:48:15 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/*#include <string.h>
#include <stdio.h>

int	main()
{
	char *str1 = "cat";
	char *str2 = "cat";

	printf ("%d\n",ft_strcmp(str1, str2));
	printf ("%d\n", strcmp(str1, str2));
}*/
