#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "ObjectManager.h"
#include "Sound.h"
#include "Define.h"
#include "SpriteSheet.h"

using namespace Define;

class Scene
{
protected:
	Sprite* sprite;
	SpriteSheet* infoScene;
	Animation* MenuAnimation;
	D3DXVECTOR2 positionMenu;
	float timedelay;

	//Sound
	Sound* sound;

	GSound* soundTitle;
	GSound* soundEnd;

	ObjectManager* objManager;
public:

	enum Scenestage
	{
		Start,
		Play,
		End
	} SceneStage;
	Scene();
	~Scene();

	//Load Data Game
	void Init(Graphic* graphic);

	//Update Game sau khoảng thời gian gameTime
	void Update(float gameTime, Keyboard* key);

	//Vẽ Object lên màn hình
	void Render();
};

