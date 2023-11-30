#include "Landscape/ProceduralLandscapeGeneric.h"



AProceduralLandscapeGeneric::AProceduralLandscapeGeneric()
{
	PrimaryActorTick.bCanEverTick = true;
    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = ProceduralMesh;
    sizeChankGlobal = 5;
    sizeSegment = 200.0f;
}

TArray<FVector>  AProceduralLandscapeGeneric::GeneratePoints(int numberIterations, int sizeChank)
{   
    TArray<FVector> Vertices;
    for (int x = 0; x < sizeChank; x++) {
        for (int y = 0; y < sizeChank; y++) {
           //float z = FMath::PerlinNoise2D(FVector2D(x+ ScaleXNoise + 0.1, y+ ScaleYNoise + 0.1)) * zMultiply;
            DrawDebugSphere(GetWorld(), FVector(x* sizeSegment + offsetX, y * sizeSegment + offsetY, 0), 5, 8, FColor::Red, false, 60, 0, 1);
            Vertices.Add(FVector(x * sizeSegment + offsetX, y * sizeSegment + offsetY, 0));
        }
    }
    return Vertices;
}

TArray<int32> AProceduralLandscapeGeneric::TrianglesGenerate(int numberIterations, int sizeChank)
{
    TArray<int32> _Triangles;
    int row1 = Triangles.Num();
    int row2 = sizeChank + Triangles.Num();
    int row3 = sizeChank + 1 + Triangles.Num();
    int chet = 0;
    int chet1 = 1;
    for (int i = offsetTriagles; i < (sizeChank*sizeChank)*2 + offsetTriagles; i++) {
        if (i == ((sizeChank + (sizeChank - 4)) * chet1)) {
            row1 += 2;
            row3 += 2;
            chet += 2;
            chet1++;
        }
        else if (i % 2 == 1)
        {
            row1 += 1;
            row3 += 1;
            chet++;
        }
        _Triangles.Add(row1);
        _Triangles.Add(row2 - (sizeChank - 1) + chet);
        _Triangles.Add(row3);
        _Triangles.Add(row3);
        _Triangles.Add(row2 + chet);
        _Triangles.Add(row1);
    }
    return _Triangles;
}

void AProceduralLandscapeGeneric::GenerateChanks(FVector PlayerPosition)
{
    //������ ���� � ����������� ���������, ��� �������� ������� ������ ���������. ����� �� ��� Y ������������ 25 �����. 
    if (chank[key.indexChank].Vertices[sizeChankGlobal - 1].Y < PlayerPosition.Y) {
    if (chank[key.indexChank].frontSpawn == true) {
        
            chank[key.indexChank].distance = CheckDistance(PlayerPosition, front);
            chank[key.indexChank].offsetY += ((sizeChankGlobal * sizeSegment)-sizeSegment) * chank[key.indexChank].distance;
            offsetY = chank[key.indexChank].offsetY;
            chank[key.indexChank].frontSpawn = false;
            chank[key.indexChank].backSpawn = false;
            GenerateSquareMesh(sizeChankGlobal, NumberIteration);
            chank[key.indexChank+1].backSpawn = false;
       }
    }
    if (chank[key.indexChank].Vertices[0].Y > PlayerPosition.Y) {
    if (chank[key.indexChank].backSpawn == true) {
        
            chank[key.indexChank].distance = CheckDistance(PlayerPosition, back);
            chank[key.indexChank].offsetY -= ((sizeChankGlobal * sizeSegment) - sizeSegment) * chank[key.indexChank].distance;
            offsetY = chank[key.indexChank].offsetY;
            chank[key.indexChank].backSpawn = false;
            chank[key.indexChank].frontSpawn = false;
            GenerateSquareMesh(sizeChankGlobal, NumberIteration);
            chank[key.indexChank+1].frontSpawn = false;
        }
    }
    
}

void AProceduralLandscapeGeneric::IdentificationChank(FVector PlayerPosition)
{         
    //������������� ����� ���������� ��������� ���� ��������� ������� ����� � ������������ �������� ��������� ������ � ���������� �����.
    for (int i = 0; i < chank.Num(); i++) {
        if (PlayerPosition.X < chank[i].Vertices[sizeChankGlobal * sizeChankGlobal - 1].X && 
            PlayerPosition.X > chank[i].Vertices[0].X &&
            PlayerPosition.Y < chank[i].Vertices[sizeChankGlobal * sizeChankGlobal - 1].Y &&
            PlayerPosition.Y > chank[i].Vertices[0].Y) {
            //�������� � ���� ����� ��� ������ � ������� � ��� Id ��� ��������
            key.idChank = chank[i].idChank;
            key.indexChank = i;
            
        }
     
    }


}


void AProceduralLandscapeGeneric::PerlinNoiseGeneration()
{


}

int AProceduralLandscapeGeneric::CheckDistance(FVector PlayerPositio, sideChank Side)
{
    int distance = 0;
    switch (Side)
    {
    case front:
        while (true) {
            if (PlayerPositio.Y > ((sizeChankGlobal - 1) * sizeSegment) * distance) {
                break;
            }
            distance++;
        }
        return distance - 1;
        break;
    case right:
        break;
    case left:
        break;
    case back:
        while (true) {
            if (PlayerPositio.Y < ((sizeChankGlobal - 1) * sizeSegment) * distance) {
                break;
            }
            distance--;
        }
        
        return distance+1;
        break;
    default:
        break;
    }
    return 0;
}


void AProceduralLandscapeGeneric::BeginPlay()
{

	
	Super::BeginPlay();
    GenerateSquareMesh(sizeChankGlobal, NumberIteration);
   
   
}

void AProceduralLandscapeGeneric::GenerateSquareMesh(int sizeChank, int numberIterations)
{

    TArray<FVector2D> UVs;
    Chank tempChank;
    ProceduralMesh->ClearAllMeshSections();
    UVs.Add(FVector2D(0,0));
    UVs.Add(FVector2D(0,1));
    UVs.Add(FVector2D(1, 0));
    UVs.Add(FVector2D(1,1));
    TArray<FVector> normals;
    TArray<FProcMeshTangent> tangent;
    //���������� ������ ������� �.� ����� ��� �������� ���� �������.
    coordinats += GeneratePoints(numberIterations, sizeChank);
    // � ��������� �������� ����� � �������� ���������� � ��� ������ (ID)
    tempChank.Vertices = GeneratePoints(numberIterations, sizeChank);;
    tempChank.idChank = chank.Num() + 1;
    chank.Add(tempChank);
   // Triangles += TrianglesGenerate(numberIterations, sizeChank);
    ProceduralMesh->CreateMeshSection(0, coordinats, Triangles, normals, UVs, TArray<FColor>(), tangent, true);
    if (Material)
    {
        ProceduralMesh->SetMaterial(0, Material);
    }
}

void AProceduralLandscapeGeneric::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FVector MyCharacter = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    //������ ����� ��� ��������� ���������.
    if (timer > 100) {
        DrawDebugString(GetWorld(), FVector(0, 0, 0), FString::FromInt(coordinats.Num()), nullptr, FColor::Blue, 0.0f, false);
        IdentificationChank(MyCharacter);
        GenerateChanks(MyCharacter);
    }
    timer++;
    DrawDebugString(GetWorld(), FVector(100, 0, 0), FString::FromInt(timer), nullptr, FColor::Blue, 0.0f, false);
    DrawDebugString(GetWorld(), FVector(200, 0, 0), FString::FromInt(currentChank), nullptr, FColor::Blue, 0.0f, false);
}
/*��� ������ � ����, ��� ���� ����� ���������� �������� �������� �����. �.� ��� ����� ������� ����� � ������� �������� � ���� 
����� id ����� � ��� ������ � �������*/