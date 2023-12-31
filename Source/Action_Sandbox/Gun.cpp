// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger(USceneComponent* Mesh)
{

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("WeaponSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("WeaponSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	if (GunTraceSuccess(Hit, ShotDirection))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		DrawDebugLine(GetWorld(), GetActorLocation(), Hit.ImpactPoint, FColor::Green, false, 1, 0, 1);
	}
}

bool AGun::GunTraceSuccess(FHitResult& Hit, FVector& ShotDirection)
{
    AController* OwnerController = GetOwnerController();
    if (OwnerController == nullptr)
        return false;

    FVector Location;
    FRotator Rotation;
    OwnerController->GetPlayerViewPoint(Location, Rotation);

    float RandomPitchAngle = FMath::RandRange(-Spread, Spread); 
    float RandomYawAngle = FMath::RandRange(-Spread, Spread);

    FRotator RandomRotation = FRotator(RandomPitchAngle, RandomYawAngle, 0);
    ShotDirection = (Rotation + RandomRotation).Vector();

    FVector End = Location + ShotDirection * MaxRange;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());
    return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;

	return OwnerPawn->GetController();
}