/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		rt_exit(t_env *env, t_gui *gui)
{
	SDL_DestroyRenderer(env->img);
	SDL_DestroyWindow(env->win);
	SDL_DestroyRenderer(gui->img);
	SDL_DestroyWindow(gui->win);
	SDL_Quit();
	exit(1);
}

void		event_textbox_edit(t_gui *gui, t_textbox *textbox, char *color)
{
	gui_font_init(gui, "Starjedi", 16);
	gui_write_textbox_value(gui, textbox, color);
	TTF_CloseFont(TTF->font);
}

void		event_textbox_value_force(t_textbox *textbox, char *forced_value)
{
	int i;
	int j;

	i = textbox->maxlen - 1;
	j = ft_strlen(forced_value) - 1;
	printf("[%s] value %s not allowed, forcing to %s\n", textbox->tag, textbox->value, forced_value);
	while (j >= 0)
	{
		textbox->value[i] = forced_value[j];
		j--;
		i--;
	}
	while (i >= 0)
		textbox->value[i--] = ' ';
}

void		event_textbox_value_allowed(t_textbox *textbox)
{
	if (ft_strstr(textbox->tag, "__X") || ft_strstr(textbox->tag, "__Y")
		|| ft_strstr(textbox->tag, "__Z"))
	{
		if (ft_atoi(textbox->value) > GUI_XYZ_MAX)
			event_textbox_value_force(textbox, ft_itoa(GUI_XYZ_MAX));
		if (ft_atoi(textbox->value) < GUI_XYZ_MIN)
			event_textbox_value_force(textbox, ft_itoa(GUI_XYZ_MIN));
	}
	if (ft_strstr(textbox->tag, "__V") || ft_strstr(textbox->tag, "__H"))
	{
		if (ft_atoi(textbox->value) > GUI_VH_MAX)
			event_textbox_value_force(textbox, ft_itoa(GUI_VH_MAX));
		if (ft_atoi(textbox->value) < GUI_VH_MIN)
			event_textbox_value_force(textbox, ft_itoa(GUI_VH_MIN));
	}
	if (ft_strstr(textbox->tag, "__R") || ft_strstr(textbox->tag, "__G")
		|| ft_strstr(textbox->tag, "__B") || ft_strstr(textbox->tag, "__A"))
	{
		if (ft_atoi(textbox->value) > GUI_RGBA_MAX)
			event_textbox_value_force(textbox, ft_itoa(GUI_RGBA_MAX));
		if (ft_atoi(textbox->value) < GUI_RGBA_MIN)
			event_textbox_value_force(textbox, ft_itoa(GUI_RGBA_MIN));
	}
	if (ft_strstr(textbox->tag,"RFR") || ft_strstr(textbox->tag, "RFL"))
	{
		if (ft_atoi(textbox->value) > GUI_INDEX_MAX)
			event_textbox_value_force(textbox, ft_itoa(GUI_INDEX_MAX));
		if (ft_atoi(textbox->value) < GUI_INDEX_MIN)
			event_textbox_value_force(textbox, ft_itoa(GUI_INDEX_MIN));
	}
}

void		event_textbox_deselect(t_gui *gui)
{
	t_textbox *tmp;
	// save value
	tmp = gui->widget_active;
	tmp->edited = 0;
	gui->widget_active = NULL;
	gui_widget_texture_get_bmp(tmp, "textbox_white.bmp");
	gui_widget_display(tmp);
	gui_widget_draw_in_line(tmp->dest, 1, "black");
	event_textbox_value_allowed(tmp);
	event_textbox_edit(gui, tmp, "black");

}

void		event_widget_deselect(t_gui *gui)
{
	if (*(int *)WIDGET == TXB)
		event_textbox_deselect(gui);
	else if (*(int *)WIDGET == SCL)
		gui_scroll_toggle(gui, (t_scroll *)gui->widget_active);

}

void		event_textbox_select(t_gui *gui, t_textbox *textbox)
{
	if (textbox == gui->widget_active)
		event_widget_deselect(gui);
	else
	{
		if (gui->widget_active)
			event_widget_deselect(gui);
		gui->widget_active = textbox;
		gui_widget_texture_get_bmp(textbox, "textbox_black.bmp");
		gui_widget_display(textbox);
		gui_widget_draw_in_line(textbox->dest, 1, "white");
		textbox->vlen = 0;
		event_textbox_edit(gui, gui->widget_active, "white");
	}
}

void		event_textbox_value_rot(t_textbox *textbox, char nb)
{
	int i;
	int reserved;

	if (textbox->maxlen == 3)
		reserved = 0;
	else
		reserved = 1;
	i = textbox->maxlen - 1;
	while (textbox->value[textbox->maxlen - 1] != ' ')
	{
		//printf("rot i : %d\n", i);
		if (i == reserved && textbox->value[i] != ' ')
		{
			//printf("0 isnt free, clearing\n");
			gui_textbox_value_clear(textbox, textbox->maxlen);
			i = textbox->maxlen;
		}
		else if (i > reserved && textbox->value[i - 1] == ' ')
		{
			//printf("swapping %d to %d\n", i, i - 1);
			textbox->value[i - 1] = textbox->value[i];
			//printf("free %d\n", i);
			textbox->value[i] = ' ';
			i += 2;
		}
		i--;
	}
	if (i != textbox->maxlen - 1)
		i--;
	textbox->value[i] = nb;
}

void		event_textbox_backspace(t_textbox *textbox)
{
	int i;
	int reserved;

	if (textbox->maxlen == 3)
		reserved = 0;
	else
		reserved = 1;
	i = textbox->maxlen - 1;
	textbox->value[i] = ' ';
	while (i > reserved)
	{
		textbox->value[i] = textbox->value[i - 1];
		i--;
	}
	textbox->value[reserved] = ' ';
}

void		gui_textbox_switch_select(t_gui *gui, t_textbox *textbox)
{
	int i;

	i = 1;
	if (*(int *)WIDGET == TXB)
		{
		if (textbox->id < BLOCK[textbox->p]->textbox_qt - 1)
			event_textbox_select(gui, BLOCK[textbox->p]->textbox[textbox->id + 1]);
		else
		{
			while ((textbox->p + i) < GUI_CONTAINER_TOTAL_NB)
			{
				if (BLOCK[textbox->p + i]->textbox)
				{
					event_textbox_select(gui, BLOCK[textbox->p + i]->textbox[0]);
					i = GUI_CONTAINER_TOTAL_NB;
				}
				i++;
				if ((textbox->p + i) == GUI_CONTAINER_TOTAL_NB)
					i = -textbox->p;
			}
		}
	}
}

void		event_textbox_insert(SDL_Event event, t_gui *gui, t_textbox *textbox)
{
	int action;

	action = 1;
	if (SCANCODE == 40 || SCANCODE == 88)
	{
		event_widget_deselect(gui);
		action = 0;
	}
	else if (SCANCODE == 43)
	{
		gui_textbox_switch_select(gui, textbox);
		action = 0;
	}
	else if (SCANCODE == 87 && textbox->maxlen > 3)
			textbox->value[0] = ' ';
	else if (SCANCODE == 86 && textbox->maxlen > 3)
			textbox->value[0] = '-';
	else if (SCANCODE == 42)
			event_textbox_backspace(textbox);
	else if (SCANCODE == 76)
			gui_textbox_value_clear(textbox, textbox->maxlen);
	else if ((SCANCODE >= 30 && SCANCODE <= 39)
	|| (SCANCODE >= 89 && SCANCODE <= 98))
	{
		if (textbox->edited == 0)
		{
			gui_textbox_value_clear(textbox, textbox->maxlen);
			textbox->edited = 1;
		}
		if (SCANCODE == 30 || SCANCODE == 89)
			event_textbox_value_rot(textbox, '1');
		if (SCANCODE == 31 || SCANCODE == 90)
			event_textbox_value_rot(textbox, '2');
		if (SCANCODE == 32 || SCANCODE == 91)
			event_textbox_value_rot(textbox, '3');
		if (SCANCODE == 33 || SCANCODE == 92)
			event_textbox_value_rot(textbox, '4');
		if (SCANCODE == 34 || SCANCODE == 93)
			event_textbox_value_rot(textbox, '5');
		if (SCANCODE == 35 || SCANCODE == 94)
			event_textbox_value_rot(textbox, '6');
		if (SCANCODE == 36 || SCANCODE == 95)
			event_textbox_value_rot(textbox, '7');
		if (SCANCODE == 37 || SCANCODE == 96)
			event_textbox_value_rot(textbox, '8');
		if (SCANCODE == 38 || SCANCODE == 97)
			event_textbox_value_rot(textbox, '9');
		if (SCANCODE  == 39 || SCANCODE == 98)
			event_textbox_value_rot(textbox, '0');
	}
	else
		action = 0;
	//printf("new total value = .%s.\n", textbox->value);
	if (action == 1)
	{
		gui_widget_texture_get_bmp(textbox, "textbox_black.bmp");
		gui_widget_display(textbox);
		event_textbox_edit(gui, textbox, "white");
		SDL_RenderPresent(gui->img);
	}
}

void		button_perform_action(t_env *env, t_gui *gui, char *action)
{
	if (WIDGET)
		event_widget_deselect(gui);
	if (ft_strstr(action, "DEL") != NULL)
		return;
	else if (ft_strstr(action, "SAVE") != NULL)
		return;
	else if (ft_strstr(action, "APPLY") != NULL)
		return;
	else if (ft_strstr(action, "PARAM") != NULL)
	{
		if (WIDGET == HELP)
			gui_help_close(gui);
		gui_param_toggle(gui);
	}
	else if (ft_strstr(action, "HELP") != NULL)
	{
		if (WIDGET == PARAM)
			gui_param_close(gui);
		gui_help_toggle(gui);
	}
	else if (ft_strstr(action, "EXIT") != NULL)
		rt_exit(env, gui);
}

int			event_is_button(SDL_Event event, t_env *env, t_gui *gui)
{
	int id;
	int i;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->button == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->button_qt)
			{
				if ((event.button.x >= BUTTON[i]->dest.x) &&
				(event.button.x <= BUTTON[i]->dest.x + BUTTON[i]->dest.w) &&
				(event.button.y >= BUTTON[i]->dest.y) &&
				(event.button.y <= BUTTON[i]->dest.y + BUTTON[i]->dest.h))
				{
					printf("EVENT : BUTTON [%d][%d] -> %s\n", id, i,
						BUTTON[i]->action);
					button_perform_action(env, gui, BUTTON[i]->action);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}

int			event_is_param_scroll(SDL_Event event, t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->scroll_qt)
	{
		if (PARAM_SCL == gui->widget_active)
			return (gui_scroll_value_select(gui, event, PARAM_SCL));
		if ((event.button.x >= PARAM_SCL_B->dest.x) &&
		(event.button.x <= PARAM_SCL_B->dest.x + PARAM_SCL_B->dest.w) &&
		(event.button.y >= PARAM_SCL_B->dest.y) &&
		(event.button.y <= PARAM_SCL_B->dest.y + PARAM_SCL_B->dest.h))
		{
			printf("EVENT : PARAM SCROLL [%d]\n", i);
			gui_scroll_toggle(gui, PARAM_SCL);
			return (1);
		}
		i++;
	}
	return (0);
}

int			event_is_scroll(SDL_Event event, t_gui *gui)
{
	int id;
	int i;

	id = 0;
	if (PARAM && PARAM->active == 1)
		return (event_is_param_scroll(event, gui));
	while (id < GUI_CONTAINER_TOTAL_NB && HELP && HELP->active == 0)
	{
		if (BLOCK[id]->scroll == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->scroll_qt)
			{
				if (SCROLL[i] == gui->widget_active)
					return (gui_scroll_value_select(gui, event, SCROLL[i]));
				if ((event.button.x >= SCROLL_B->dest.x) &&
				(event.button.x <= SCROLL_B->dest.x + SCROLL_B->dest.w) &&
				(event.button.y >= SCROLL_B->dest.y) &&
				(event.button.y <= SCROLL_B->dest.y + SCROLL_B->dest.h))
				{
					printf("EVENT : SCROLL [%d][%d]\n", id, i);
					gui_scroll_toggle(gui, SCROLL[i]);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}

int			event_is_param_checkbox(SDL_Event event, t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->checkbox_qt)
	{
		if ((event.button.x >= PARAM_CBX->dest.x) &&
		(event.button.x <= PARAM_CBX->dest.x + PARAM_CBX->dest.w) &&
		(event.button.y >= PARAM_CBX->dest.y) &&
		(event.button.y <= PARAM_CBX->dest.y + PARAM_CBX->dest.h))
		{
			printf("EVENT : PARAM CHECKBOX [%d]\n", i);
			gui_param_checkbox_toggle(gui, PARAM_CBX);
			return (1);
		}
		i++;
	}
	return (0);

}

int			event_is_checkbox(SDL_Event event, t_gui *gui)
{
	if (PARAM && PARAM->active == 1)
		return(event_is_param_checkbox(event, gui));
	// main window checkbox research to be included here
	return (0);
}

int			event_is_textbox(SDL_Event event, t_gui *gui)
{
	int id;
	int i;

	id = 0;
	if (PARAM && PARAM->active == 1)
		return (0); // a changer si textbox dans param
	while (id < GUI_CONTAINER_TOTAL_NB && HELP && HELP->active == 0)
	{
		if (BLOCK[id]->textbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->textbox_qt)
			{
				if ((event.button.x >= TEXTBOX[i]->dest.x) &&
				(event.button.x <= TEXTBOX[i]->dest.x + TEXTBOX[i]->dest.w) &&
				(event.button.y >= TEXTBOX[i]->dest.y) &&
				(event.button.y <= TEXTBOX[i]->dest.y + TEXTBOX[i]->dest.h))
				{
					printf("EVENT : TEXTBOX [%d][%d]\n", id, i);
					event_textbox_select(gui, TEXTBOX[i]);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}

void		event_scroll_mouse_over(SDL_Event event, t_gui *gui, t_scroll *scroll)
{
	int	motion;

	if ((event.motion.x >= scroll->dest.x) &&
	(event.motion.x <= scroll->dest.x + scroll->dest.w) &&
	(event.motion.y >= scroll->dest.y) &&
	(event.motion.y <= scroll->dest.y + scroll->dest.h))
	{
		motion = (event.motion.y - scroll->dest.y + (scroll->mod * GUI_LIST_STEP)) / GUI_LIST_STEP;
		gui_scroll_write_list(gui, scroll, motion);
	}
}

void		event_scroll_down(t_gui *gui, t_scroll *scroll)
{
	if (scroll->mod < scroll->nb_value - GUI_SCROLL_MAX_SHOWN)
	{
		scroll->mod++;
		gui_widget_texture_get_bmp(scroll, "scroll_white.bmp");
		gui_widget_display(scroll);
		gui_scroll_write_list(gui, scroll, -1);
	}
}

void		event_scroll_up(t_gui *gui, t_scroll *scroll)
{
	if (scroll->mod > 0)
	{
		scroll->mod--;
		gui_widget_texture_get_bmp(scroll, "scroll_white.bmp");
		gui_widget_display(scroll);
		gui_scroll_write_list(gui, scroll, -1);
	}
}

int			event_scroll_mouse_wheel(SDL_Event event, t_gui *gui)
{
	t_scroll	*tmp;
	
	if (WIDGET && *(int *)WIDGET == SCL)
	{
		tmp = WIDGET;
		if (event.wheel.y > 0)
			event_scroll_up(gui, tmp);
		else if (event.wheel.y < 0)
			event_scroll_down(gui, tmp);
		else
			return (0);
		return (1);
	}
	return (0);
}

void		event_mouse_wheel(SDL_Event event, t_gui *gui)
{
	if (!event_scroll_mouse_wheel(event, gui))
		return;
}

void		event_mouse_click(SDL_Event event, t_env *env, t_gui *gui)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (!event_is_scroll(event, gui))
			if (!event_is_checkbox(event, gui))
				if (!event_is_button(event, env, gui))
					if (!event_is_textbox(event, gui))
						if (gui->widget_active)
							event_widget_deselect(gui);
	}
}

static int	event_keydown(SDL_Event event, t_env *env, t_gui *gui)
{
	//printf("EVENT : KEY = %d\n", SCANCODE);
	if (event.key.keysym.sym == SDLK_ESCAPE)
		rt_exit(env, gui);
	if (gui->widget_active)
		event_textbox_insert(event, gui, gui->widget_active);
	return (0);
}

void		event_mouse_motion(SDL_Event event, t_gui *gui)
{
	t_scroll	*tmp;

	if (WIDGET && *(int *)WIDGET == SCL)
	{
		tmp = WIDGET;
		event_scroll_mouse_over(event, gui, tmp);
	}
}

int			event(SDL_Event event, t_env *env)
{
	t_gui *gui;

	gui = get_gui();
	if (event.type == SDL_WINDOWEVENT)
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				rt_exit(env, gui);
	if (event.type == SDL_KEYDOWN)
		event_keydown(event, env, gui);
	else
	{
		if (event.window.windowID == gui->winID)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
				event_mouse_click(event, env, gui);
			if (event.type == SDL_MOUSEWHEEL)
				event_mouse_wheel(event, gui);
			if (event.type == SDL_MOUSEMOTION)
				event_mouse_motion(event, gui);
		}
		SDL_RenderPresent(gui->img);
	}
	return (0);
}
