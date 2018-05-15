// Copyright by Carlo Eigenmann 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Return hit for first physics body in reach

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Find attached components
	void FindPhysicsHandleComponent();
	void SetupInputComponent();

	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetReachLineStart() const;

	FVector GetReachLineEnd() const;

private:
	// Player reach
	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach, and released
	void Grab();
	void Release();
};
