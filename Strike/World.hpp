#include "SDK.hpp"
#include "Globals.hpp"

class World
{
public:
	static SDK::AActor* SpawnActor(SDK::UClass* ActorClass, SDK::FVector Location, SDK::FRotator Rotation)
	{
		SDK::FQuat Quat;
		SDK::FTransform Transform;
		Quat.W = 0;
		Quat.X = Rotation.Pitch;
		Quat.Y = Rotation.Roll;
		Quat.Z = Rotation.Yaw;

		Transform.Rotation = Quat;
		Transform.Scale3D = SDK::FVector{ 1,1,1 };
		Transform.Translation = Location;

		auto Actor = Globals::GameplayStatics->STATIC_BeginSpawningActorFromClass(Globals::Engine->GameViewport->World, ActorClass, Transform, false, nullptr);
		Globals::GameplayStatics->STATIC_FinishSpawningActor(Actor, Transform);
		return Actor;
	}
};