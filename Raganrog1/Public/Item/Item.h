// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Item.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;

UCLASS()
class RAGANROG1_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItem();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionComponent;
};
