/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:47:36 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:03:07 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	trans_rotation(t_env *env)
{
	t_vec	trans;

	if (LINE[0] == 't')
	{
		trans = get_vector(env);
		env->data.pos = add_vec(env->data.pos, trans);
	}
	else if (LINE[0] == 'r')
	{
		trans = get_vector(env);
		env->data.n = rotvec(env->data.n, trans);
	}
}

void	old_parse_cone(t_env *env)
{
	t_line		*file;

	env->data.pos = default_pos();
	env->data.n = default_n();
	env->data.color = default_color();
	env->data.r = 0.5;
	while (env->file->next && (LINENEXT[0] == 'r' || LINENEXT[0] == 't'
				|| LINENEXT[0] == 'o' || LINENEXT[0] == 'c') &&
			!ft_isalpha(LINENEXT[1]))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't' || LINE[0] == 'r')
			trans_rotation(env);
		else if (LINE[0] == 'c')
			env->data.color = get_color_t(env);
		else if (LINE[0] == 'o')
			env->data.r = ft_atod(LINE);
	}
	create_cone(env, env->data);
}
