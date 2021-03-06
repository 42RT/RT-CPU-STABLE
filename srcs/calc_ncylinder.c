/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ncylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:25:33 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:49:38 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec	calc_ncylinder(t_ray *ray, t_obj *obj)
{
	t_vec	n;
	float	m;
	t_vec	x;

	x = calc_vec(obj->vec1, ray->pos);
	m = dot(VDIR, obj->vec2) * RDIST + dot(x, obj->vec2);
	n.x = (VDIR.x * RDIST + ray->pos.x) - obj->vec1.x - obj->vec2.x * m;
	n.y = (VDIR.y * RDIST + ray->pos.y) - obj->vec1.y - obj->vec2.y * m;
	n.z = (VDIR.z * RDIST + ray->pos.z) - obj->vec1.z - obj->vec2.z * m;
	return (n);
}
