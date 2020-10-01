/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:52:06 by alex              #+#    #+#             */
/*   Updated: 2020/08/25 19:52:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

// public void drawGradient(int x1, int y1, int color1, int x2, int y2, int color2) {
// 	float dx = x1 - x2; //Вспомогательные переменные
// 	float dy = y1 - y2;
// 	float AB = (float) Math.sqrt(dx * dx + dy * dy); //Вычисляется только один раз

// 	//Перебираем все пиксели изображения
// 	for (int y = 0; y < height; y++) {
// 		for (int x = 0; x < width; x++) {
// 			dx = x1 - x;
// 			dy = y1 - y;
// 			float AE2 = dx * dx + dy * dy;
// 			float AE = (float) Math.sqrt(AE2);

// 			dx = x2 - x;
// 			dy = y2 - y;
// 			float EB2 = dx * dx + dy * dy;
// 			float EB = (float) Math.sqrt(EB2);

// 			float p = (AB + AE + EB) / 2f;


// 			float EF = 2 / AB * (float)Math.sqrt(Math.abs(p * (p - AB) *
// 				(p - AE) * (p - EB)))
// 			float EF2 = EF * EF;

// 			float AF = (float) Math.sqrt(Math.abs(AE2 - EF2));
// 			float BF = (float) Math.sqrt(Math.abs(EB2 - EF2));

// 			if (AF + BF - 0.1f > AB) {
// 				//Если пиксель лежит в зеленой или красной зоне
// 				rgb[y * width + x] = AF < BF ? color1 : color2;
// 			} else { //Рассчитываем цвет пикселя
// 				float progress = AF / AB;
// 				//Об методе interpolate речь пойдет дальше
// 				rgb[y * width + x] = interpolate(color1, color2, progress);
// 			}
// 		}
// 	}
// }

void	draw_gradient(SDL_Renderer * renderer,
			SDL_Rect *back_rect, const SDL_Color c1, const SDL_Color c2)
{
	int i;
	SDL_Color start;
	SDL_Color end;
	SDL_Rect rect;
    float yt;
	float ys;

	yt = back_rect->y;
    start.r = c1.r;
    start.g = c1.g;
    start.b = c1.b;
    start.a = c1.a;
	ys = back_rect->h / COLOR_STEP;
    end.r = (c2.r - c1.r) / COLOR_STEP;
    end.g = (c2.g - c1.g) / COLOR_STEP;
    end.b = (c2.b - c1.b) / COLOR_STEP;
    end.a = (c2.a - c1.a) / COLOR_STEP;
	i = 0;
	while (i < COLOR_STEP)
	{
		rect.x = back_rect->x;
		rect.y = yt;
		rect.w = back_rect->w;
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
