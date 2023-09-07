// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Gun.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<AGun>(GunClass);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Fire);

	PlayerInputComponent->BindAction(TEXT("AutoDeath"), EInputEvent::IE_Pressed, this, &APlayerCharacter::AutoDie);
}

bool APlayerCharacter::IsDead() const
{
	return Dead;
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Fire()
{
	if (FireAttackMontage == nullptr)
	{
		Gun->PullTrigger();
		return;
	}

	PlayAnimMontage(FireAttackMontage);
}

void APlayerCharacter::AutoDie()
{
	Dead = !Dead;
	UE_LOG(LogTemp, Warning, TEXT("Dead = %b"), Dead);
}

