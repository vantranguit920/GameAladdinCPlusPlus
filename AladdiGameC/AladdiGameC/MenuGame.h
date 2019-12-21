#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Sound.h"

class MenuGame
{
protected:
	Sprite* spriteMenu;
	Sprite* spriteLogo;
	Sprite* spritePoint;
	Sprite* spriteComplete;
	Sound *sound;
	int posY = 185;
	GSound *soundMenu;
	GSound *soundSelect;
	bool flag = false;
	float timereturn = 0.0f;
	float timechange = 0.0f;
public:
	MenuGame();
	~MenuGame();
	bool complete = false;
	bool nextscene = false;
	void Init(Graphic* graphic);
	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);
	//Vẽ Object lên màn hình 
	void Render();
};

