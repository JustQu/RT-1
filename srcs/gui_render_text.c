#include "gui.h"
#include "rt.h"

SDL_Texture*		render_text(char *message, char *font_file,
		SDL_Color color, int font_size, SDL_Renderer *renderer)
{
	TTF_Font		*font;
	SDL_Surface		*surf;
	SDL_Texture		*texture;

	font = TTF_OpenFont(font_file, font_size);
	if (font == NULL)
		return (NULL);
	surf = TTF_RenderText_Blended(font, message, color);
	if (surf == NULL)
	{
		return (NULL);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL)
	{
		return (NULL);
	}
	// SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return (texture);
}
