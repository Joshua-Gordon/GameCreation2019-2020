#include "sprite.h"

void Sprite::render(const RenderProxy &r) {
	RenderProxy transformed(r, x_, y_);
	if(texture_) {
		SDL_Rect *src = NULL;
		if(clip_.w && clip_.h) src = &clip_;
		transformed.render(*texture_, 0, 0, src);
	}
	renderChildren(transformed);
}
