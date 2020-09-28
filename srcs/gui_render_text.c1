#include "gui.h"
#include "rt.h"

SDL_Texture*		render_text(char *message, char *fontFile,
		SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
		TTF_Font *font;
		SDL_Surface *surf;

		font = TTF_OpenFont(fontFile, fontSize);
		if (font == NULL)
				return (NULL);
		surf = TTF_RenderText_Blended(font, message, color);
		if (surf == NULL){
				return (NULL);
		}
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		if (texture == NULL){
				return (NULL);
		}
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);
		return texture;
}
