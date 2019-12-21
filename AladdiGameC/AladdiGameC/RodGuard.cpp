#include "RodGuard.h"


RodGuard::~RodGuard() {}
RodGuard::RodGuard(Sprite* spRodGuard, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spRodGuard;
	this->aladdin = aladdin;
	this->RodGuardAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	hprod = 6;
	SetBound(20, 50);
	allowDraw = true;
	flipFlag = false;
	this->state = RodGuardState::Stand;

}


void RodGuard::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case RodGuardState::Stand:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 5, 5, true);
		break;
	case RodGuardState::Attack:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 0, 11, true);
		break;
	case RodGuardState::Hitted:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 11, 20, false);
		break;
	case RodGuardState::Died:
		RodGuardAnim->SetFrame(position, flipFlag, 20, 21, 26, false);
		break;
	}
}

void RodGuard::Update(float dt, Keyboard* key) {
	if (!allowDraw)
		return;
	if (aladdin->GetPosition().x - position.x < 0) {
		this->flipFlag = true;

	}
	else {
		this->flipFlag = false;
	}
	if (isbleed) {
		this->state = RodGuardState::Hitted;
		if (this->RodGuardAnim->GetIndex() == 20) {
			isbleed = false;
		}
	}
	else {
		D3DXVECTOR2 posAla = aladdin->GetPosition();
		if (abs(aladdin->GetPosition().x - position.x) < 80 && abs(aladdin->GetPosition().y - position.y) < 50) {

			this->state = RodGuardState::Attack;
			if (RodGuardAnim->GetIndex() == 11) {
				timeattack += dt;
				if (timeattack >= 0.2) {
					aladdin->getState()->BleedState((int)flipFlag, 2);
					timeattack = 0.0f;
				}


			}

		}
		else {
			this->state = RodGuardState::Stand;
		}
	}
	if (hprod < 0) {
		this->state = RodGuardState::Died;
		if (RodGuardAnim->GetIndex() == 26) {
			allowDraw = false;
		}
	}
	ChangeAnimation(key);
	Object::Update(dt, key);
	RodGuardAnim->Update(dt, key);
}
void RodGuard::bleed(int dame) {
	hprod =hprod-dame;
	isbleed = true;
}
void RodGuard::OnCollision(Object* obj, D3DXVECTOR2 distance) {
	if (obj->GetTag() == Object::Tag::Player) {
		Aladdin *ala = (Aladdin*)obj;
		if (ala->getState()->delayComplete) {
			RECT board = this->GetBoard(distance);
			if (Collision::isCollision(board, ala->GetBoundKnif())) {
				if (!Collision::isNested(this->GetBound2(), ala->GetBoundKnif()))
				{
					D3DXVECTOR2 sideCollision;
					float time = Collision::CollisionAABB(this->GetBound2(), ala->GetBoundKnif(), distance, sideCollision);
					if (time < 1.0f) {
						ala->getState()->delayComplete = false;
						bleed(2);
						timeout = 0;
					}
						
				}
				else {
					ala->getState()->delayComplete = false;
					bleed(2);
					timeout = 0;
				}
			}
		}
	}
}
void RodGuard::OnCollision() {
	bleed(2);
}
void RodGuard::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;
*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			RodGuardAnim->GetRect(),
			RodGuardAnim->GetCenter(),
			RodGuardAnim->GetPosition(),
			RodGuardAnim->GetScale(),
			RodGuardAnim->GetTransform(),
			RodGuardAnim->GetAngle());
		if (this->GetFlipFlag()) {
			this->sprite->SetScale(D3DXVECTOR2(-1.0f, 1.0f));
		}
		else {
			this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		}

		this->sprite->Render(viewport);
	}
	
	/*}
	else {
		this->allowDraw = false;
		RodGuardAnim->SetIndex(0);
	}*/
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