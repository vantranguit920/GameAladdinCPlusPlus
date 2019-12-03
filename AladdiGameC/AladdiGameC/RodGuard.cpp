#include "RodGuard.h"

RodGuard::RodGuard() {}
RodGuard::~RodGuard() {}
RodGuard::RodGuard(Sprite* spRodGuard, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spRodGuard;
	this->aladdin = aladdin;
	this->RodGuardAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = RodGuardState::Attack;

}


void RodGuard::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case RodGuardState::Stand:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 0, 1, false);
		break;
	case RodGuardState::Attack:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 0, 5, false);
		break;
	case RodGuardState::Hitted:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 6, 14, false);
		break;
	case RodGuardState::Died:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 15, 28, false);
		break;
	}
}

void RodGuard::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();

	

	if (timeout >= 0.5f) {
		/*if (this->state == RodGuardState::Attack)
			this->SetState(RodGuardState::Hitted);
		else
			this->SetState(RodGuardState::Attack);*/
		timeout = 0;
	}
	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	RodGuardAnim->Update(dt, key);
}
void RodGuard::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disGuard) {
}
void RodGuard::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			RodGuardAnim->GetRect(),
			RodGuardAnim->GetCenter(),
			RodGuardAnim->GetPosition(),
			RodGuardAnim->GetScale(),
			RodGuardAnim->GetTransform(),
			RodGuardAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		RodGuardAnim->SetIndex(0);
	}
}
void RodGuard::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	RodGuardAnim->SetIndex(0);
}

bool RodGuard::GetAllowDraw() {
	return this->allowDraw;
}
void RodGuard::SetState(RodGuardState gState) {
	this->state = gState;
}
void RodGuard::GetState() {

}