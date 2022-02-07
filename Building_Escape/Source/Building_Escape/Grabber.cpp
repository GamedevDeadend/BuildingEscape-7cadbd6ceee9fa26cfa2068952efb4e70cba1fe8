// Copyright Michael Bridges 2019

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting on duty !!"));

	// ...
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerviewLocation;
	FRotator PlayerviewRotator;

	//Get Player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerviewLocation,
		OUT PlayerviewRotator
	);

	UE_LOG
	(
		LogTemp, Display,TEXT("Location: %s  Rotation: %s"),
		*OUT PlayerviewLocation.ToString(),*OUT PlayerviewRotator.ToString()
	);

	FVector LineTraceEnd = PlayerviewLocation + (PlayerviewRotator.Vector())*Reach;
	DrawDebugLine
	(
		GetWorld(),
		PlayerviewLocation,
		LineTraceEnd,
		FColor(255,255,255),
		false,
		0.f,
		0.f,
		5.f
	);

	

	// ...
}
