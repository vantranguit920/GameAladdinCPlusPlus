#include "Aladdin.h"



Aladdin::Aladdin()
{
}

Aladdin::Aladdin(Sprite *spAla, SpriteSheet *ifoAla, Sprite *spApple, SpriteSheet *ifoaple)
{


	tag = Object::Player;
	//pathPNG = "aladdin.png";
	sprite = spAla;
	animAla = new AladdinAnimation(ifoAla);
	this->anim = animAla;
	stateAla = new AladinState(this);
	position = D3DXVECTOR2(50, 150);
	SetBound(20, 50);
	numapples = 20;
	numspend = 10;
	HP = 32;
	velocity = D3DXVECTOR2(0, -2);
	for (int i = 0; i < 3; i++) {
		applethrow[i] = new AppleThrow(spApple, ifoaple);
	}
	numapple = 0;

}

AladinState *Aladdin::getState() {
	return stateAla;
}
void Aladdin::newala()
{
	numapples = 20;
	numspend = 10;
	HP = 32;
	position = D3DXVECTOR2(50, 150);
	this->stateAla->SetState(AladinState::Standing);
}
void Aladdin::ChangeAnimation(float dt, Keyboard* key) {



	stateAla->CheckSide(key);
	switch (stateAla->GetState())
	{
	case AladinState::Standing:
		stateAla->StandState(key);
		animAla->standAnimation();
		break;
	case AladinState::Attack:

		stateAla->AttackState(key);
		animAla->attackAnimation();

		break;
	case AladinState::runattack:

		stateAla->AttackState(key);
		animAla->runAnimation();

		break;
	case AladinState::run:

		stateAla->RunState(key);
		animAla->runAnimation();
		break;
	case AladinState::jum:
		stateAla->jumState(key);
		animAla->jumpAnimation();
		break;
	case AladinState::fall:
		stateAla->fallState(key);
		animAla->fallAnimation();
		break;
	case AladinState::standthrow:
		stateAla->standthrows(key);
		animAla->throwAnimation();
		break;
	case AladinState::verticalJump:
		stateAla->jumState(key);
		animAla->VerticalJumpAnimation();
		break;
	case AladinState::jumAttack:
		stateAla->jumAtackState(key);
		animAla->jumpAttackAnimation();
		break;
	case AladinState::down:
		stateAla->downState(key);
		animAla->downAnimation();
		break;
	case AladinState::downattack:
		stateAla->AttackState(key);
		animAla->dowmAttackAnim();
		break;
	case AladinState::jumpthrow:
		stateAla->jumthrowState(key);
		animAla->jumpthrowAnimation();
		break;
	case AladinState::downthrow:
		stateAla->standthrows(key);
		animAla->downThrow();
		break;
	case AladinState::swing:
		stateAla->swinggostate(key,rope);
		animAla->swingAnim();
		break;
	case AladinState::swinggo:
		stateAla->swinggostate(key, rope);
		animAla->swingGoAnim();
		break;
	case AladinState::swingdown:
		stateAla->swinggostate(key, rope);
		animAla->swingGodown();
		break;
	case AladinState::swingjump:
		stateAla->jumState(key);
		animAla->swingjump();
		break;
	case AladinState::swingattack:
		stateAla->AttackState(key);
		animAla->swingAttack();
		break;
	case AladinState::swingThrow:
		stateAla->standthrows(key);
		animAla->swingThrow();
		break;
	}
	if(stateAla->isswing)
		stateAla->swinggostate(key,rope);
	if (stateAla->isbleeds()) {
		animAla->damageAnimation();
	}
	if (stateAla->isbleedbyboss) {
		animAla->bleddbyboss();
	}

	stateAla->Update(dt, key);



}
RECT Aladdin::GetBoundKnif()
{

	RECT boudKnif;
	if (!this->GetFlipFlag()) {
		boudKnif.left = position.x;
		boudKnif.right = bound.left + 80.0f;
	}
	else
	{
		boudKnif.right = position.x;
		boudKnif.left = bound.right - 80.0f;
	}

	boudKnif.top = position.y + height;
	boudKnif.bottom = position.y;
	return boudKnif;

}
Animation* Aladdin::getAnimAladdin()
{
	return this->animAla;
}
void Aladdin::OnCollision(Object *obj, D3DXVECTOR2 distance, D3DXVECTOR2 disAla) {


	RECT board = this->GetBoard(distance);
	//Nếu other trong vùng di chuyển
	if (Collision::isCollision(board, obj->GetBound()))
	{
		if (!Collision::isNested(GetBound2(), obj->GetBound()))
		{
			//Lấy cạnh va chạm
			D3DXVECTOR2 sideCollision;

			//Lấy thời gian va chạm
			float time = Collision::CollisionAABB(GetBound2(), obj->GetBound(), distance, sideCollision);

			//Bé hơn 1 thì có va chạm
			if (time < 1.0f)
			{
				if (sideCollision.x != 0.0f)
				{
					if (obj->GetTag() == Object::Tag::Wall) {
						position.x += disAla.x * time;
						velocity.x = 0;
					}


				}
				else if (sideCollision.y == -1.0f)	//va chạm trên
				{
					
				}
				else if (sideCollision.y == 1.0f)	//va chạm dưới
				{
					if (obj->GetName() == "Brick" || obj->GetTag() == Object::Tag::Ground || obj->GetTag() == Object::Tag::Wall) {
						if (obj->GetName() == "Brick") {
							Brick *b = (Brick*)obj;
							if (b->getIndexAnim() < 8) {
								position.y += disAla.y * time;
								velocity.y = 0;
							}
						}
						else
						{
							position.y += disAla.y * time;
							velocity.y = 0;
						}
					}
				}

				if (obj->GetTag(obj->GetName()) == Object::Tag::Enemys) {
					int side;
					if (this->position.x < obj->GetPosition().x) {
						side = 1;
					}
					else
					{
						side = -1;
					}
					if (obj->GetName() == "Pendu") {
						pendulum *pendu = (pendulum*)obj;
						if (pendu->getIndexAnim() > 5 && pendu->getIndexAnim() < 20) {
							position.x += disAla.x * time;
							velocity.x = 0;
							this->stateAla->BleedState(side, 1);
						}
					}
					else if (obj->GetName() == "Arow") {
						Arrow *arow = (Arrow*)obj;
						if (arow->getIndexAnim() > 3 && arow->getIndexAnim() < 8) {
							position.x += disAla.x * time;
							velocity.x = 0;
							this->stateAla->BleedState(side,1);
						}
					}
					else  if (obj->GetName() == "Bat") {
						this->stateAla->BleedState(side, 1);
					}

				}
				
			}

		}
		else {
			if (obj->GetTag(obj->GetName()) == Object::Tag::Enemys) {
				int side;
				if (this->position.x < obj->GetPosition().x) {
					side = 1;
				}
				else
				{
					side = -1;
				}
				if (obj->GetName() == "Pendu") {
					pendulum *pendu = (pendulum*)obj;
					if (pendu->getIndexAnim() > 5 && pendu->getIndexAnim() < 20) {

						velocity.x = 0;
						this->stateAla->BleedState(side, 1);
					}
				}
				else if (obj->GetName() == "Arow") {
					Arrow *arow = (Arrow*)obj;
					if (arow->getIndexAnim() > 3 && arow->getIndexAnim() < 8) {

						velocity.x = 0;
						this->stateAla->BleedState(side, 1);
					}
				}
				else  if (obj->GetName() == "Bat") {
					this->stateAla->BleedState(side, 1);
				}
				


				

			}
			else  if (obj->GetName() == "Rope") {
				stateAla->isswing = true;
				this->position.x = obj->GetPosition().x - 3;
				rope = obj;
			}
		}

	}
}

void Aladdin::Update(float dt, Keyboard* key) {
	Object::Update(dt, key);
	animAla->SetFlipFlag(GetFlipFlag());
	animAla->Update(dt, key);
	if (stateAla->getThrow()&&numapples>0) {
		if (animAla->GetIndex() == 42|| animAla->GetIndex() == 114 || animAla->GetIndex() == 72 || animAla->GetIndex() == 180) {
			if (!applethrow[numapple]->GetAllowDraw()) {
				if(!stateAla->isDown)
					applethrow[numapple]->NewApple(D3DXVECTOR2(this->position.x, this->position.y + 50.0f), this->flipFlag);
				else {

					applethrow[numapple]->NewApple(D3DXVECTOR2(this->position.x, this->position.y + 20.0f), this->flipFlag);
				}
				if (this->flipFlag) {
					applethrow[numapple]->SetVelocity(-4, 2);
				}
				else {
					applethrow[numapple]->SetVelocity(4, 2);
				}
				stateAla->setThrow(false);
				numapples--;
				numapple++;
				if (numapple > 2) {
					numapple = 0;
				}
			}
		}
		
	}
	for (int i = 0; i < 3; i++) {
		if (applethrow[i]->GetAllowDraw()) {
			applethrow[i]->Update(dt, key);
		}
	}
}
void Aladdin::Render(Viewport *viewport) {
	sprite->SetData(
		animAla->GetRect(),
		animAla->GetCenter(),
		animAla->GetPosition(),
		animAla->GetScale(),
		animAla->GetTransform(),
		animAla->GetAngle()
	);
	if (GetFlipFlag()) {
		sprite->SetScale(D3DXVECTOR2(-1.2, 1.2));
	}
	else
	{
		sprite->SetScale(D3DXVECTOR2(1.2, 1.2));
	}

	for (int i = 0; i < 3; i++) {
		applethrow[i]->Render(viewport);
	}

	sprite->SetPosition(position);

	sprite->Render(viewport);


}
Aladdin::~Aladdin()
{
}
