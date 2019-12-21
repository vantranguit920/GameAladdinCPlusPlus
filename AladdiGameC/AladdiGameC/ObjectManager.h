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
class ObjectManager
{
protected:
	

	Viewport* viewport;
	Map* map;
	Map* map2;
	Map3D* map3;
	Grid* grid;

	PointMap* point;

	
	
	vector <Object*> listObjectCollison;
	vector <Object*> listGround;
	vector <Object*> listWall2;
	vector <Object*> listObject;
	D3DXVECTOR2 prePosView;
	D3DXVECTOR2 prePosAla;
	D3DXVECTOR2 newPosAla;
	
	float timeMap=0;
	
	int timecout = 0;

	Aladdin *aladin;
	Sprite *spriteAladdin;
	SpriteSheet *infoAlddin;

	Lamp* lamp;
	HeadAla *head;
	itemApple* itemapple;
	itemspend* itemspends;
	Sprite *spriteLamp;
	SpriteSheet *infoLamp;

	Sprite *spriteBrick;
	SpriteSheet *infoBrick;

	
	Sprite* spriteRodGuard;
	SpriteSheet* infoRodGuard;

	Sprite *spriteGuard;
	SpriteSheet *infoGuard;
	
	
	Sprite* spriteSpendThese;
	SpriteSheet* infoSpendThese;

	Sprite* spriteSavePosition;
	SpriteSheet* infoSavePosition;

	
	Sprite* spriteBonusLevel;
	SpriteSheet* infoBonusLevel;



	
	Sprite* spriteApple;
	SpriteSheet* infoApple;


	
	Sprite* spriteShop;
	SpriteSheet* infoShop;
	
	Sprite *spritePendu;
	SpriteSheet *infoPendu;

	Arrow* arrow;
	Sprite* spriteArrow;
	SpriteSheet* infoArrow;
	Skeleton* skeleton;
	Sprite* spriteSkeleton;
	SpriteSheet* infoSkeleton;
	
	Sprite *spriteBat;
	SpriteSheet *infoBat;
	std::unordered_set<Object*> objects;

public:
	Sound *sound;
	GSound *soundGame;
	ObjectManager();
	~ObjectManager();
	void Init(Graphic* graphic);
	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);
	Aladdin* getAladdin();
	//Vẽ Object lên màn hình 
	void Render();
	void ReadGrid(TiXmlElement *root,Grid *grid);	
};
