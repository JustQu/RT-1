#include "gui.h"
#include "rt.h"

void	draw_titles(t_rt *rt, SDL_Color *color)
{
	SDL_Texture *rt_text;
	SDL_Texture *direction_text;
	SDL_Texture *center_text;
	SDL_Texture *rotate_text;

	rt_text = render_text("RT", "font/Title.ttf",
	*color, FONT_TITLE_SIZE * 2, rt->sdl.render);
	render_texture(rt_text, rt->sdl.render, WIDTH_OFFSET + WIDTH_MENU / 2 - 25, MARGIN);
	direction_text = render_text("Direction", "font/Title.ttf",
	*color, FONT_TITLE_SIZE, rt->sdl.render);
	render_texture(direction_text, rt->sdl.render, WIDTH_OFFSET + MARGIN, 75);
	center_text = render_text("Center", "font/Title.ttf",
	*color, FONT_TITLE_SIZE, rt->sdl.render);
	render_texture(center_text, rt->sdl.render, WIDTH_OFFSET + MARGIN, 145);
	rotate_text = render_text("Rotate", "font/Title.ttf",
	*color, FONT_TITLE_SIZE, rt->sdl.render);
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
	*text_color, FONT_TITLE_SIZE, rt->sdl.render);
	SDL_QueryTexture(x_text, NULL, NULL, &w, &h);
	render_texture(x_text, rt->sdl.render, x, y + 15 - h / 2);
}

void	create_xyz_subtitles(t_rt *rt, int x, int y, char *str, t_colors *color)
{
	SDL_Texture *text;
	int w;
	int h;

	text = render_text(str, "font/Title.ttf",
	color->subtitle_xyz_color, FONT_SUBTITLE_SIZE, rt->sdl.render);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	render_texture(text, rt->sdl.render, x - w - MARGIN / 2, y + 15 - h / 2);
}

void	draw_xyz(t_rt *rt, int y, t_vector *vector, t_colors *color)
{
	int i;
	SDL_Rect	xyz;
	int		offset;

	offset = (WIDTH_MENU - (MARGIN * 4)) / 3;
	xyz.x = WIDTH_OFFSET + MARGIN;
	xyz.y = y;
	xyz.w = xyz.x + offset;
	xyz.h = y + 30;
	i = 0;
	while (i < 3)
	{
		roundedBoxRGBA(rt->sdl.render, xyz.x, xyz.y, xyz.w, xyz.h, 5, color->preground.r, color->preground.g, color->preground.b, 255);
		roundedRectangleRGBA(rt->sdl.render, xyz.x - 1, xyz.y - 1, xyz.w + 1, xyz.h + 1, 5, 217, 217, 217, 255);
		// draw_fill_rect(rt, &xyz, color);
		xyz.x += offset + MARGIN;
		xyz.w += offset + MARGIN;
		i++;
	}
	i = WIDTH_OFFSET + MARGIN;
	create_xyz_subtitles(rt, i + offset, y, "x", color);
	create_xyz_subtitles(rt, i + offset * 2 + MARGIN, y, "y", color);
	create_xyz_subtitles(rt, i + (offset + MARGIN) * 2 + offset, y, "z", color);
	xyz_text(rt, vector->x, &color->xyz_text_color, y, i + MARGIN / 2);
	xyz_text(rt, vector->y, &color->xyz_text_color, y, i + offset + MARGIN + MARGIN / 2);
	xyz_text(rt, vector->z, &color->xyz_text_color, y, i + (offset + MARGIN) * 2 + MARGIN / 2);

}
