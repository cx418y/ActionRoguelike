// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(StaticMeshComp);

	StaticMeshComp->SetSimulatePhysics(true);  //物理模拟
	StaticMeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName); //碰撞预设

	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->Radius = 750.0f;			 // 爆炸范围
	RadialForceComp->ImpulseStrength = 700.0f; // 冲击力
	RadialForceComp->bImpulseVelChange = true; // 忽略质量大小；见UE中ForceComp的“冲量速度变更”


}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnActorHit);
}

void AExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImplise, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
	 
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive"));
}


