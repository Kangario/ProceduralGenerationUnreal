#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Item/Item.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player_controller.generated.h"

UCLASS()
class RAGANROG1_API APlayer_controller : public ACharacter
{
	GENERATED_BODY()
public:
	APlayer_controller();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	void Turn(float Value);
	void LookUp(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlapingItem;
public:
	FORCEINLINE void SetOverlappingItem(AItem* item){OverlapingItem = item; }	
};
