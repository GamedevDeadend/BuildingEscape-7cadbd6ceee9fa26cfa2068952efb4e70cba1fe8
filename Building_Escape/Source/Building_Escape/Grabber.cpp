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
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();

	FindPhysicshandle();
	// ...
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		FVector PlayerviewLocation;
		FRotator PlayerviewRotator;

		// Get Player view point
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
		(
			OUT PlayerviewLocation,
			OUT PlayerviewRotator
		);

		FVector LineTraceEnd = PlayerviewLocation + (PlayerviewRotator.Vector()) * Reach;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber ::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber is pressed"));

	FVector PlayerviewLocation;
	FRotator PlayerviewRotator;

	// Get Player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerviewLocation,
		OUT PlayerviewRotator);

	FVector LineTraceEnd = PlayerviewLocation + (PlayerviewRotator.Vector()) * Reach;

	FHitResult HitPhysicsBody = GetFirstPhysicsBodyInreach();
	UPrimitiveComponent *ComponentToGrab = HitPhysicsBody.GetComponent();

	if (HitPhysicsBody.GetActor())

	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd);
	}
}


void UGrabber ::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber is Release"));

	PhysicsHandle->ReleaseComponent();
}


void UGrabber ::FindPhysicshandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT(" The %s has no PhysicsComponent !!"), *GetOwner()->GetName());
	}
}


void UGrabber ::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component has found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber ::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber ::Release);
	}
}


FHitResult UGrabber ::GetFirstPhysicsBodyInreach()
{
	FVector PlayerviewLocation;
	FRotator PlayerviewRotator;

	// Get Player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerviewLocation,
		OUT PlayerviewRotator);

	FVector LineTraceEnd = PlayerviewLocation + (PlayerviewRotator.Vector()) * Reach;

	/*
	DrawDebugLine
		(
			GetWorld(),
			PlayerviewLocation,
			LineTraceEnd,
			FColor(255,255,255),   //FOR DEBUG PURPOSES ONLY
			false,
			0.f,
			0.f,
			5.f
		);
	*/

	FHitResult Hit;

	FCollisionQueryParams TraceParmas(
		FName(TEXT("")),
		false,
		GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerviewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel ::ECC_PhysicsBody),
		TraceParmas);

	AActor *ActorHit = Hit.GetActor();
	
	return Hit;
}