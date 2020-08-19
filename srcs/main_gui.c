#include "rt.h"
#include "gui.h"


#include <stdio.h>

void	render_rect(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

SDL_Texture*		load_texture(char *str, SDL_Renderer *renderer)
{
	SDL_Texture *texture;

	texture = IMG_LoadTexture(renderer, str);
	if (!texture)
	{
		printf("You don't have the power");
	}
	return texture;
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	render_rect(tex, ren, x, y, w, h);
}

void	draw_background(t_rt *rt)
{

	SDL_Texture		*background;

	background = load_texture("images/background.png", rt->sdl.render);
	render_rect(background, rt->sdl.render, WIDTH - 200, 0, 200, HEIGHT);
}

SDL_Texture*		render_text(char *message, char *fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
		TTF_Font *font;
		SDL_Surface *surf;


		font = TTF_OpenFont(fontFile, fontSize);
		if (font == NULL)
				printf("not font");
		surf = TTF_RenderText_Blended(font, message, color);
		if (surf == NULL){
				return NULL;
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (texture == NULL){
				return NULL;
		}
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;
}

void	draw_fill_rect(t_rt *rt, SDL_Rect *background, SDL_Color *color)
{
	SDL_Rect rect;

	SDL_SetRenderDrawColor(rt->sdl.render, color->r, color->g,
							color->b, color->a);
	rect.x = background->x;
	rect.y = background->y;
	rect.w = background->w;
	rect.h = background->h;
    SDL_RenderFillRect(rt->sdl.render, &rect);
}

void	draw_border(t_rt *rt, SDL_Rect *border_rect, SDL_Color *color)
{
	SDL_Rect rect;

	SDL_SetRenderDrawColor(rt->sdl.render, color->r, color->g,
							color->b, color->a);
	rect.x = border_rect->x;
	rect.y = border_rect->y;
	rect.w = border_rect->w;
	rect.h = border_rect->h;
    SDL_RenderDrawRect(rt->sdl.render, &rect);
}

void draw_gradient(SDL_Renderer * renderer,
        const int x, const int y, const int w, const int h,
        const SDL_Color c1, const SDL_Color c2)
{
	int i;
	SDL_Color start;
	SDL_Color end;
	SDL_Rect rect;
    float yt;
	float ys;
	yt = y;
    start.r = c1.r;
    start.g = c1.g;
    start.b = c1.b;
    start.a = c1.a;
	ys = h / COLOR_STEP;
    end.r = (c2.r - c1.r) / COLOR_STEP;
    end.g = (c2.g - c1.g) / COLOR_STEP;
    end.b = (c2.b - c1.b) / COLOR_STEP;
    end.a = (c2.a - c1.a) / COLOR_STEP;
	i = 0;
	while (i < COLOR_STEP)
	{
		// SDL_Rect rect = { x, yt, w, ys + 1 };
		rect.x = x;
		rect.y = yt;
		rect.w = w;
		rect.h = ys + 1;
		SDL_SetRenderDrawColor(renderer, start.r, start.g, start.b, start.a);
		SDL_RenderFillRect(renderer, &rect);
		yt += ys;
        start.r += end.r;
        start.g += end.g;
        start.b += end.b;
        start.a += end.a;
		i++;
	}
}

int		main_gui(t_rt *rt)
{
	//init rt
	rt->direction.x = 1.23;
	rt->direction.y = 1.02;
	rt->direction.z = 2.093432;

	SDL_Color	border_color;
	SDL_Color	background_color;
	SDL_Color	text_color;
	SDL_Rect	background;
	SDL_Rect	color_picker;

	//colorPicker
	SDL_Color	red_color;

	SDL_Rect	border;

	TTF_Init();

	background.x = WIDTH_OFFSET - 1;
	background.y = 1;
	background.w = WIDTH_MENU;
	background.h = HEIGHT;

	background_color.r = 242;
	background_color.g = 242;
	background_color.b = 242;
	background_color.a = 0;

	red_color.r = 255;
	red_color.g = 0;
	red_color.b = 0;
	red_color.a = 0;

	text_color.r = 38;
	text_color.g = 38;
	text_color.b = 38;
	text_color.a = 0;

	border.x = WIDTH_OFFSET;
	border.y = 0;
	border.w = WIDTH_MENU;
	border.h = HEIGHT;

	border_color.r = 255;
	border_color.g = 255;
	border_color.b = 255;
	border_color.a = 0;

	color_picker.x = WIDTH_OFFSET + MARGIN;
	color_picker.y = 500;
	color_picker.w = WIDTH_MENU - MARGIN * 2;
	color_picker.h = 200;
	draw_fill_rect(rt, &background, &background_color);
	draw_xyz(rt, 100, &border_color, &rt->direction, &text_color);
	draw_xyz(rt, 170, &border_color, &rt->center, &text_color);
	draw_xyz(rt, 240, &border_color, &rt->rotate, &text_color);
	draw_border(rt, &border, &border_color);
	draw_titles(rt, &text_color);
	draw_gradient(rt->sdl.render, WIDTH_OFFSET, 500, WIDTH_MENU, 200, red_color, border_color);
	return (0);
}
