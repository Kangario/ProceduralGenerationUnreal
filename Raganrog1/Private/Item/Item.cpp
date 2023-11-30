

#include "Item/Item.h"

AItem::AItem()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
    CollisionComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f)); 
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
  //  SkeletalMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetIncludingScale);
	

	
	
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

