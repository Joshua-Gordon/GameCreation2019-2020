#include "renderproxy.h"

void RenderProxy::render(Texture &t, int gx, int gy, SDL_Rect *src) const {
	t.render(gx + x_off, gy + y_off, src);
}
