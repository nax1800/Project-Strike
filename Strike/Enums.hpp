#pragma once


enum StrikeState
{
	StrikeIdle,
	StrikeSetup,
	StrikeReady,
	StrikeNone
};

enum FortState
{
	EFortIdle,
	EFortFrontEnd,
	EFortInGame,
	EFortNone
};

enum FortMode
{
	BattleRoyale,
	SaveTheWorld
};

enum FortMap
{
	AthenaTerrain,
	FaceOff,
	TwinePeaks,
	StoneWood,
	CannyValley,
	Plankerton
};