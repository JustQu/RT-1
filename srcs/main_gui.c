#include "rt.h"
#include "gui.h"
#include <SDL2/SDL_render.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

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
				return NULL;
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

int		main_gui(t_rt *rt)
{
	SDL_Color	border_color;
	SDL_Color	background_color;

	SDL_Rect	background;
	SDL_Rect	border;

	background.x = WIDTH - 299;
	background.y = 2;
	background.w = 299;
	background.h = HEIGHT;

	background_color.r = 0;
	background_color.g = 0;
	background_color.b = 200;
	background_color.a = 0;

	border.x = WIDTH - 300;
	border.y = 1;
	border.w = 300;
	border.h = HEIGHT;

	border_color.r = 0;
	border_color.g = 255;
	border_color.b = 0;
	border_color.a = 0;
	draw_fill_rect(rt, &background, &background_color);
	draw_border(rt, &border, &border_color);
	SDL_Texture *rt_text = render_text("RT", "font/font.ttf",
	border_color, 50, rt->sdl.render);
	render_texture(rt_text, rt->sdl.render, WIDTH - 125, 50);
	return (0);
}
