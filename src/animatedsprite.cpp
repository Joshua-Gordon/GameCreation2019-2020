#include "animatedsprite.h"

void AnimatedSprite::recomputeClip() {
	if(texture_) {
		clip_.w = texture_->getWidth() / xdivs_;
		clip_.h = texture_->getHeight() / ydivs_;
		clip_.x = frame_ * clip_.w;
		clip_.y = seq_ * clip_.h;
		fprintf(stderr, "AS::rC: rect %d,%d %dx%d\n", clip_.x, clip_.y, clip_.w, clip_.h);
	}
}

void AnimatedSprite::reset() {
	seq_ = 0;
	frame_ = 0;
	maxframe_ = xdivs_;
	idle_ = false;
	period_ = 30;
	lastchange = -1;
}

void AnimatedSprite::render(const RenderProxy &r, const GlobalState &gs) {
	if(!idle_) {
		if(lastchange == -1) lastchange = gs.frames;
		if(gs.frames - lastchange >= period_) {
			lastchange = gs.frames;
			frame_++;
			if(frame_ >= maxframe_) frame_ = 0;
			recomputeClip();
		}
	}
    fprintf(stderr,"AS::render?\n");
	Sprite::render(r, gs);
    fprintf(stderr,"AS::render!\n");
}
