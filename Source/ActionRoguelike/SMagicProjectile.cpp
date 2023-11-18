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
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	DamageAmount = 20.0f;
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			// minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(-DamageAmount);

			// Only explode when we hit something valid
			Explode();
		}
	}
}

// FVector ASMagicProjectile::GetMoveDirection()
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("into GetDrrection."));
// 
// 	UE_LOG(LogTemp, Warning, TEXT("Instigator: %s"), GetInstigator());
// 	APawn* MyInstigator = Cast<APawn>( GetInstigator());
// 	FVector HitLocation;
// 	if (MyInstigator)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("instigator exisit."));
// 		USpringArmComponent* SpringArmComp = Cast<USpringArmComponent>(MyInstigator->GetComponentByClass(USpringArmComponent::StaticClass()));
// 		FVector SpringArmForwardVector = SpringArmComp->GetForwardVector();
// 		FVector End = SpringArmForwardVector * 1000;
// 
// 		FCollisionObjectQueryParams ObjectQueryParams;
// 		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);  // 世界中动态的物体才能触发
// 
// 		FHitResult Hit;
// 		bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, SpringArmForwardVector, End, ObjectQueryParams);
// 		
// 		FColor LineColor = bHit ? FColor::Green : FColor::Red;
// 		if (bHit)
// 		{
// 			HitLocation = Hit.ImpactPoint;
// 		}
// 		else {
// 			HitLocation = End;
// 		}
// 		DrawDebugLine(GetWorld(), SpringArmForwardVector, End,LineColor, false, 2.0f, 0, 2.0f);
// 		
// 	}
// 	return HitLocation - this->GetActorLocation();
// 
// }
// 
// void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (OtherActor && OtherActor != GetInstigator())
// 	{
// 		USAttributeComponent* AttribteComp = Cast<USAttributeComponent>( OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
// 		if(AttribteComp)
// 		{
// 			AttribteComp->ApplyHealthChange(-20.0f);
// 
// 			Destroy();
// 		}
// 	}
// }
// 
// 
// 
// // Called when the game starts or when spawned
// void ASMagicProjectile::BeginPlay()
// {
// 	Super::BeginPlay();
// 	
// }
// 
// // Called every frame
// void ASMagicProjectile::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// 
// }

