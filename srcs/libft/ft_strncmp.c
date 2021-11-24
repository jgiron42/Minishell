/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:25:47 by ereali            #+#    #+#             */
/*   Updated: 2021/07/27 03:47:21 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	if (s1[i + 1] && s1[i] == '-' && s2[j] == '-')
	{
		i++;
		j++;
	}
	if ((s1[i + 1] && s1[i] == '+'))
		i++;
	while (s1[i + 1] && s1[i] == '0')
		i++;
	while (s1[i] == s2[j] && s1[i] != '\0' && s2[j] != '\0' && i < n)
	{
		i++;
		j++;
	}
	if (i >= n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
