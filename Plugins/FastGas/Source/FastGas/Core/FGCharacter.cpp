// Fill out your copyright notice in the Description page of Project Settings.


#include "FastGas/Core/FGCharacter.h"

#include "Data/FGTypesCore.h"
#include "GAS/FGComponent.h"
#include "GAS/FGAttributeSetBase.h"

// Sets default values
AFGCharacter::AFGCharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UFGComponent>(TEXT("AbilityComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UFGAttributeSetBase>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void AFGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	InitAttributes();
	AddCharacterStartupAbilities();
	AddStartUpEffects();
}

UAbilitySystemComponent* AFGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFGCharacter::InitAttributes()
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(FGLog, Warning, TEXT("InitAttributes failed [no ASC]  !!"));
		return;
	}
	if (!DefaultAttributeEffect)
	{
		UE_LOG(FGLog, Warning, TEXT("InitAttributes failed [no DefaultAttributeEffect]  !!"));
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, GetLevel(), EffectContextHandle);
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
	}
}

void AFGCharacter::AddCharacterStartupAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bHasGiveCharacterAbilities)
	{
		return;
	}
	for (auto ga : CharacterAbilities)
	{
		AbilitySystemComponent->AddNewAbility(ga, 1);
	}
	AbilitySystemComponent->bHasGiveCharacterAbilities = true;
}

void AFGCharacter::AddStartUpEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bHasApplyStartupEffects)
	{
		UE_LOG(FGLog, Warning, TEXT("Add Startup Effects failed"));
		return;
	}
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	for (auto ge : StartupEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ge, GetLevel(), EffectContextHandle);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
		}
	}
	AbilitySystemComponent->bHasApplyStartupEffects = true;

	
}

int32 AFGCharacter::GetLevel() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetLevel();
	}
	return 1;
}

float AFGCharacter::GetHealth_Current() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHealth_Current();
	}
	return 0;
}

float AFGCharacter::GetMaxHealth() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHealth_Max_Final();
	}
	return 0;
}

float AFGCharacter::GetShield_Current() const
{
	if (GetAttribute())
	{
		return GetAttribute()->GetShield_Current();
	}
	return 0;
}

float AFGCharacter::GetMaxShield() const
{
	if (GetAttribute())
	{
		return GetAttribute()->GetShield_Max_Final();
	}
	return 0;
}

bool AFGCharacter::IsAlive() const
{
	return GetHealth_Current() > 0;
}

UFGAttributeSetBase* AFGCharacter::BP_GetAttribute()
{
	return Cast<UFGAttributeSetBase>(AttributeSet);
}

const UFGAttributeSetBase* AFGCharacter::GetAttribute() const
{
	return  Cast<UFGAttributeSetBase>(AttributeSet);
}

