#include "MenuGame.h"



MenuGame::MenuGame()
{
}


MenuGame::~MenuGame()
{
}

void MenuGame::Init(Graphic * graphic)
{
	spriteMenu = new Sprite(graphic, "./Resource Files/menu.png", D3DCOLOR_XRGB(163, 73, 164));
	spriteLogo = new Sprite(graphic, "./Resource Files/menu.png", D3DCOLOR_XRGB(255, 0, 255));
	spritePoint = new Sprite(graphic, "./Resource Files/menu.png", D3DCOLOR_XRGB(255, 0, 255));
	spriteComplete = new Sprite(graphic, "./Resource Files/Next.png", D3DCOLOR_XRGB(255, 0, 255));

	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->soundMenu = this->sound->LoadSound("./Sound/MenuSelect_Background.wav");
	this->soundSelect = this->sound->LoadSound("./Sound/MenuSelect_SelectChange.wav");
}

void MenuGame::Update(float dt, Keyboard * key)
{
	sound->LoopSound(soundMenu);
	if (complete) {
		timereturn += dt;
		if (timereturn >= 3.0) {
			complete = false;
			timereturn = 0.0f;
		}
		return;
	}
		
	if (key->IsKeyDown(DIK_RETURN)) {
		nextscene = true;
		sound->StopSound(soundMenu);
	}
	else {
		if (key->IsKeyDown(DIK_UP)) {

			switch (posY)
			{
			case 235:
				posY = 185;
				this->sound->PlaySoundA(soundSelect);
				break;
			default:
				break;
			}

		}
		else if (key->IsKeyDown(DIK_DOWN)) {

			switch (posY)
			{
			case 185:
				posY = 235;
				this->sound->PlaySoundA(soundSelect);
				break;
			default:
				break;
			}

		}
	}
	if (timechange > 0.1) {
		flag = !flag;
		timechange = 0.0f;
	}
	timechange += dt;
}

void MenuGame::Render()
{


	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 320;
	r.bottom = 255;
	this->spriteMenu->SetPosition(D3DXVECTOR2(0, 0));
	this->spriteMenu->SetRect(r);
	this->spriteMenu->SetScale(D3DXVECTOR2(1.6f, 2.0f));
	this->spriteMenu->Render();

	//
	RECT rlg;
	rlg.left = 336;
	rlg.top = 73;
	rlg.right = 600;
	rlg.bottom = 192;
	this->spriteLogo->SetPosition(D3DXVECTOR2(125, 50));
	this->spriteLogo->SetRect(rlg);
	this->spriteLogo->SetScale(D3DXVECTOR2(1.0f, 1.0f));
	this->spriteLogo->Render();
	//
	RECT rpoint;
	rpoint.left = 350;
	rpoint.top = 25;
	rpoint.right = 400;
	rpoint.bottom = 50;
	if (flag) {
		this->spriteLogo->SetPosition(D3DXVECTOR2(125, posY));
	}
	else {
		this->spriteLogo->SetPosition(D3DXVECTOR2(120, posY));
	}

	this->spriteLogo->SetRect(rpoint);
	this->spriteLogo->SetScale(D3DXVECTOR2(1.5f, 1.5f));
	this->spriteLogo->Render();
	//
	if (complete) {
		RECT rcomplete;
		rcomplete.left = 0;
		rcomplete.top = 0;
		rcomplete.right = 320;
		rcomplete.bottom = 216;
		this->spriteComplete->SetPosition(D3DXVECTOR2(0, 0));
		this->spriteComplete->SetRect(rcomplete);
		this->spriteComplete->SetScale(D3DXVECTOR2(1.7f, 2.5f));
		this->spriteComplete->Render();
	}
	
}
