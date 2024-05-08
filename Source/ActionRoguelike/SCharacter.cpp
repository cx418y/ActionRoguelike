// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SActionComponent.h"




// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true; 
	SpringArmComp->SetupAttachment(RootComponent);
	

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	TimeToHitParamName = "TimeToHit";

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using SCharacter."));
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASCharacter::Dash);
	PlayerInputComponent->BindAction("BlackHole", IE_Pressed, this, &ASCharacter::BlackHoleAttack);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASCharacter::SprintStop);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

}

void ASCharacter::MoveForward(float Value)
{
	//if ((Controller != nullptr) && (Value != 0.0f))
	//{
	//	// find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	// get forward vector
	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//	AddMovementInput(Direction, Value);
	//}
	// 
	// AddMovementInput(GetActorForwardVector(), Value);
// 	
// 	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
// 	AddMovementInput(Direction, Value);

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);


}

void ASCharacter::MoveRight(float Value)
{
	// AddMovementInput(GetActorRightVector(), Value);

// 	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
// 	AddMovementInput(Direction, Value);

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

//void ASCharacter::PrimaryAttack()
//{
//
//	// PlayAnimMontage(AttackAnim);
//	StartAttackEffects();
//
//	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, AttackAnimDelay);
//
//}


//void ASCharacter::PrimaryAttack_TimeElapsed()
//{
//	SpawnProjectile(ProjectileClass);

// 	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
// 
// 	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
// 
// 	FActorSpawnParameters SpawnParams;
// 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 	SpawnParams.Instigator = this;
// 
// 	// USpringArmComponent* SpringArmComp = Cast<USpringArmComponent>(MyInstigator->GetComponentByClass(USpringArmComponent::StaticClass()));
// 	FVector CameraForwardVector = CameraComp->GetComponentLocation();
// 	FVector End = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);;
// 
// 	FCollisionObjectQueryParams ObjectQueryParams;
// 	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);  // 世界中动态的物体才能触发
// 	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
// 	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
// 
// 	FHitResult Hit;
// 	bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, CameraForwardVector, End, ObjectQueryParams);
// 
// 	FColor LineColor = bHit ? FColor::Green : FColor::Red;
// 	FVector HitLocation;
// 	
// 	if (bHit)
// 	{
// 		HitLocation = Hit.ImpactPoint;
// 	}
// 	else {
// 		HitLocation = End;
// 	}
// 	UE_LOG(LogTemp, Log, TEXT("ISHit: %d "), bHit);
// 	DrawDebugLine(GetWorld(), CameraForwardVector, End, LineColor, false, 2.0f, 0, 2.0f);
// 
// 	FRotator Rotation = (FRotationMatrix::MakeFromX(HitLocation - HandLocation)).Rotator();
// 	
// 
// 	GetWorld()->SpawnActor<AActor>(ProjectileClass, HandLocation, Rotation, SpawnParams);

//}

//void ASCharacter::Dash()
//{
//	// PlayAnimMontage(AttackAnim);
//	StartAttackEffects();
//
//	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ASCharacter::Dash_TimeElapsed, AttackAnimDelay);
//}


//void ASCharacter::Dash_TimeElapsed()
//{
//	SpawnProjectile(DashProjectileClass);
//}

//void ASCharacter::BlackHole()
//{
//	PlayAnimMontage(AttackAnim);
//
//	GetWorldTimerManager().SetTimer(TimerHandle_BlackHole, this, &ASCharacter::BlackHole_TimeElapsed, AttackAnimDelay);
//}
//
//void ASCharacter::BlackHole_TimeElapsed()
//{
//	SpawnProjectile(BlackHoleProjectileClass);
//}
//
//void ASCharacter::StartAttackEffects()
//{
//	PlayAnimMontage(AttackAnim);
//
//	UGameplayStatics::SpawnEmitterAttached(CastingEffect, GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
//
//}

//void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
//{
//	if (ensureAlways(ClassToSpawn))
//	{
//		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
//
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//		SpawnParams.Instigator = this;
//
//		FCollisionShape Shape;
//		Shape.SetSphere(20.0f);
//
//		// Ignore Player
//		FCollisionQueryParams Params;
//		Params.AddIgnoredActor(this);
//
//		FCollisionObjectQueryParams ObjParams;
//		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
//		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
//		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
//
//		FVector TraceStart = CameraComp->GetComponentLocation();
//
//		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
//		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);
//
//		FHitResult Hit;
//		// returns true if we got to a blocking hit
//		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
//		{
//			// Overwrite trace end with impact point in world
//			TraceEnd = Hit.ImpactPoint;
//		}
//
//		// find new direction/rotation from Hand pointing to impact point in world.
//		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
//
//		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
//		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
//	}
//}

void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}


void ASCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}



void ASCharacter::BlackHoleAttack()
{
	ActionComp->StartActionByName(this, "Blackhole");
}


void ASCharacter::Dash()
{
	ActionComp->StartActionByName(this, "Dash");
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

  
void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{

	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
    AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}
