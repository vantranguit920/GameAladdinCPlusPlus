#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "Text.h"
#include "Viewport.h"
#include "Map.h"
#include "Sound.h"
#include "Aladdin.h"
#include "Brick.h"
#include "pendulum.h"
#include "Arrow.h"
#include "Bat.h"
#include "Grid.h"
#include "Map3D.h"
#include "PointMap.h"
#include "Guard.h"
#include "Skeleton.h"
#include "RodGuard.h"
#include "Shop.h"
#include "SpendThese.h"
#include "SavePosition.h"
#include "BonusLevel.h"
#include "Apple.h"
#include "Lamp.h"
#include "HeadAla.h"
#include "itemApple.h"
#include "itemspend.h"
#include "Boss.h"
#include "Fire.h"
class SceneBoss
{
protected:
	Sound *sound;

	GSound *soundGame;
	vector <Object*> listObjectCollison;
	vector <Object*> listGround;
	vector <Object*> listWall2;
	vector <Object*> listObject;
	Viewport* viewport;
	Boss* boss;
	Sprite* spBoss;
	SpriteSheet* infoBoss;
	Map* map;
	bool isFirt = true;
	Map3D* map3;
	PointMap* point;
	D3DXVECTOR2 prePosView;
	D3DXVECTOR2 prePosAla;
	D3DXVECTOR2 newPosAla;
	Aladdin *aladin;
	Grid* grid;
	Lamp* lamp;
	HeadAla *head;
	itemApple* itemapple;
	itemspend* itemspends;
	Sprite *spriteLamp;
	SpriteSheet *infoLamp;
public:
	SceneBoss();
	~SceneBoss();
	bool gamecomplete = false;
	void Init(Graphic* graphic, Aladdin* ala);
	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);
	void stopSound();
	//Vẽ Object lên màn hình 
	void Render();
	void ReadGrid(TiXmlElement *root, Grid *grid);
};

