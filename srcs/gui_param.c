#include <rt.h>

void	gui_param_get_bmp_n_display(t_gui *gui)
{
	gui_widget_texture_get_bmp(PARAM, "help_black.bmp");
	SDL_SetTextureBlendMode(PARAM->bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(PARAM->bmp, 240);
	gui_widget_display(PARAM);
	gui_widget_draw_outline(PARAM->dest, 5, "purple deep");
	SDL_RenderPresent(gui->img);
}

t_scroll	*gui_param_scroll_init()
{
	t_scroll	*scroll;

	if ((scroll = (t_scroll *)malloc(sizeof(t_scroll))) == NULL)
		error(1);
	scroll->nb_value = 6;
	if ((scroll->value = (char **)malloc(sizeof(char *) * scroll->nb_value))
	== NULL)
		error(1);
	if ((scroll->button = (t_button *)malloc(sizeof(t_button))) == NULL)
		error(1);
	if ((scroll->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
		error(1);
	if ((scroll->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
		error(1);
	scroll->value[0] = "param1";
	scroll->value[1] = "param2";
	scroll->value[2] = "param3";
	scroll->value[3] = "param4";
	scroll->value[4] = "param5";
	scroll->value[5] = "param6";
	scroll->active_value = 0;
	scroll->mod = 0;
	scroll->nature = SCL;
	scroll->surface = NULL;
	scroll->bmp = NULL;
	scroll->button->surface = NULL;
	scroll->button->bmp = NULL;
	scroll->button->action = "scroll";
	return (scroll);
}

void	gui_param_scroll_set(t_scroll *scroll)
{
	t_gui	*gui;

	gui = get_gui();
	scroll->dest.w = DEF->scl_w;
	scroll->dest.h = DEF->scl_h;
	gui_scroll_set_halign(scroll);
	scroll->button->dest.x = scroll->dest.x + scroll->dest.w;
	scroll->button->dest.y = scroll->dest.y;
	scroll->button->dest.w = DEF->scl_h;
	scroll->button->dest.h = DEF->scl_h;
}

void	gui_param_scroll_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->scroll_qt)
	{
		gui_widget_texture_get_bmp(PARAM_SCL, "textbox_white.bmp");
		gui_widget_display(PARAM_SCL);
		gui_widget_draw_in_line(PARAM_SCL->dest, 1, "black");
		gui_scroll_value_write(gui, PARAM_SCL, "black");
		gui_widget_texture_get_bmp(PARAM_SCL_B, "scrollB_jade.bmp");
		gui_widget_display(PARAM_SCL_B);
		gui_widget_draw_in_line(PARAM_SCL_B->dest, 1, "black");
		i++;
	}
}

void	gui_param_text_build(t_gui *gui)
{
	int i;

	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	if (PARAM->button_qt > 0)
	{
		i = 0;
		while (i < PARAM->button_qt)
		{
			gui_widget_write_txt(PARAM->button[i], "white");
			i++;
		}
	}
	if (PARAM->scroll_qt > 0)
	{
		i = 0;
		while (i < PARAM->scroll_qt)
		{
			gui_widget_write_txt(PARAM->scroll[i], "white");
			i++;
		}
	}
	if (PARAM->textbox_qt > 0)
	{
		i = 0;
		while (i < PARAM->textbox_qt)
		{
			gui_widget_write_txt(PARAM->textbox[i], "white");
			i++;
		}
	}
	if (PARAM->checkbox_qt > 0)
	{
		i = 0;
		while (i < PARAM->checkbox_qt)
		{
			gui_widget_write_txt(PARAM->checkbox[i], "white");
			i++;
		}
	}
	/*gui_write_param(gui, "options", GUI_ALIGN_MID, 20);
	gui_write_param(gui, "Resolution", GUI_ALIGN_LEFT, 45);
	gui_write_param(gui, "Anti-aliasing", GUI_ALIGN_LEFT, 70);*/
	TTF_CloseFont(TTF->font);

}

void	gui_param_build(t_gui *gui)
{
	gui_param_scroll_create_all(gui);
	gui_param_checkbox_create_all(gui);
	gui_param_text_build(gui);
}

void	gui_param_open(t_gui *gui)
{
	if (gui->widget_active)
		event_widget_deselect(gui);
	gui->widget_active = PARAM;
	//printf("WIDGET ACTIVE = %d\n", *(int *)WIDGET);
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_build(gui);
	PARAM->active = 1;
}

void	gui_param_close(t_gui *gui)
{
	gui->widget_active = NULL;
	//printf("WIDGET NULL\n");
	PARAM->active = 0;
	gui_main_refresh(gui);
}

void	gui_param_toggle(t_gui *gui)
{
	if (WIDGET == PARAM)
		gui_param_close(gui);
	else
		gui_param_open(gui);
}

void	gui_param_refresh(t_gui *gui)
{
	gui->widget_active = PARAM;
	//printf("WIDGET ACTIVE = %d\n", *(int *)WIDGET);
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_scroll_create_all(gui);
	gui_param_checkbox_create_all(gui);
	gui_param_text_build(gui);
}
