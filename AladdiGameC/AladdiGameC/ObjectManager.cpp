#include "ObjectManager.h"
#include "string.h"

ObjectManager::ObjectManager()
{
}
ObjectManager::~ObjectManager()
{

	delete map;
	delete viewport;




}

//Load Game
void ObjectManager::Init(Graphic* graphic)
{

	this->sound = new Sound(graphic->GetHwnd());
	this->sound->Init_DirectSound();
	soundGame = this->sound->LoadSound("./Sound/PrinceAli.wav");
	//
	spriteAladdin = new Sprite(graphic, "AladinAnimXml.png", D3DCOLOR_XRGB(255, 0, 255));
	infoAlddin = new SpriteSheet("AladinAnimXml.xml");
	spriteBrick = new Sprite(graphic, "./Resource Files/Brick.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBrick = new SpriteSheet("./Resource Files/Brickxml.xml");
	//
	spritePendu = new Sprite(graphic, "./Resource Files/pendulum.png", D3DCOLOR_XRGB(163, 73, 164));
	infoPendu = new SpriteSheet("./Resource Files/conlacxml.xml");
	//
	spriteArrow = new Sprite(graphic, "./Resource Files/arrow.png", D3DCOLOR_XRGB(163, 73, 164));
	infoArrow = new SpriteSheet("./Resource Files/arrow.xml");
	//
	spriteGuard = new Sprite(graphic,"./Resource Files/Guard.png", D3DCOLOR_XRGB(163, 73, 164));
	infoGuard = new SpriteSheet("./Resource Files/Guard.xml");
	//
	spriteBat = new Sprite(graphic, "./Resource Files/Batxml.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBat = new SpriteSheet("./Resource Files/Batsprite.xml");
	//
	spriteSkeleton = new Sprite(graphic, "./Resource Files/skeleton.png", D3DCOLOR_XRGB(163, 73, 164));
	infoSkeleton = new SpriteSheet("./Resource Files/skeleton.xml");
	//
	spriteRodGuard = new Sprite(graphic, "./Resource Files/RodGuard.png", D3DCOLOR_XRGB(163, 73, 164));
	infoRodGuard = new SpriteSheet("./Resource Files/RodGuard.xml");
	//
	pendu = new pendulum(spritePendu, infoPendu, D3DXVECTOR2(400, 300));

	
	//
	
	//
	arrow = new Arrow(spriteArrow, infoArrow, D3DXVECTOR2(420, 300));

	//
	
	point = new PointMap();
	//
	
	aladin = new Aladdin(spriteAladdin, infoAlddin);

	guard = new Guard(spriteGuard, infoGuard, D3DXVECTOR2(800, 50), aladin);
	skeleton = new Skeleton(spriteSkeleton, infoSkeleton, D3DXVECTOR2(800, 60), aladin);
	rodGuard = new RodGuard(spriteRodGuard, infoRodGuard, D3DXVECTOR2(800, 233), aladin);

	bat = new Bat(spriteBat, infoBat, D3DXVECTOR2(200, 621), aladin);
	viewport = new Viewport(0, 1152);
	map = new Map(graphic, MapXML, TileSetPNG);
	map->WriteGrid(map->grid);
	map2 = new Map(graphic, MapXML2, TileSetPNG);
	map3 = new Map3D(graphic, MapXML3, TileSetPNG3);
	grid = new Grid();
	TiXmlDocument doc(GridXML);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load QuadTree.xml file", "Error", MB_OK);
		return;
	}
	TiXmlElement* root = doc.RootElement();
	ReadGrid(root, grid);
	objects = grid->GetCell(2, 2)->objects;
	prePosView = viewport->GetPosition();
	prePosAla = point->GetPosition();

}

//Update Game
void ObjectManager::Update(float dt, Keyboard* keyboard)
{
	aladin->ChangeAnimation(dt, keyboard);
	//aladin->SetVelocityY(-1);
	//Kiểm tra dịch chuyển
	if (prePosView != viewport->GetPosition())
	{
		prePosView = viewport->GetPosition();

	}

	point->Update(dt, keyboard);
	for (size_t i = 0; i < listWall.size(); i++)
	{
		D3DXVECTOR2 disMan = aladin->Distance(dt);
		aladin->OnCollision(listWall.at(i), disMan, disMan);

		//Kiểm tra cổng
		

		listWall.at(i)->Update(dt, keyboard);
	}
	
	aladin->Update(dt, keyboard);

	printf("%f\n", aladin->GetPosition().y);
	//
	//brick->SetPosition(D3DXVECTOR2(aladin->GetPosition().x,aladin->GetPosition().y-45));

	

	pendu->Update(dt, keyboard);

	pendu->Update(dt,keyboard);
	arrow->Update(dt, keyboard);
	guard->Update(dt, keyboard);
	rodGuard->Update(dt, keyboard);
	skeleton->Update(dt, keyboard);
	bat->Update(dt, keyboard);
	for (auto o : objects) {
		o->Update(dt, keyboard);
	}
	viewport->Update(dt, keyboard, aladin->GetPosition(), aladin->GetVelocity(), map->listStage);

	sound->LoopSound(soundGame);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);

	
	pendu->Render(viewport);


	for (auto o : objects) {
		o->Render(viewport);
	}

	arrow->Render(viewport);
	guard->Render(viewport);
	skeleton->Render(viewport);
	rodGuard->Render(viewport);

	aladin->Render(viewport);
	bat->Render(viewport);
	map2->Render(viewport);
	map3->Render(viewport, D3DXVECTOR2(-50, 70),point->GetPosition());
}

void ObjectManager::ReadGrid(TiXmlElement * root, Grid * grid)
{
	if (!root)
		return;
	TiXmlElement *cell = root->FirstChildElement();

	while (cell != NULL)
	{
		float x, y, numobject,w,h;
		cell->QueryFloatAttribute("x", &x);
		cell->QueryFloatAttribute("y", &y);
		
		cell->QueryFloatAttribute("numobject", &numobject);
		if (numobject > 0) {
			TiXmlElement *obj = cell->FirstChildElement();
			for (int i = 0; i < numobject; i++) {
				string name = (char*)obj->Attribute("name");
				float posX, posY;
				int alow = 0;
				obj->QueryIntAttribute("alow", &alow);
				obj->QueryFloatAttribute("x", &posX);
				obj->QueryFloatAttribute("y", &posY);
				obj->QueryFloatAttribute("w", &w);
				obj->QueryFloatAttribute("h", &h);

				if (name == "Helit") {
					Brick* brick = new Brick(spriteBrick, infoBrick, D3DXVECTOR2(posX, posY));
					brick->SetName(name);
					if (alow) {
						brick->setstate(Brick::oppen);
					}
					else {
						brick->setstate(Brick::close);
					}
					grid->GetCell(x, y)->Add(brick);
				}
				else if(name == "Wall")
				{
					Object* wall = new Object();
					wall->SetName(name);
					wall->SetTag(name);
					wall->SetPosition(D3DXVECTOR2(posX, posY));
					wall->SetPositionStart(D3DXVECTOR2(posX, posY));
					wall->SetBound(w, h);
					grid->GetCell(x, y)->Add(wall);
					listWall.push_back(wall);

				}
				



				obj = obj->NextSiblingElement();
			}
		}

		cell = cell->NextSiblingElement();
	}


}



