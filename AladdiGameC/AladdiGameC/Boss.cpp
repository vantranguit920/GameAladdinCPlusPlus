#include "Boss.h"

Boss::Boss() {}
Boss::~Boss() {

}
Boss::Boss(Sprite* spBoss, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spBoss;
	this->aladdin = aladdin;
	this->BossAnim = new Animation(info);
	isJra = true;
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	SetBound(60, 90);
	numFire = 0;
	allowDraw = true;
	flipFlag = false;
	for (int i = 0; i < 4; i++) {
		fire[i] = new Fire(spBoss, info, pos, aladdin);
	}
	for (int i = 0; i < 20; i++) {
		star[i] = new Star(spBoss, info, pos, aladdin);
	}
	this->state = BossState::jra;
}


void Boss::ChangeAnimation(Keyboard* key) {

	switch (this->state) {
	case BossState::jra:
		BossAnim->SetFrame(position, flipFlag, 50, 0, 3, true);
		break;
	case BossState::pushStar:
		BossAnim->SetFrame(position, flipFlag, 20, 4, 7, false);
		break;
	case BossState::Snake:
		BossAnim->SetFrame(position, flipFlag, 40, 11, 13, true);
		break;
	case BossState::SnakeFire:
		BossAnim->SetFrame(position, flipFlag, 30, 14, 18, false);
		break;
	case BossState::snakeAppear:
		BossAnim->SetFrame(position, flipFlag, 30, 8, 10, false);
		break;

	}
}

void Boss::Update(float dt, Keyboard* key) {


	if (!allowDraw)
		return;
	if (aladdin->GetPosition().x - position.x < 0) {
		this->flipFlag = true;

	}
	else {
		this->flipFlag = false;
	}

	if (isJra) {
		//update jra
		if (this->state == BossState::jra) {
			if (timePushStar >= 2.0f) {
				timePushStar = 0.0f;
				this->state = BossState::pushStar;
			}
			timePushStar += dt;
		}
		else if (this->state == BossState::pushStar) {
			if (BossAnim->GetIndex() == 7) {
				if (delayStar > 0.3f) {
					if (!star[numStar]->GetAllowDraw()) {
						if (flipFlag) {
							star[numStar]->NewStar(D3DXVECTOR2(940, 240), flipFlag, numStar);
						}
						else {
							star[numStar]->NewStar(D3DXVECTOR2(1060, 240), flipFlag, numStar);
						}

						numStar++;
						if (numStar > 19)
							numStar = 0;
					}
					delayStar = 0.0f;
					if (numStar == 19) {
						this->state = BossState::jra;
					}
				}
				delayStar += dt;
			}
		}

		if (this->hp < 10) {
			isJra = false;
			this->state = BossState::snakeAppear;
		}
		timejra += dt;

	}
	else {
		//updatesnake
		if (this->state == BossState::snakeAppear) {
			if (BossAnim->GetIndex() == 10) {
				this->state = BossState::Snake;
			}
		}
		else if (this->state == BossState::Snake) {
			if (timePushFire <= 0.0f) {
				timePushFire = 2.0f;
				this->state = BossState::SnakeFire;
			}
			timePushFire -= dt;
		}
		else if (this->state == BossState::SnakeFire) {
			if (BossAnim->GetIndex() == 18) {
				if (delayFire > 0.2f) {
					if (!fire[numFire]->GetAllowDraw()) {
						fire[numFire]->NewFire(D3DXVECTOR2(995, 140), flipFlag);
						printf("%d\n", numFire);
						numFire++;
						if (numFire > 3)
							numFire = 0;
					}
					this->state = BossState::Snake;
					delayFire = 0.0f;
				}
				delayFire += dt;
			}
		}
	}



	D3DXVECTOR2 posAla = aladdin->GetPosition();
	ChangeAnimation(key);
	Object::Update(dt, key);
	BossAnim->Update(dt, key);
	if (!isJra) {
		for (int i = 0; i < 4; i++) {
			if (fire[i]->GetAllowDraw()) {
				fire[i]->Update(dt, key);
				if (fire[i]->getAnim()->GetIndex() > 34) {
					if (Collision::isCollision(aladdin->GetBound2(), fire[i]->GetBound2())) {
						aladdin->getState()->BleedState((int)fire[i]->GetFlipFlag(), 2);
					}
				}


			}

		}
		//timePushFire -= dt;
	}
	else {
		for (int i = 0; i < 20; i++) {
			if (star[i]->GetAllowDraw()) {
				star[i]->Update(dt, key);
				if (Collision::isCollision(aladdin->GetBound2(), star[i]->GetBound2())) {
					star[i]->OnCollision();
					aladdin->getState()->BleedState(this->GetFlipFlag());
				}
			}
		}
	}
	if (hp < 0)
		this->allowDraw = false;


}
void Boss::OnCollision(Object* obj, D3DXVECTOR2 distance) {

}
void Boss::OnCollision()
{
	this->hp = hp - 1;
	printf("%d\n", hp);
}
void Boss::Render(Viewport* viewport) {

	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			BossAnim->GetRect(),
			BossAnim->GetCenter(),
			BossAnim->GetPosition(),
			BossAnim->GetScale(),
			BossAnim->GetTransform(),
			BossAnim->GetAngle());
		if (this->GetFlipFlag()) {
			this->sprite->SetScale(D3DXVECTOR2(-1.5, 1.5));
		}
		else {
			this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		}

		this->sprite->Render(viewport);
	}
	if (isJra) {
		for (int i = 0; i < 20; i++) {
			star[i]->Render(viewport);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			fire[i]->Render(viewport);
		}

	}


}
void Boss::SetAllowDraw(bool allow) {
	this->allowDraw = allow;

}

bool Boss::GetAllowDraw() {
	return this->allowDraw;
}
void Boss::SetState(BossState gState) {
	this->state = gState;
}
void Boss::GetState() {

}