// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AEffectActor::AEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!TargetASC)return;
	FGameplayEffectContextHandle EffectContextHandle=TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,Level,EffectContextHandle);

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

// Called every frame
void AEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectActor::SetLevel(float InLevel)
{
	Level=InLevel;
}


