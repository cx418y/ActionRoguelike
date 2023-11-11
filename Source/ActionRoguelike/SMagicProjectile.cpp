// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SAttributeComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	
// 	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
// 	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
// 	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;



	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true; // 初始速度将相对于对象的本地坐标空间进行计算
	MovementComp->SetVelocityInLocalSpace(ASMagicProjectile::GetMoveDirection());
}

FVector ASMagicProjectile::GetMoveDirection()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("into GetDrrection."));

	APawn* MyInstigator = Cast<APawn>( this->GetInstigator());
	FVector HitLocation;
	if (MyInstigator)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("instigator exisit."));
		USpringArmComponent* SpringArmComp = Cast<USpringArmComponent>(MyInstigator->GetComponentByClass(USpringArmComponent::StaticClass()));
		FVector SpringArmForwardVector = SpringArmComp->GetForwardVector();
		FVector End = SpringArmForwardVector * 1000;

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);  // 世界中动态的物体才能触发

		FHitResult Hit;
		bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, SpringArmForwardVector, End, ObjectQueryParams);
		
		FColor LineColor = bHit ? FColor::Green : FColor::Red;
		if (bHit)
		{
			HitLocation = Hit.ImpactPoint;
		}
		else {
			HitLocation = End;
		}
		DrawDebugLine(GetWorld(), SpringArmForwardVector, End,LineColor, false, 2.0f, 0, 2.0f);
		
	}
	return HitLocation - this->GetActorLocation();

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttribteComp = Cast<USAttributeComponent>( OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(AttribteComp)
		{
			AttribteComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
	}
}



// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

