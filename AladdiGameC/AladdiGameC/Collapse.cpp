#include "Collapse.h"
#include <cstdlib>
#include <ctime>

Collapse::Collapse(Sprite *sprite_collapse, SpriteSheet* spriteSheet)
{
	sprite = sprite_collapse;
	for (int i = 0; i < 4; i++)
	{
		element[i] = new Object();
	}
	spriteSheetCollapse = spriteSheet;
}

Collapse::Collapse()
{
}

Collapse::~Collapse()
{

}

void Collapse::NewCollapse(D3DXVECTOR2 pos, int type)
{
	D3DXVECTOR2 posit;

	switch (type)
	{
	case Collapse::CollapseSkeleton:
		start = 26;
		end = 29;
		posit = D3DXVECTOR2(pos.x + 50, pos.y);
		break;
	default:
		break;
	}

	int r;
	srand(time(NULL));

	//Tạo ngẫu nhiên vận tốc
	for (int i = 0; i < 4; i++)
	{
		// rand() % (b – a + 1) + a
		/*r = rand() % (20 - 0 + 1) + 0;
		float vx = -1 + 0.1 * r;
		float vy = 1 + 0.1 * r;*/
		switch (i)
		{
		case 0:
			element[i]->SetVelocity(D3DXVECTOR2(-1.8, 3.5f));
			this->flipFlag = true;
			break;
		case 1:
			element[i]->SetVelocity(D3DXVECTOR2(1.8, 3.5f));
			this->flipFlag = false;
			break;
		case 2:
			element[i]->SetVelocity(D3DXVECTOR2(-1.8, 1.5f));
			this->flipFlag = true;
			break;
		case 3:
			element[i]->SetVelocity(D3DXVECTOR2(1.5, 1.5f));
			this->flipFlag = false;
			break;
		default:
			break;
		}

		element[i]->SetAllowDraw(true);
		element[i]->SetPosition(posit);
	}

	//Lấy ngẫu nhiên 4 mảnh vỡ
	int indexitem = start;
	int n = 0;
	do {
		listRECT[n] = indexitem;
		indexitem++;
		if (indexitem > end) {
			indexitem = start;
		}
		n++;
	} while (n < 4);
	position = pos;
	SetBound(10, 10);
	allowDraw = true;
}

void Collapse::Update(float dt, Keyboard* key)
{
	if (this->allowDraw) {
		for (int i = 0; i < 4; i++)
		{
			element[i]->Update(dt, key);
			element[i]->SetVelocityY(element[i]->GetVelocity().y - 0.1f);
			if (timecout >= 1.5f) {
				element[i]->SetAllowDraw(false);
				element[i]->SetBound(0, 0);
			}
		}
		timecout += dt;
	}
	

}

//Vẽ
void Collapse::Render(Viewport* view)
{

	
		for (int i = 0; i < 4; i++)
		{
			if (element[i]->GetAllowDraw()) {
				sprite->SetRect(spriteSheetCollapse->GetRect(listRECT[i]));
				sprite->SetPosition(element[i]->GetPosition());
				this->sprite->SetScale(D3DXVECTOR2(1.7f, 1.7f));
				sprite->Render(view);
			}
		
		}



}