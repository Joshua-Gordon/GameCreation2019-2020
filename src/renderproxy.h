#pragma once

#include "util/Texture.h"

class RenderProxy {
	protected:
		int x_off, y_off;

	public:
		RenderProxy() : x_off(0), y_off(0) {}
		RenderProxy(int x, int y) : x_off(x), y_off(y) {}
		RenderProxy(const RenderProxy &r) : x_off(r.x_off), y_off(r.y_off) {}
		RenderProxy(const RenderProxy &r, int x, int y) : x_off(r.x_off + x), y_off(r.y_off + y) {}

		int x() const { return x_off; }
		int y() const { return y_off; }

		void render(Texture &, int = 0, int = 0, SDL_Rect * = NULL) const;
};
