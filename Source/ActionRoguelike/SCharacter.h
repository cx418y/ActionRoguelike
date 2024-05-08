// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"



class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;
class USpringArmComponent;
class USAttributeComponent;
class USActionComponent;
UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	//UPROPERTY(VisibleAnywhere, Category = "Effects")
	//FName HandSocketName;

	//UPROPERTY(EditAnywhere, Category = "Attack")
	//TSubclassOf<AActor> ProjectileClass;

	//UPROPERTY(EditAnywhere, Category = "Attack")
	//TSubclassOf<AActor> DashProjectileClass;

	//UPROPERTY(EditAnywhere, Category = "Attack")
	//TSubclassOf<AActor> BlackHoleProjectileClass;

	//UPROPERTY(EditAnywhere, Category="Attack")
	//UAnimMontage* AttackAnim;

	///* Particle System played during attack animation */
	//UPROPERTY(EditAnywhere, Category = "Attack")
	//UParticleSystem* CastingEffect;

	//FTimerHandle TimerHandle_PrimaryAttack;
	//FTimerHandle TimerHandle_Dash;
	//FTimerHandle TimerHandle_BlackHole;

	//UPROPERTY(EditDefaultsOnly, Category = "Attack")
	//float AttackAnimDelay;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;


	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;


	UPROPERTY(VisibleAnywhere, Category = "Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void SprintStart();

	void SprintStop();

	void PrimaryAttack();

	void BlackHoleAttack();

	void Dash();

	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

};
