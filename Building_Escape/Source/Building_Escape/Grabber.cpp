// Copyright Michael Bridges 2019

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
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

	Physicshandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Physicshandle)
	{
		// Physics handle is found
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT(" The %s has no PhysicsComponent !!"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		UE_LOG( LogTemp , Warning , TEXT("Input component has found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber :: Grab);
	}


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

	FHitResult Hit;

	FCollisionQueryParams TraceParmas
	(
		FName(TEXT("")),
		false,
		GetOwner()
	);

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerviewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams (ECollisionChannel :: ECC_PhysicsBody),
		TraceParmas
	);

		AActor* ActorHit = Hit.GetActor();
		if(ActorHit)
		{
			// Ray has hit the Actor
		}
	
}

void UGrabber :: Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber is pressed"));
}