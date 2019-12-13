#include "Scene.h"


Scene::Scene()
{
	SceneStage = Start;
}


Scene::~Scene()
{
	delete objManager;
}

void Scene::Init(Graphic* graphic)
{
	//sound
	sound = new Sound(graphic->GetHwnd());
	sound->Init_DirectSound();

	/*soundTitle = sound->LoadSound("./Sound/MenuSelect_Background.wav");
	soundEnd = sound->LoadSound("./Sound/LevelComplete.wav");
	*/

	//tạo ảnh Menu
	sprite = new Sprite(graphic, "./Resource Files/Scene.png", D3DCOLOR_XRGB(163, 73, 164));
	infoScene = new SpriteSheet("./Resource Files/Scene.xml");

	MenuAnimation = new Animation(infoScene);
	positionMenu = D3DXVECTOR2(0, 0);
	sprite->SetPosition(positionMenu);
	timedelay = 0.0f;

	//Tạo GamePlay
	objManager = new ObjectManager();
	objManager->Init(graphic, sound);
	//sound->LoopSound(soundTitle);
}


void Scene::Update(float gameTime, Keyboard* key)
{
	switch (SceneStage)
	{
		//Màn hình khởi động
	case Scene::Start:
	{
		timedelay += gameTime;

		
		MenuAnimation->SetFrame(positionMenu, false, 50, 51, 53);

		if (key->IsKeyDown(DIK_RETURN) && timedelay >= 0.25f)
		{
			//objManager->Start();
			SceneStage = Play;
			timedelay = 0.0f;
		}

		//Update
		MenuAnimation->Update(gameTime, key);
		break;
	}
	case Scene::Play:
	{

		objManager->Update(gameTime, key);
		timedelay += gameTime;
		if (key->IsKeyDown(DIK_RETURN) && timedelay >= 0.5f)
		{
			
			SceneStage = End;
			//timedelay = 0.0f;
		}

		//Update
		
		break;
	}
	case Scene::End:
	{
		timedelay += gameTime;

		if (timedelay >= 60.0f) {
			timedelay = 0.0f;
		}

		if (timedelay >= 0.0f && timedelay <= 6.0f) {
			MenuAnimation->SetFrame(positionMenu, false, 15, 0, 37);
		}
		else if (timedelay >= 6.0f && timedelay <= 25.7f) {
			MenuAnimation->SetFrame(positionMenu, false, 200, 38, 49);
		}
		else 
		if(timedelay > 25.7f)
		{
			MenuAnimation->SetFrame(positionMenu, false, 1000, 50, 50);
		}

		MenuAnimation->Update(gameTime, key);
		break;
	}
	default:
		break;
	}

}

//Vẽ Object lên màn hình
void Scene::Render()
{
	if (SceneStage == Play)
		objManager->Render();
	else
	{
		sprite->SetRect(MenuAnimation->GetRect());
		sprite->SetScale(D3DXVECTOR2(1.6, 2.3));
		sprite->Render();
	}
}