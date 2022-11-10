// Fill out your copyright notice in the Description page of Project Settings.


#include "FGAbilityItem.h"

#include "GAS/FGAttributeSetBase.h"
#include "GAS/FGComponent.h"


AFGAbilityItem::AFGAbilityItem(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UFGComponent>(TEXT("AbilityComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
    
    AttributeSet = CreateDefaultSubobject<UFGAttributeSetBase>("AttributeSet");

}

UAbilitySystemComponent* AFGAbilityItem::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFGAbilityItem::InitWithOutPawn_Implementation()
{
	if (bHasInit)
	{
		return;
	}
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		for (auto ga : DefaultAbilities)
		{
			AbilitySystemComponent->AddNewAbility(ga, 1);
		}
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		for (auto ge : StartupEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ge, GetLevel() , EffectContextHandle);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
			}
		}
		
	}
	bHasInit = true;
}


void AFGAbilityItem::Init_Implementation(AFGCharacter* InOwnerPawn)
{
	if (!InOwnerPawn || bHasInit)
	{
		return;
	}
	OwnerPawn = InOwnerPawn;
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, InOwnerPawn);
		
		for (auto ga : DefaultAbilities)
		{
			AbilitySystemComponent->AddNewAbility(ga, 1);
		}
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		for (auto ge : StartupEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ge, GetLevel() , EffectContextHandle);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
			}
		}
		
	}
	bHasInit = true;
}


void AFGAbilityItem::Reset_Implementation()
{
	OwnerPawn = nullptr;
	
	for (auto ga : DefaultAbilities)
	{
		AbilitySystemComponent->RemoveAbilityByClass(ga);
	}
	//重制所有属性
	AttributeSet->SetAttack_Final(0);
	AttributeSet->SetArmor_Final(0);
	bHasInit = false;
}

int32 AFGAbilityItem::GetLevel() const
{
	return AttributeSet? AttributeSet->GetLevel(): -1;
}

UFGComponent* AFGAbilityItem::BP_GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

