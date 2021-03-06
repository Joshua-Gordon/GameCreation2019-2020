#pragma once

#include "scene.h"

class Sprite : public Scene {
	protected:
		Texture *texture_;
		SDL_Rect clip_;
		int x_, y_;

	public:
		Sprite() : texture_(NULL), clip_(), x_(0), y_(0) {}
		Sprite(Texture *t) : texture_(t), clip_(), x_(0), y_(0) {}
		Sprite(Texture *t, int x, int y) : texture_(t), clip_(), x_(x), y_(y) {}
		Sprite(Texture *t, SDL_Rect c) : texture_(t), clip_(c), x_(0), y_(0) {}
		Sprite(Texture *t, int x, int y, SDL_Rect c) : texture_(t), clip_(c), x_(x), y_(y) {}

		const Texture *texture() const { return texture_; }
		void setTexture(Texture *t) { texture_ = t; }
		const SDL_Rect *clip() const { return &clip_; }
		void setClip(SDL_Rect c) { clip_ = c; }
		int x() const { return x_; }
		void setX(int x) { x_ = x; }
		int y() const { return y_; }
		void setY(int y) { y_ = y; }

		virtual void render(const RenderProxy &, const GlobalState &);
};
