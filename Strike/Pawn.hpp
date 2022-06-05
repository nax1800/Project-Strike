#pragma once
#include "Globals.hpp"
#include "util.h"
#include "SDK.hpp"

class Pawn
{
public:
	static SDK::FGuid RandomGuid()
	{
		SDK::FGuid Guid;
		Guid.A = rand() % 1000;
		Guid.B = rand() % 1000;
		Guid.C = rand() % 1000;
		Guid.D = rand() % 1000;
		return Guid;
	}

	static void EquipWeapon(std::string Type, std::string WID)
	{
		std::string finalwid = Type + " " + WID + "." + WID;
		std::string wid = finalwid;
		Globals::Pawn->EquipWeaponDefinition(SDK::UObject::FindObject<SDK::UFortWeaponItemDefinition>(wid), RandomGuid());
	}

	static DWORD PlayerThread(LPVOID lpParam)
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_SPACE) && 0x01)
			{
				if (Globals::Pawn->CanJump() && !Globals::Pawn->IsJumpProvidingForce()) {
					Globals::Pawn->Jump();
				}
			}
			Globals::Pawn->CurrentMovementStyle = Globals::Controller->bWantsToSprint ? SDK::EFortMovementStyle::Sprinting : SDK::EFortMovementStyle::Sprinting;

			if (Globals::Fort == EFortFrontEnd)
				break;

		}
		ExitThread(0);
	}
};