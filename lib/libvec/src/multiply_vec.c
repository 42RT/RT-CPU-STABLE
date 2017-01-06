/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 03:31:54 by rdieulan          #+#    #+#             */
/*   Updated: 2016/11/23 03:31:55 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

t_vec	multiply_vec(t_vec v, float n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}