#include "Skeleton.h"

Skeleton::Skeleton() {}
Skeleton::~Skeleton() {}
Skeleton::Skeleton(Sprite* spSkeleton, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spSkeleton;
	this->aladdin = aladdin;
	this->SkeletonAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = SkeletonState::Stand;

}


void Skeleton::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case SkeletonState::Stand:
		SkeletonAnim->SetFrame(position, flipFlag, 20, 0, 1, false);
		break;
	case SkeletonState::Attack:
		SkeletonAnim->SetFrame(position, flipFlag, 20, 0, 19, false);
		break;
	case SkeletonState::Died:
		SkeletonAnim->SetFrame(position, flipFlag, 20, 25, 38, false);
		break;
	}
}

void Skeleton::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	
	if (abs(aladdin->GetPosition().x - position.x) < 150 && abs(aladdin->GetPosition().x - position.x) > 50) {
		this->state = SkeletonState::Attack;

	}
	else {
		this->state = SkeletonState::Stand;
	}

	if (timeout >= 0.1f) {
		
		timeout = 0;
	}
	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	SkeletonAnim->Update(dt, key);
}
void Skeleton::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disGuard) {
}
void Skeleton::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			SkeletonAnim->GetRect(),
			SkeletonAnim->GetCenter(),
			SkeletonAnim->GetPosition(),
			SkeletonAnim->GetScale(),
			SkeletonAnim->GetTransform(),
			SkeletonAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		SkeletonAnim->SetIndex(0);
	}
}
void Skeleton::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	SkeletonAnim->SetIndex(0);
}

bool Skeleton::GetAllowDraw() {
	return this->allowDraw;
}
void Skeleton::SetState(SkeletonState gState) {
	this->state = gState;
}
void Skeleton::GetState() {

}