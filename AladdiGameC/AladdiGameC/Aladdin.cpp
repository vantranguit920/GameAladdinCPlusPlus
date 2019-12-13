#include "Aladdin.h"



Aladdin::Aladdin()
{

}

Aladdin::Aladdin(Sprite *spAla, SpriteSheet *ifoAla)
{
	tag = Object::Player;
	//pathPNG = "aladdin.png";
	sprite = spAla;
	animAla = new AladdinAnimation(ifoAla);
	stateAla = new AladinState(this);
	position = D3DXVECTOR2(50, 1150);
	SetBound(20, 34);
	velocity = D3DXVECTOR2(0, -2);
	
}

AladinState *Aladdin::getState() {
	return stateAla;
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
	
	}
	if (stateAla->isbleeds()) {
		animAla->damageAnimation();
	}
	if(stateAla->getAttack())
		this->SetBound(150, 30);
	else
		this->SetBound(20, 30);
	stateAla->Update(dt, key);



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
					if (obj->GetName() == "Brick"|| obj->GetTag() == Object::Tag::Ground|| obj->GetTag() == Object::Tag::Wall) {
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
						if (pendu->getIndexAnim()>5&& pendu->getIndexAnim() < 20) {
							position.x += disAla.x * time;
							velocity.x = 0;
							this->stateAla->BleedState(side);
						}
					}else if(obj->GetName() == "Arow") {
						Arrow *arow = (Arrow*)obj;
						if (arow->getIndexAnim() > 3 && arow->getIndexAnim() < 8) {
							position.x += disAla.x * time;
							velocity.x = 0;
							this->stateAla->BleedState(side);
						}
					}else  if (obj->GetName() == "Guard") {
						int a = 1 + 2;
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
						this->stateAla->BleedState(side);
					}
				}
				else if (obj->GetName() == "Arow") {
					Arrow *arow = (Arrow*)obj;
					if (arow->getIndexAnim() > 3 && arow->getIndexAnim() < 8) {
						
						velocity.x = 0;
						this->stateAla->BleedState(side);
					}
				}
				else  if (obj->GetName() == "Guard") {
					int a = 1 + 2;
				}

			}
		}
		
	}
}

void Aladdin::Update(float dt, Keyboard* key) {
	Object::Update(dt, key);
	animAla->SetFlipFlag(GetFlipFlag());
	animAla->Update(dt, key);

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
	
	
	sprite->SetPosition(position);	
	
	sprite->Render(viewport);
	
	
}
Aladdin::~Aladdin()
{
}
