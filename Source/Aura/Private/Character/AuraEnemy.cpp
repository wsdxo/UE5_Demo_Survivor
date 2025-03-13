// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
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
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Init ActorInfo
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAuraEnemy::OnCollisionBegin);
	check(EnemyControllerClass);
	Controller=GetWorld()->SpawnActor<AAIController>(EnemyControllerClass);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	AddCharacterAbilities();
	
}

void AAuraEnemy::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if(IsValid(PlayerPawn) && GetCharacterMovement())
	{
		FVector DirectionToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
		FVector Direction=DirectionToPlayer.GetSafeNormal();
		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), 
			GetActorLocation() + Direction * 100.f, 10.f, FColor::Red);
		GetMovementComponent()->AddInputVector(Direction);
	}
	FVector CurrentVelocity = GetVelocity();
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), CurrentVelocity.Size());
}

void AAuraEnemy::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!TargetASC)return;
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle=TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,Level,EffectContextHandle);

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


void AAuraEnemy::OnCollisionBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor&&OtherActor->IsA(AAuraCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("与玩家碰撞"));
		ApplyEffectToTarget(OtherActor,InstantGameplayEffect);
		//Destroy();
	}
}

void AAuraEnemy::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC=CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority())return;
	AuraASC->AddCharacterAbilities(StartUpAbilities);
}
