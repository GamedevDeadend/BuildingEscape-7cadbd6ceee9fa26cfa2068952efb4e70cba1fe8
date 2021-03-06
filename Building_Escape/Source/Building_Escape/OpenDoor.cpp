// Copyright Michael Bridges 2019

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;
	FindPressurePlate();
	FindAudio();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMass() > OpenDoorMass)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		if (!DoorAudio){return;}
		if (AudioSwitch)
		{DoorAudio->Play();}
		AudioSwitch = false;
	}

	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > CloseDelay)
		{
			CloseDoor(DeltaTime);
			if(!AudioSwitch)
			{DoorAudio->Play();}
			AudioSwitch = true;
		}
	}
}

void UOpenDoor ::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor ::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorClosedSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor :: TotalMass() const
{
	float Totalmass = 0.f;

	TArray <AActor*> ActorThatOverlap;
	
	if (!PressurePlate) {return Totalmass;}

	PressurePlate->GetOverlappingActors(OUT ActorThatOverlap);
	for(AActor* Actor : ActorThatOverlap)
	{
		Totalmass +=  Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return Totalmass;
}

void UOpenDoor :: FindAudio()
{
	DoorAudio = GetOwner()->FindComponentByClass <UAudioComponent>();

	if (!DoorAudio)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no audio component present"), *GetOwner()->GetName());
	}
}

void UOpenDoor :: FindPressurePlate ()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has component attached to it but without pressure plates"), *GetOwner()->GetName());
	}

}