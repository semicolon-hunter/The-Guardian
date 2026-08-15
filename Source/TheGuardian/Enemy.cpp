// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	// Пока просто берём игрока как цель.
    // Позже это лучше заменить на UAIPerceptionComponent.
	TargetPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	UE_LOG(LogTemp, Warning, TEXT("[%s] TargetPawn: %s | Controller: %s"),
		*GetName(),
		TargetPawn ? *TargetPawn->GetName() : TEXT("NULL"),
		GetController() ? *GetController()->GetName() : TEXT("NULL"));
}

void AEnemy::UpdateState()
{
	if (!TargetPawn)
	{
		CurrentState = EEnemyState::Idle;
		return;
	}

	const float Dist = FVector::Dist(GetActorLocation(), TargetPawn->GetActorLocation());

	if (Dist <= AttackRadius)
	{
		CurrentState = EEnemyState::Attacking;
		DoAttack();
	}
	else if (CanSeeTarget())
	{
		CurrentState = EEnemyState::Chasing;

		AController* RawController = GetController();
		UE_LOG(LogTemp, Warning, TEXT("[%s] RawController=%s IsValid=%d Class=%s"),
			*GetName(),
			RawController ? *RawController->GetName() : TEXT("NULL"),
			IsValid(RawController),
			RawController ? *RawController->GetClass()->GetName() : TEXT("N/A"));

		if (AAIController* AICon = Cast<AAIController>(RawController))
		{
			EPathFollowingRequestResult::Type Result = AICon->MoveToActor(TargetPawn, AttackRadius * 0.8f);
			UE_LOG(LogTemp, Warning, TEXT("[%s] MoveToActor -> %d"), *GetName(), (int32)Result);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[%s] No AIController!"), *GetName());
		}
	}
}

void AEnemy::DoAttack()
{
	if (TimeSinceLastAttack < AttackCooldown)
	{
		return;
	}

	TimeSinceLastAttack = 0.0f;
	UE_LOG(LogTemp, Log, TEXT("%s attacks target!"), *GetName());

	// Тут будет UGameplayStatics::ApplyDamage(TargetPawn, AttackDamage, ...)
	// либо вызов интерфейса урона у цели.
}

bool AEnemy::CanSeeTarget() const
{
	if (!TargetPawn)
	{
		return false;
	}

	const float Dist = FVector::Dist(GetActorLocation(), TargetPawn->GetActorLocation());
	return Dist <= SightRadius ;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == EEnemyState::Dead)
	{
		return;
	}

	TimeSinceLastAttack += DeltaTime;
	UpdateState();
}

void AEnemy::ApplyDamage(float DamageAmount)
{
	if (CurrentState == EEnemyState::Dead)
	{
		return;
	}

	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0.0f)
	{
		CurrentState = EEnemyState::Dead;
		// Проиграть анимацию смерти, отключить коллизию, задестроить через таймер и т.д.
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

