﻿#pragma once

namespace Define
{
	const float WinWidth = 800.0f;
	const float WinHeight = 600.0f;

	const float GameWidth = 500.0f;
	const float GameHeight = 500.0f;


	//Map
	const char TileSetPNG[] = "./Resource Files/aladin.png";
	const char MapXML[] = "./Resource Files/Mapscene1.tmx";
	const char MapXML2[] = "./Resource Files/backgroud.tmx";
	const char GridXML[] = "./Resource Files/Grid.xml";
	const char MapXML3[] = "./Resource Files/MapAla3.tmx";
	const char TileSetPNG3[] = "./Resource Files/map3.png";

	const char MapBoss[] = "./Resource Files/MapbossAladdin.tmx";
	const char MapBoss2[] = "./Resource Files/MapbossAladdin2.tmx";
	const char TileSetBoss[] = "./Resource Files/final.png";


	//Speed
	const float RunSpeed = 2.0f;
	const float GlideSpeed = 3.0f;
	const float JumpSpeed = 3.0f;
	const float ClampSpeed = 0.8f;
	const float KickSpeed = 1.0f;
	const float BulletSpeed = 4.0f;
	const float Gravity = 1.0f;
	const float FallAcceleration = 0.15f;

	//Distance
	const float JumpMax = 100.0f;
	const float JumpMin = 50.0f;
	const float GlideMax = 100.0f;
	const float GlideMin = 30.f;

	//Time
	const float DelayAnimation = 0.2f;



}