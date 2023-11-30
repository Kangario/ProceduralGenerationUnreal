#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "Containers/Array.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetProceduralMeshLibrary.h"

#include "ProceduralLandscapeGeneric.generated.h"

enum sideChank 
{
	front,
	right,
	left,
	back
};
class Chank {
public:
	int idChank;
	int distance = 0;
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	float offsetX = 0;
	float offsetY = 0;
	bool frontSpawn = true;
	bool rightSpawn = true;
	bool backSpawn = true;
	bool leftSpawn = true;

};
struct Keys {
	public:
		int idChank = 1;
		int indexChank = 0;
};
class UProceduralMeshComponent;
UCLASS()
class RAGANROG1_API AProceduralLandscapeGeneric : public AActor
{
	GENERATED_BODY()
public:	

	AProceduralLandscapeGeneric();
	TArray<int32> Triangles;
	float offsetX = 0;
	float offsetY = 0;
	int offsetTriagles = 0;
	int currentChank = 0;
	int NumberIteration = 0;
	bool isGenerate = true;
	bool One = true;
	
private:
	
	TArray<FVector> GeneratePoints(int numberIterations, int sizeChank);
	TArray<int32> TrianglesGenerate(int numberIterations, int sizeChank);
	void GenerateChanks(FVector PlayerPosition);
	void IdentificationChank(FVector PlayerPosition);
	void PerlinNoiseGeneration();
	int CheckDistance(FVector PlayerPositio, sideChank side);
protected:
	
	virtual void BeginPlay() override;
	void GenerateSquareMesh(int sizeChank, int numberIterations);
public:	
	int timer;
	UPROPERTY(EditAnywhere)
		float zMultiply = 1.0f;
	UPROPERTY(EditAnywhere)
		float ScaleXNoise = 100.0f;
	UPROPERTY(EditAnywhere)
		float ScaleYNoise = 100.0f;

	sideChank side;
	TArray<FVector> coordinats;
	TArray<Chank> chank;
	Keys key;
	UProceduralMeshComponent* ProceduralMesh;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;
	UPROPERTY(EditAnywhere)
		int sizeChankGlobal;
	UPROPERTY(EditAnywhere)
		float sizeSegment;
	
	virtual void Tick(float DeltaTime) override;

};
