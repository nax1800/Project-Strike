#pragma once

#include "framework.h"
#include <map>
#include "Pawn.hpp"
#include "World.hpp"
#include "kiero/kiero.h"
#include "Menu.hpp"
#include "kiero/minhook/include/MinHook.h"
void* (*ProcessEvent)(void* Object, void* Function, void* Params);


class Game
{
private:

public:
	//	static inline SDK::UCustomCharacterPart* BodyPart = SDK::UObject::FindObject<SDK::UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01");
	//	static inline SDK::UCustomCharacterPart* HeadPart = SDK::UObject::FindObject<SDK::UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1");

	static void LoadMap()
	{
		auto Controller = reinterpret_cast<SDK::AFortPlayerControllerAthena*>(Globals::LocalPlayer->PlayerController);
		if (Globals::Mode == FortMode::BattleRoyale)
		{
			if (Globals::Map == FortMap::AthenaTerrain)
				Controller->SwitchLevel(L"Athena_Terrain");
			else if (Globals::Map == FortMap::FaceOff)
				Controller->SwitchLevel(L"Athena_Faceoff");
		}
		else if (Globals::Mode == FortMode::SaveTheWorld)
		{
			if (Globals::Map == FortMap::StoneWood)
				Controller->SwitchLevel(L"Zone_Outpost_Stonewood");
			else if (Globals::Map == FortMap::Plankerton)
				Controller->SwitchLevel(L"Zone_Outpost_Plankerton_AD");
			else if (Globals::Map == FortMap::CannyValley)
				Controller->SwitchLevel(L"Zone_Outpost_CannyValley");
			else if (Globals::Map == FortMap::TwinePeaks)
				Controller->SwitchLevel(L"Zone_Outpost_TwinePeaks");
		}
		Globals::Fort = EFortIdle;
	}

	static void* FortniteHook(SDK::UObject* Object, SDK::UObject* Function, PVOID Params)
	{
		auto ObjectFullName = Object->GetFullName();
		auto FunctionFullName = Function->GetFullName();
		auto ObjectName = Object->GetName();
		auto FunctionName = Function->GetName();

		//if(GetAsyncKeyState(VK_F4) && Globals::Fort == EFortFrontEnd)
		if (FunctionName.find("BP_PlayButton") != std::wstring::npos && Globals::Fort == EFortFrontEnd)
		{
			auto Controller = reinterpret_cast<SDK::AFortPlayerControllerAthena*>(Globals::LocalPlayer->PlayerController);
			if (Globals::Mode == FortMode::BattleRoyale)
			{
				if (Globals::Map == FortMap::AthenaTerrain)
					Controller->SwitchLevel(L"Athena_Terrain");
				else if (Globals::Map == FortMap::FaceOff)
					Controller->SwitchLevel(L"Athena_Faceoff");
			}
			else if (Globals::Mode == FortMode::SaveTheWorld)
			{
				if (Globals::Map == FortMap::StoneWood)
					Controller->SwitchLevel(L"Zone_Outpost_Stonewood");
				else if (Globals::Map == FortMap::Plankerton)
					Controller->SwitchLevel(L"Zone_Outpost_Plankerton_AD");
				else if (Globals::Map == FortMap::CannyValley)
					Controller->SwitchLevel(L"Zone_Outpost_CannyValley");
				else if (Globals::Map == FortMap::TwinePeaks)
					Controller->SwitchLevel(L"Zone_Outpost_TwinePeaks");
			}
			Globals::Fort = EFortIdle;
		}

		if (FunctionName.find("ReadyToStartMatch") != std::wstring::npos && Globals::Fort == EFortIdle)
		{
			Globals::Fort = EFortInGame;
			if (Globals::Mode == FortMode::BattleRoyale)
			{
				SetConsoleTitleA("Fortnite - [Strike] Player Has Gone In-Game");
				auto GameMode = static_cast<SDK::AFortGameModeAthena*>(Globals::Engine->GameViewport->World->AuthorityGameMode);
				auto GameState = static_cast<SDK::AFortGameStateAthena*>(GameMode->GameState);
				auto Controller = static_cast<SDK::AFortPlayerControllerAthena*>(Globals::Engine->GameInstance->LocalPlayers[0]->PlayerController);
				auto PlayerState = static_cast<SDK::AFortPlayerStateAthena*>(Controller->PlayerState);
				Globals::Controller = Controller;
				Globals::PlayerState = PlayerState;

				auto PlayerStart = GameMode->K2_FindPlayerStart(Controller, L"");
				auto SpawnLoc = PlayerStart->K2_GetActorLocation();

				//SDK::FVector{ -127500, -110500, +4000 }
				World::SpawnActor(SDK::APlayerPawn_Athena_C::StaticClass(), SDK::FVector{ -127500, -110500, +4000 }, {});
				Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortPlayerPawnAthena::StaticClass(), &Globals::Actors);

				auto Pawn = reinterpret_cast<SDK::AFortPlayerPawnAthena*>(Globals::Actors[0]);

				Globals::Pawn = Pawn;

				auto Playlist = SDK::UObject::FindObject<SDK::UFortPlaylistAthena>("FortPlaylistAthena Playlist_Playground.Playlist_Playground");
				Playlist->bNoDBNO = true;
				Playlist->RespawnLocation = SDK::EAthenaRespawnLocation::Air;
				Playlist->RespawnType = SDK::EAthenaRespawnType::InfiniteRespawn;
				GameState->CurrentPlaylistData = Playlist;
				GameState->OnRep_CurrentPlaylistData();

				GameState->WarmupCountdownStartTime = 45;
				GameState->WarmupCountdownEndTime = 45;

				GameState->MiniMapBackgroundDrawingMaterial = nullptr;
				GameState->MinimapBackgroundImage = SDK::UObject::FindObject<SDK::UTexture2D>("Texture2D MiniMapAthena.MiniMapAthena");

				GameState->AircraftStartTime = 5;
				GameState->GamePhase = SDK::EAthenaGamePhase::Warmup;
				GameState->OnRep_GamePhase(SDK::EAthenaGamePhase::None);

				Controller->Possess(Pawn);

				SDK::UFortWeaponItemDefinition* PickaxeDef = SDK::UObject::FindObject<SDK::UFortWeaponItemDefinition>("FortWeaponMeleeItemDefinition WID_Harvest_Pickaxe_Athena_C_T01.WID_Harvest_Pickaxe_Athena_C_T01");
				Pawn->EquipWeaponDefinition(PickaxeDef, Pawn::RandomGuid());

				CreateThread(0, 0, Pawn::PlayerThread, 0, 0, 0);

				Controller->ServerReadyToStartMatch();

			}
			else if (Globals::Mode == FortMode::SaveTheWorld)
			{
				auto GameMode = static_cast<SDK::AFortGameMode*>(Globals::Engine->GameViewport->World->AuthorityGameMode);
				auto GameState = static_cast<SDK::AFortGameState*>(GameMode->GameState);
				auto Controller = static_cast<SDK::AFortPlayerController*>(Globals::Engine->GameInstance->LocalPlayers[0]->PlayerController);
				auto PlayerState = static_cast<SDK::AFortPlayerState*>(Controller->PlayerState);
				Globals::Controller = Controller;
				Globals::PlayerState = PlayerState;
				World::SpawnActor(SDK::AFortGameStateZone::StaticClass(), SDK::FVector{ 0, 0, 0 }, {});
				Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortGameStateZone::StaticClass(), &Globals::Actors);


				GameState = static_cast<SDK::AFortGameStateZone*>(Globals::Actors[0]);

				auto PlayerStart = GameMode->K2_FindPlayerStart(Controller, L"");
				auto SpawnLoc = PlayerStart->K2_GetActorLocation();
				// SDK::FVector{ 0, 275, 0 }
				World::SpawnActor(SDK::APlayerPawn_Generic_C::StaticClass(), SpawnLoc, {});
				Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortPlayerPawn::StaticClass(), &Globals::Actors);
				auto Pawn = reinterpret_cast<SDK::AFortPlayerPawn*>(Globals::Actors[0]);
				Globals::Pawn = Pawn;

				Controller->Possess(Pawn);
				static_cast<SDK::AFortPlayerStateZone*>(PlayerState)->OnRep_CharacterParts();
				CreateThread(0, 0, Pawn::PlayerThread, 0, 0, 0);

				auto QuickBarsPlayer = World::SpawnActor(SDK::AFortQuickBars::StaticClass(), SDK::FVector{ -122398, -103873, 3962 }, {});

				QuickBarsPlayer->SetOwner(Controller);

				Pawn->EquipWeaponDefinition(SDK::UObject::FindObject<SDK::UFortWeaponItemDefinition>("FortWeaponMeleeItemDefinition WID_Harvest_Pickaxe_Athena_C_T01.WID_Harvest_Pickaxe_Athena_C_T01"), Pawn::RandomGuid());
				GameMode->StartMatch();
				GameMode->StartPlay();
			}

		}


		if (FunctionName.find("ServerLoadingScreenDropped") != std::wstring::npos && Globals::Fort == EFortInGame)
		{
			if (Globals::Mode == BattleRoyale)
			{
				static_cast<SDK::AFortPlayerStateAthena*>(Globals::PlayerState)->TeamIndex = SDK::EFortTeam::HumanPvP_Team1;
				Globals::PlayerState->OnRep_PlayerTeam();
				Globals::Controller->bHasClientFinishedLoading = true;
				Globals::Controller->ServerSetClientHasFinishedLoading(true);
				Globals::Controller->bHasServerFinishedLoading = true;
				Globals::Controller->OnRep_bHasServerFinishedLoading();
				static_cast<SDK::AFortPlayerStateAthena*>(Globals::PlayerState)->OnRep_SquadId();
				Globals::Pawn->ServerChoosePart(SDK::EFortCustomPartType::Body, SDK::UObject::FindObject<SDK::UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01"));
				Globals::Pawn->ServerChoosePart(SDK::EFortCustomPartType::Head, SDK::UObject::FindObject<SDK::UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1"));
				static_cast<SDK::AFortPlayerStateAthena*>(Globals::Controller->PlayerState)->OnRep_CharacterParts();
			}
			static_cast<SDK::AFortPlayerStateZone*>(Globals::Controller->PlayerState)->bIsGameSessionOwner = true;
			static_cast<SDK::AFortPlayerStateZone*>(Globals::Controller->PlayerState)->OnRep_SessionOwner();
			Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortHLODSMActor::StaticClass(), &Globals::Actors);
			for (int i = 0; i < Globals::Actors.Num(); i++)
			{
				reinterpret_cast<SDK::AFortHLODSMActor*>(Globals::Actors[i])->K2_DestroyActor();
			}
		}

		if (FunctionName.find("AttemptAircraftJump") != std::wstring::npos && Globals::Fort == EFortInGame || FunctionName.find("AircraftExitedDropZone") != std::wstring::npos && Globals::Fort == EFortInGame)
		{

			if (static_cast<SDK::AFortPlayerControllerAthena*>(Globals::Controller)->IsInAircraft())
			{
				Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortAthenaAircraft::StaticClass(), &Globals::Actors);
				auto bus = static_cast<SDK::AFortAthenaAircraft*>(Globals::Actors[0]);
				auto Loc = bus->K2_GetActorLocation();
				World::SpawnActor(SDK::APlayerPawn_Athena_C::StaticClass(), Loc, {});
				Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortPlayerPawnAthena::StaticClass(), &Globals::Actors);
				Globals::Pawn = static_cast<SDK::AFortPlayerPawnAthena*>(Globals::Actors[0]);
				Globals::Pawn->K2_SetActorRotation(SDK::FRotator{ 0,Globals::Pawn->K2_GetActorRotation().Yaw,0 }, false);
				Globals::Controller->Possess(Globals::Pawn);

				Globals::Pawn->EquipWeaponDefinition(SDK::UObject::FindObject<SDK::UFortWeaponItemDefinition>("FortWeaponMeleeItemDefinition WID_Harvest_Pickaxe_Athena_C_T01.WID_Harvest_Pickaxe_Athena_C_T01"), SDK::FGuid{ rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000 });
				//Globals::CheatManager->God();
				Globals::Pawn->ServerChoosePart(SDK::EFortCustomPartType::Body, SDK::UObject::FindObject<SDK::UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01"));
				Globals::Pawn->ServerChoosePart(SDK::EFortCustomPartType::Head, SDK::UObject::FindObject<SDK::UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1"));
				static_cast<SDK::AFortPlayerStateAthena*>(Globals::Controller->PlayerState)->OnRep_CharacterParts();
			}
		}
		if (FunctionName.find("ClientOnPawnDied") != std::wstring::npos && Globals::Fort == EFortInGame)
		{
			World::SpawnActor(SDK::APlayerPawn_Athena_C::StaticClass(), SDK::FVector{ 0, 0, 15000 }, {});
			Globals::GameplayStatics->STATIC_GetAllActorsOfClass(Globals::Engine->GameViewport->World, SDK::AFortPlayerPawnAthena::StaticClass(), &Globals::Actors);
			Globals::Pawn = static_cast<SDK::AFortPlayerPawnAthena*>(Globals::Actors[0]);
			Globals::Pawn->K2_SetActorRotation(SDK::FRotator{ 0,Globals::Pawn->K2_GetActorRotation().Yaw,0 }, false);
			Globals::Controller->Possess(Globals::Pawn);
			Globals::Pawn->bIsSkydiving = true;
			Globals::Pawn->OnRep_IsSkydiving(Globals::Pawn->IsSkydiving());
		}


		return ProcessEvent(Object, Function, Params);
	}

	static DWORD CheckIfAvailable(LPVOID lpParam)
	{
		auto Engine = SDK::UObject::FindObject<SDK::UFortEngine>("FortEngine_");
		auto LclPlayer = reinterpret_cast<SDK::UFortLocalPlayer*>(Engine->GameInstance->LocalPlayers[0]);
		auto GmplStat = reinterpret_cast<SDK::UGameplayStatics*>(SDK::UGameplayStatics::StaticClass());
		if (Engine && LclPlayer && GmplStat && Globals::Strike == StrikeState::StrikeSetup)
		{
			Globals::Engine = Engine;
			Globals::LocalPlayer = LclPlayer;
			Globals::GameplayStatics = GmplStat;
			Globals::Strike = StrikeReady;
			Globals::Fort = EFortFrontEnd;
			SetConsoleTitleA("Fortnite - [Strike] Ready!");
		}
		return NULL;
	}

	static void SetupStrike(uintptr_t Offset)
	{
			 MH_Initialize();
			 MH_CreateHook(reinterpret_cast<LPVOID>(Offset), FortniteHook, reinterpret_cast<LPVOID*>(&ProcessEvent));
			 MH_EnableHook(reinterpret_cast<LPVOID>(Offset));
	}

	static DWORD CreateMenu(LPVOID lpvoid)
	{
		bool init_hook = false;
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&Menu::oPresent, Menu::hkPresent);
			init_hook = true;
			SetWindowTextA(Menu::window, "Fortnite - Using Strike");
		} while (!init_hook);
		return TRUE;

		return NULL;
	}
	static void Setup()
	{
		Util::InitConsole();
		SetConsoleTitleA("Fortnite - [Strike] Setting Up!");

		auto GObjectsAddress = Util::FindPattern("48 8B 05 ? ? ? ? 48 8D 1C C8 81 4B ? ? ? ? ? 49 63 76 30");
		auto ToStringAddress = Util::FindPattern("48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9");
		auto FreeAddress = Util::FindPattern("48 85 C9 74 1D 4C 8B 05 ? ? ? ? 4D 85 C0");

		auto ObjectsOffset = *(int32_t*)(GObjectsAddress + 3);
		auto FinalObjectsAddress = GObjectsAddress + 7 + ObjectsOffset;

		SDK::UObject::GObjects = decltype(SDK::UObject::GObjects)(FinalObjectsAddress);
		SDK::FNameToString = decltype(SDK::FNameToString)(ToStringAddress);
		SDK::FreeMemory = decltype(SDK::FreeMemory)(FreeAddress);

		auto PE = *reinterpret_cast<void***>(SDK::UObject::FindObject<SDK::UFortEngine>("FortEngine_"));

		CreateThread(0, 0, CreateMenu, 0, 0, 0);
		CreateThread(0, 0, CheckIfAvailable, 0, 0, 0);

		Globals::Strike = StrikeSetup;

		SetupStrike((uintptr_t)PE[64]);

	}
};