#include "gui.h"
#include "rt.h"

void	draw_titles(t_rt *rt, SDL_Color *color)
{
	SDL_Texture *rt_text;
	SDL_Texture *direction_text;
	SDL_Texture *center_text;
	SDL_Texture *rotate_text;

	rt_text = render_text("RT", "font/Title.ttf",
	*color, FONT_SIZE * 2, rt->sdl.render);
	render_texture(rt_text, rt->sdl.render, WIDTH_OFFSET + WIDTH_MENU / 2 - 25, MARGIN);
	direction_text = render_text("Direction", "font/Title.ttf",
	*color, FONT_SIZE, rt->sdl.render);
	render_texture(direction_text, rt->sdl.render, WIDTH_OFFSET + MARGIN, 75);
	center_text = render_text("Center", "font/Title.ttf",
	*color, FONT_SIZE, rt->sdl.render);
	render_texture(center_text, rt->sdl.render, WIDTH_OFFSET + MARGIN, 145);
	rotate_text = render_text("Rotate", "font/Title.ttf",
	*color, FONT_SIZE, rt->sdl.render);
	render_texture(rotate_text, rt->sdl.render, WIDTH_OFFSET + MARGIN, 215);
}

void	xyz_text(t_rt *rt, float xyz, SDL_Color *text_color, int y, int x)
{
	SDL_Texture *x_text;
	char str[8];
	int w;
	int h;

	gcvt(xyz, 4, str);
	x_text = render_text(str, "font/Roboto.ttf",
	*text_color, FONT_SIZE, rt->sdl.render);
	SDL_QueryTexture(x_text, NULL, NULL, &w, &h);
	render_texture(x_text, rt->sdl.render, x - w, y);
}

void	draw_xyz(t_rt *rt, int y, SDL_Color *color, t_vector *vector, SDL_Color *text_color)
{
	int i;
	SDL_Rect	xyz;
	int		offset;

	offset = (WIDTH_MENU - (MARGIN * 4)) / 3;
	xyz.x = WIDTH_OFFSET + MARGIN;
	xyz.y = y;
	xyz.w = offset;
	xyz.h = 30;
	i = 0;
	while (i < 3)
	{
		draw_fill_rect(rt, &xyz, color);
		xyz.x += offset + MARGIN;
		i++;
	}
	i = WIDTH_OFFSET + MARGIN;
	xyz_text(rt, vector->x, text_color, y, i + offset);
	xyz_text(rt, vector->y, text_color, y, i + offset * 2 + MARGIN);
	xyz_text(rt, vector->z, text_color, y, i + (offset + MARGIN) * 2 + offset);

}
