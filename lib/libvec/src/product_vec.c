/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product_vec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 03:32:11 by rdieulan          #+#    #+#             */
/*   Updated: 2016/11/23 03:32:45 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

t_vec	product_vec(t_vec v1, t_vec v2)
{
	t_vec v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}
