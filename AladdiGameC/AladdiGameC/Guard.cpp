#include "Guard.h"

Guard::Guard() {}
Guard::~Guard() {}
Guard::Guard(Sprite* spGuard, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spGuard;
	this->aladdin = aladdin;
	this->GuardAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	this->hpGuard = 6;
	SetBound(60, 70);
	this->angry = 30;
	allowDraw = true;
	flipFlag = false;
	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->soundComon = this->sound->LoadSound("./Sound/Guard Beckon.wav");
	this->soundDie = this->sound->LoadSound("./Sound/Guard's Pants.wav");
	this->state = GuardState::Common;

}


void Guard::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case GuardState::HitByBullets:
		GuardAnim->SetFrame(position, flipFlag, 10, 31, 36, false);
		break;
	case GuardState::Common:
		GuardAnim->SetFrame(position, flipFlag, 20, 9, 13, true);
		break;
	case GuardState::GuillotineKnife:
		GuardAnim->SetFrame(position, flipFlag, 10, 14, 30, true);
		break;
	case GuardState::Died:
		GuardAnim->SetFrame(position, flipFlag, 20, 37, 42, false);
		break;
	case GuardState::stand:
		GuardAnim->SetFrame(position, flipFlag, 20, 0, 8, false);
		break;
	}
}

void Guard::Update(float dt, Keyboard* key) {
	if (!allowDraw)
		return;
	if (aladdin->GetPosition().x - position.x < 0) {
		this->flipFlag = true;

	}
	else {
		this->flipFlag = false;
	}
	if (isbleed&&hpGuard<3) {
		this->state = GuardState::HitByBullets;
		if (GuardAnim->GetIndex() == 36) {
			isbleed = false;
		}
	}
	else
	{
		D3DXVECTOR2 posAla = aladdin->GetPosition();
		if (abs(aladdin->GetPosition().x - position.x) < 100 && abs(aladdin->GetPosition().y - position.y) < 50 && angry>1) {
			
			this->state = GuardState::GuillotineKnife;
			if (GuardAnim->GetIndex() == 30) {
				angry -= 4;
				aladdin->getState()->BleedState((int)flipFlag,2);
				
			}
			else if (GuardAnim->GetIndex() == 24) {
				aladdin->getState()->BleedState((int)flipFlag, 1);
			}
				
		}
		else if(abs(aladdin->GetPosition().x - position.x) < 250 && abs(aladdin->GetPosition().y - position.y) < 50) {
			this->state = GuardState::Common;
			if (GuardAnim->GetIndex() == 13)
			{
				angry++;
				sound->PlaySoundA(soundComon);
			}
				
		}
		else {
			this->state = GuardState::stand;
		}
	}
	if (this->hpGuard < 0) {
		this->state = GuardState::Died;
		timeout = 0;
		sound->PlaySoundA(soundDie);
		if(GuardAnim->GetIndex()==42)
			this->allowDraw = false;
	}

	ChangeAnimation(key);
	Object::Update(dt, key);
	GuardAnim->Update(dt, key);
}
void Guard::bleed(int dame) {
	hpGuard = hpGuard - dame;
	isbleed = true;
	angry=15;
	
}
void Guard::OnCollision(Object* obj, D3DXVECTOR2 distance) {
	if (obj->GetTag() == Object::Tag::Player) {
		Aladdin *ala = (Aladdin*)obj;
		if (ala->getState()->delayComplete) {
			RECT board = this->GetBoard(distance);
			if (Collision::isCollision(board , ala->GetBoundKnif())) {
				
				if (!Collision::isNested(this->GetBound(), ala->GetBoundKnif()))
				{
					D3DXVECTOR2 sideCollision;
					float time = Collision::CollisionAABB(this->GetBound(), ala->GetBoundKnif(), distance, sideCollision);
					if (time < 1.0f)
						bleed(2);
					ala->getState()->delayComplete = false;
				}
				else {
					bleed(2);
					ala->getState()->delayComplete = false;
				}
			}
		}
	}
}
void Guard::OnCollision()
{
	bleed(3);
}
void Guard::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			GuardAnim->GetRect(),
			GuardAnim->GetCenter(),
			GuardAnim->GetPosition(),
			GuardAnim->GetScale(),
			GuardAnim->GetTransform(),
			GuardAnim->GetAngle());
		if (this->GetFlipFlag()) {
			this->sprite->SetScale(D3DXVECTOR2(-1.2f, 1.2f));
		}
		else
		{
			this->sprite->SetScale(D3DXVECTOR2(1.2f, 1.2f));
		}

		this->sprite->Render(viewport);
	}
	
	//}
	/*else {
		this->allowDraw = false;
		GuardAnim->SetIndex(0);
	}*/
}
void Guard::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	GuardAnim->SetIndex(0);
}

bool Guard::GetAllowDraw() {
	return this->allowDraw;
}
void Guard::SetState(GuardState gState) {
	this->state = gState;
}
void Guard::GetState() {

}