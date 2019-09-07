#include "scene.h"

Scene::~Scene() {
	while(children_.size() > 0) {
		(*children_.begin())->unlink();
	}
}

void Scene::addChild(Scene *child) {
	children_.push_back(child);
	child->parent_ = this;
}

void Scene::unlink() {
tryAgain:
	for(auto it = parent_->children_.begin(); it != parent_->children_.end(); it++) {
		if((*it) == this) {
			parent_->children_.erase(it);
			goto tryAgain;
		}
	}
	parent_ = NULL;
}

void Scene::renderChildren(const RenderProxy &r) {
	for(auto it = children_.begin(); it != children_.end(); it++) {
		(*it)->render(r);
	}
}

void Scene::render(const RenderProxy &r) {
	renderChildren(r);
}
