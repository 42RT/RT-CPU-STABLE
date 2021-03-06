/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:48:55 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:50:32 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_line	*ft_new_line(char *line, int size)
{
	t_line	*file;
	int		i;

	i = 0;
	if ((file = (t_line*)malloc(sizeof(*file))) == NULL)
		error(1);
	if ((file->line = ft_strnew(size + 1)) == NULL)
		error(1);
	file->next = NULL;
	while (i < size)
	{
		file->line[i] = line[i];
		++i;
	}
	file->size = size;
	free(line);
	return (file);
}
