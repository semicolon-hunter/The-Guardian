// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Chasing,
	Attacking,
	Dead
};

UCLASS()
class THEGUARDIAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CurrentHealth = 0.0f;
	float TimeSinceLastAttack = 0.0f;

	UPROPERTY()
	class APawn* TargetPawn = nullptr;

	void UpdateState();
	void DoAttack();
	bool CanSeeTarget() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Enemy|Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy|AI")
	float SightRadius = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy|AI")
	float AttackRadius = 150.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy|AI")
	float AttackCooldown = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Enemy|Combat")
	float AttackDamage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|State")
	EEnemyState CurrentState = EEnemyState::Idle;

	UFUNCTION(BlueprintCallable, Category = "Enemy|Combat")
	void ApplyDamage(float DamageAmount);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
