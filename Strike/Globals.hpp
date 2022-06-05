#pragma once

#include "Enums.hpp"
#include "SDK.hpp"

namespace Globals
{
	StrikeState Strike = StrikeNone;
	FortState Fort = EFortNone;
	FortMap Map = AthenaTerrain;
	FortMode Mode = BattleRoyale;

	SDK::UFortEngine* Engine;
	SDK::UWorld** World;
	SDK::ULevel* Level;
	SDK::UGameplayStatics* GameplayStatics;
	SDK::TArray<SDK::AActor*> Actors;
	SDK::UGameInstance* GameInstance;
	SDK::TArray<SDK::ULocalPlayer*> LocalPlayers;
	SDK::ULocalPlayer* LocalPlayer;
	//SDK::UFortCheatManager* CheatManager;
	SDK::UCustomCharacterPart* BodyPart;
	SDK::UCustomCharacterPart* HeadPart;
	SDK::UConsole* Console;
	SDK::AFortPlayerPawn* Pawn;
	SDK::AFortPlayerController* Controller;
	SDK::AFortPlayerState* PlayerState;

}