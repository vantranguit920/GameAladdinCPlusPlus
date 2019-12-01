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
	vector <Object*> listWall;
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

	Guard *guard;
	Sprite *spriteGuard;
	SpriteSheet *infoGuard;
	
	pendulum *pendu;
	Sprite *spritePendu;
	SpriteSheet *infoPendu;

	Arrow* arrow;
	Sprite* spriteArrow;
	SpriteSheet* infoArrow;

	Bat *bat;
	Sprite *spriteBat;
	SpriteSheet *infoBat;
	std::unordered_set<Object*> objects;

public:
	ObjectManager();
	~ObjectManager();

	void Init(Graphic* graphic);

	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);

	//Vẽ Object lên màn hình 
	void Render();
	void ReadGrid(TiXmlElement *root,Grid *grid);
	/*void ReadQuadTree(TiXmlElement *root, QuadTree *node, QuadTree *father, int indexNode);*/
};
