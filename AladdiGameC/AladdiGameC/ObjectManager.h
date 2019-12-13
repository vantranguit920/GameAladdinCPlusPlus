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
class ObjectManager
{
protected:
	

	Viewport* viewport;
	Map* map;
	Map* map2;
	Map3D* map3;
	Grid* grid;

	PointMap* point;

	Sound *sound;
	GSound *soundGame;
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

	BonusLevel* bonusLevel;
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
	ObjectManager();
	~ObjectManager();
	void Init(Graphic* graphic, Sound* sound);
	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);
	//Vẽ Object lên màn hình 
	void Render();
	void Start();
	int End();
	void ReadGrid(TiXmlElement *root,Grid *grid);	
};
