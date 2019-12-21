#include "Apple.h"

Apple::Apple() {}
Apple::~Apple() {

}
Apple::Apple(Sprite* spApple, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spApple;
	this->aladdin = aladdin;
	this->AppleAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = AppleState::Show;
	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->applesound = this->sound->LoadSound("./Sound/Apple Slice.wav");

}


void Apple::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case AppleState::Show:
		AppleAnim->SetFrame(position, flipFlag, 20, 0, 0, true);
		break;

	}
}

void Apple::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	

	if (timeout >= 0.2f) {

		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	AppleAnim->Update(dt, key);
}
void Apple::OnCollision(Object* obj, D3DXVECTOR2 distance) {

	if (Collision::isCollision(this->GetBound(), aladdin->GetBound2())) {
		this->SetAllowDraw(false);
		sound->PlaySoundA(applesound);
		if(aladdin->numapples<99)
			aladdin->numapples++;
	}


	
}
void Apple::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;
*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			AppleAnim->GetRect(),
			AppleAnim->GetCenter(),
			AppleAnim->GetPosition(),
			AppleAnim->GetScale(),
			AppleAnim->GetTransform(),
			AppleAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(0.7f, 0.7f));
		this->sprite->Render(viewport);
	}
		
	/*}
	else {
		this->allowDraw = false;
		AppleAnim->SetIndex(0);
	}*/
}
void Apple::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
}

bool Apple::GetAllowDraw() {
	return this->allowDraw;
}
void Apple::SetState(AppleState gState) {
	this->state = gState;
}
void Apple::GetState() {

}