/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:10:18 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:51:12 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	old_parse_plane(t_env *env)
{
	t_line		*file;

	env->data.pos = default_pos();
	env->data.color = default_color();
	env->data.n = default_n();
	while (env->file->next && (LINENEXT[0] == 't' || LINENEXT[0] == 'c'
				|| LINENEXT[0] == 'r') && !ft_isalpha(LINENEXT[1]))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't' || LINE[0] == 'r')
			trans_rotation(env);
		else if (LINE[0] == 'c')
			env->data.color = get_color_t(env);
	}
	create_plan(env, env->data.pos, env->data.color, env->data.n);
}
