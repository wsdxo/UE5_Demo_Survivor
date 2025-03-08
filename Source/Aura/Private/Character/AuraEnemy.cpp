// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "Character/AuraCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"



AAuraEnemy::AAuraEnemy()
{
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0,0,1));
	
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	// GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	// GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAuraEnemy::OnCollisionBegin);
	check(EnemyControllerClass);
	Controller=GetWorld()->SpawnActor<AAIController>(EnemyControllerClass);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
}

void AAuraEnemy::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if(PlayerPawn && GetCharacterMovement()) {
		
		FVector DirectionToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
		FVector Direction=DirectionToPlayer.GetSafeNormal();
		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), 
			GetActorLocation() + Direction * 100.f, 10.f, FColor::Red);
		GetMovementComponent()->AddInputVector(Direction);
	}
	// 在Tick中添加速度打印
	FVector CurrentVelocity = GetVelocity();
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), CurrentVelocity.Size());
}

void AAuraEnemy::OnCollisionBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("碰撞"));
	if(OtherActor&&OtherActor->IsA(AAuraCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("与玩家碰撞"));
		Cast<AAuraCharacter>(PlayerPawn)->TakeDamage(Attack);
		Destroy();
	}
}
