// Copyright Michael Bridges 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:

	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened;
	float CloseDelay = 0.7f;

	UPROPERTY(EditAnyWhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnyWhere)
	float DoorClosedSpeed = 0.8f;

	UPROPERTY(EditAnyWhere)
	float DoorOpenSpeed = 0.2f;
	
	UPROPERTY(EditAnyWhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnyWhere)
	AActor* ActorThatOpen;

};
