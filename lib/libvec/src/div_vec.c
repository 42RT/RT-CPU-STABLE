/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 03:31:09 by rdieulan          #+#    #+#             */
/*   Updated: 2016/11/23 03:31:10 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

t_vec	div_vec(t_vec v1, float n)
{
	v1.x /= n;
	v1.y /= n;
	v1.z /= n;
	return (v1);
}
