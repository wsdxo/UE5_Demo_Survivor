// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "Character/AuraCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// 构造函数修正
AAuraEnemy::AAuraEnemy()
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0,0,1));
    
	// 设置碰撞配置
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAuraEnemy::OnCollisionBegin);

	PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	
}

void AAuraEnemy::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if(PlayerPawn && GetCharacterMovement()) {
		
		FVector ToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
		FVector PlanarDirection = FVector(ToPlayer.X, ToPlayer.Y, 0).GetSafeNormal();
		// 添加调试绘图
		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), 
			GetActorLocation() + PlanarDirection * 100.f, 10.f, FColor::Red);
		GetCharacterMovement()->Velocity = PlanarDirection * MoveSpeed;
	}
	// 在Tick中添加速度打印
	FVector CurrentVelocity = GetVelocity();
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), CurrentVelocity.Size());
}

void AAuraEnemy::OnCollisionBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor&&OtherActor->IsA(AAuraCharacter::StaticClass()))
	{
		Destroy();
	}
}
