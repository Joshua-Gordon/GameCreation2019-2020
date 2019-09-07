#pragma once

#include <vector>

#include "renderproxy.h"
#include "globalstate.h"

class Scene {
	protected:
		std::vector<Scene *> children_;
		Scene *parent_;

		void renderChildren(const RenderProxy &, const GlobalState &);

	public:
		Scene() : parent_(NULL) {}
		virtual ~Scene();

		virtual void addChild(Scene *);
		virtual void unlink();

		virtual void render(const RenderProxy &, const GlobalState &);
};
