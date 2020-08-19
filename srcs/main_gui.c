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

int		main_gui(t_rt *rt)
{
	t_colors color;
	//init rt
	rt->direction.x = 1.23;
	rt->direction.y = 1.02;
	rt->direction.z = 2.093432;

	SDL_Color	border_color;
	SDL_Color	text_color;
	SDL_Rect	background;
	SDL_Rect	color_picker;
	SDL_Rect	button;

	//colorPicker
	SDL_Color	red_color;

	SDL_Rect	border;

	TTF_Init();

	color.preground.r = 255;
	color.preground.g = 255;
	color.preground.b = 255;
	color.preground.a = 0;

	color.title_text_color.r = 128;
	color.title_text_color.g = 128;
	color.title_text_color.b = 128;
	color.title_text_color.a = 0;

	color.border_color.r = 217;
	color.border_color.g = 217;
	color.border_color.b = 217;
	color.border_color.a = 0;

	color.subtitle_xyz_color.r = 36;
	color.subtitle_xyz_color.g = 36;
	color.subtitle_xyz_color.b = 36;
	color.subtitle_xyz_color.a = 0;

	color.xyz_text_color.r = 38;
	color.xyz_text_color.g = 38;
	color.xyz_text_color.b = 38;
	color.xyz_text_color.a = 0;


	button.x = WIDTH_OFFSET + MARGIN;
	button.y = 400;
	button.w = button.x + 70;
	button.h = 400 + 30;

	background.x = WIDTH_OFFSET;
	background.y = 0;
	background.w = WIDTH_MENU;
	background.h = HEIGHT;

	color.background_color.r = 242;
	color.background_color.g = 242;
	color.background_color.b = 242;
	color.background_color.a = 0;

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
	draw_fill_rect(rt, &background, &color.background_color);
	draw_xyz(rt, 100, &rt->direction, &color);
	draw_xyz(rt, 170, &rt->center, &color);
	draw_xyz(rt, 240, &rt->rotate, &color);
	roundedRectangleRGBA(rt->sdl.render, WIDTH_OFFSET, 0, WIDTH, HEIGHT, 5, color.border_color.r, color.border_color.g, color.border_color.b, 255);
	vlineRGBA(rt->sdl.render, WIDTH_OFFSET, 0, HEIGHT, color.border_color.r, color.border_color.g, color.border_color.b, 255);
	draw_titles(rt, &text_color);
	draw_gradient(rt->sdl.render, &color_picker, red_color, border_color);
	draw_button(rt, &button, "Color", &color);
	hlineRGBA(rt->sdl.render, WIDTH_OFFSET + MARGIN,WIDTH - MARGIN, 300, 217, 217, 217, 255);
	return (0);
}
