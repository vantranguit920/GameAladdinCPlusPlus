#include "Score.h"



Score::Score()
{
}

Score::Score(Sprite *sprite, SpriteSheet* spriteSheet,D3DXVECTOR2 pos) {
	this->sprite = sprite;
	postion = pos;
	this->animascore = new Animation(spriteSheet);
	this->animascore->SetFrame(postion, true, 10, 36, 36, false);
}
void Score::changeAnim() {
	switch (scores)
	{
	case 0:
		this->animascore->SetFrame(postion, true, 10, 36, 36, false);
		break;
	case 1:
		this->animascore->SetFrame(postion, true, 10, 37, 37, false);
		break;
	case 2:
		this->animascore->SetFrame(postion, true, 10, 38, 38, false);
		break;
	case 3:
		this->animascore->SetFrame(postion, true, 10, 39, 39, false);
		break;
	case 4:
		this->animascore->SetFrame(postion, true, 10, 40, 40, false);
		break;
	case 5:
		this->animascore->SetFrame(postion, true, 10, 41, 41, false);
		break;
	case 6:
		this->animascore->SetFrame(postion, true, 10, 42, 42, false);
		break;
	case 7:
		this->animascore->SetFrame(postion, true, 10, 43, 43, false);
		break;
	case 8:
		this->animascore->SetFrame(postion, true, 10, 44, 44, false);
		break;
	case 9:
		this->animascore->SetFrame(postion, true, 10, 45, 45, false);
		break;
	default:
		break;
	}
}
void Score::Update(float dt, Keyboard* key, int scorep) {
	scores = scorep;
	changeAnim();
	animascore->Update(dt, key);
}
void Score::render() {
	this->sprite->SetData(animascore->GetRect(),
		animascore->GetCenter(),
		postion,
		animascore->GetScale(),
		animascore->GetTransform(),
		animascore->GetAngle());
	this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
	this->sprite->Render();
}
Score::~Score()
{
}
