#include "Player/Player_controller.h"

APlayer_controller::APlayer_controller()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,0.f,400.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 0.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
}

void APlayer_controller::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayer_controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"),this, &APlayer_controller::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"),this, &APlayer_controller::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"),this, &APlayer_controller::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"),this, &APlayer_controller::LookUp);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
}
void APlayer_controller::MoveForward(float Value)
{	
	
		if (Controller && Value!=0.f)
		{
			//find out which is forward
			const FRotator ControlRotation = GetControlRotation();
			const FRotator YawRotation(0.f,ControlRotation.Yaw, 0.f);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
}
void APlayer_controller::MoveRight(float Value)
{		
	
		if (Controller && Value!=0.f)
		{
			const FRotator ControlRotation = GetControlRotation();
			const FRotator YawRotation(0.f,ControlRotation.Yaw, 0.f);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
}
void APlayer_controller::Turn(float Value)
{
AddControllerYawInput(Value);
}
void APlayer_controller::LookUp(float Value)
{
AddControllerPitchInput(Value);
}

