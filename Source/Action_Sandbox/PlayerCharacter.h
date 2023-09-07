// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AGun;

UCLASS()
class ACTION_SANDBOX_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* FireAttackMontage;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void Fire();
	void AutoDie();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	UPROPERTY(EditAnywhere)
	bool Dead = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY()
	AGun* Gun;
};
