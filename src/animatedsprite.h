#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite {
	protected:
		int xdivs_, ydivs_;
		int frame_, maxframe_, period_, seq_, lastchange;
		bool idle_;

		void recomputeClip();

	public:
		AnimatedSprite(): Sprite(), xdivs_(1), ydivs_(1) { reset(); recomputeClip(); }
		AnimatedSprite(Texture *t) : Sprite(t), xdivs_(1), ydivs_(1) { reset(); recomputeClip(); }
		AnimatedSprite(Texture *t, int x, int y) : Sprite(t, x, y), xdivs_(1), ydivs_(1) { reset(); recomputeClip(); }
		AnimatedSprite(Texture *t, int x, int y, int xd, int yd) : Sprite(t, x, y), xdivs_(xd), ydivs_(yd) { reset(); recomputeClip(); }

		int xdivs() const { return xdivs_; }
		void setXdivs(int xd) {
			xdivs_ = xd;
			recomputeClip();
		}
		int ydivs() const { return ydivs_; }
		void setYdivs(int yd) {
			ydivs_ = yd;
			recomputeClip();
		}
		int frame() const { return frame_; }
		void setFrame(int f) { frame_ = f; }
		int maxframe() const { return maxframe_; }
		void setMaxframe(int f) {
			maxframe_ = f;
			if(frame_ > maxframe_) frame_ = 0;
		}
		int period() const { return period_; }
		void setPeriod(int p) { period_ = p; }
		int seq() const { return seq_; }
		void setSeq(int s) {
			seq_ = s;
			recomputeClip();
		}
		bool idle() const { return idle_; }
		void setIdle(bool i) {
			idle_ = i;
			if(idle_) frame_ = 0;
		}

		void reset();

		virtual void render(const RenderProxy &, const GlobalState &);
};
