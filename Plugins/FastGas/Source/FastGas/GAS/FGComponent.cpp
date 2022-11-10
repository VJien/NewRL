// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/FGComponent.h"
#include "FGGameplayAbility.h"
#include "Core/FGCharacter.h"
#include "Data/FGTypesCore.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Lib/FGBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"


void UFGComponent::RPC_Ser_AddAbility_Implementation(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 level)
{
	if (!AbilityClass)
	{
		UE_LOG(FGLog, Warning, TEXT("AddNewAbility  Fail! [no Ability Class]"))
		return ;
	}
	if (AbilitySpecs.Num()>0)
	{
		if (AbilitySpecs.Find(AbilityClass) != nullptr)
		{
			UE_LOG(FGLog, Warning, TEXT("AddNewAbility  Fail! [ Has Repeat Ability]"))
			return;
		}
	}
	FGameplayAbilitySpec spec = FGameplayAbilitySpec(AbilityClass, level, static_cast<int32>(AbilityClass.GetDefaultObject()->InputID), GetOwnerActor());
	GiveAbility(spec);
	AbilitySpecs.Add(AbilityClass.GetDefaultObject()->AbilityName,  this->FindAbilitySpecFromClass(AbilityClass));

}

bool UFGComponent::RPC_Ser_AddAbility_Validate(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 level)
{
	return true;
}

void UFGComponent::RPC_Ser_RemoveAbilityByClass_Implementation(TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	FGameplayAbilitySpec* spec = FindAbilitySpecFromClass(AbilityClass);
	if (spec)
	{
		this->ClearAbility(spec->Handle);
		AbilitySpecs.Remove(AbilityClass);
		return;
	}
	UE_LOG(FGLog, Warning, TEXT("RemoveAbilityByClass Failed!! Do not has this ability"))
}

bool UFGComponent::RPC_Ser_RemoveAbilityByClass_Validate(TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	return true;
}

void UFGComponent::RPC_Ser_RemoveAbilityByName_Implementation(const FString& name)
{
	if (HasAbility(name))
	{
		FGameplayAbilitySpec* spec = AbilitySpecs.Find(name);
		ClearAbility(spec->Handle);
		AbilitySpecs.Remove(name);
		return;
	}
	UE_LOG(FGLog, Warning, TEXT("RemoveAbilityByClass Failed!! Do not has this ability"))
}

bool UFGComponent::RPC_Ser_RemoveAbilityByName_Validate(const FString& name)
{
	return true;
}

void UFGComponent::RPC_Ser_UpgradeAbilityByName_Implementation(const FString& name, int32 upLevel)
{
	if (AbilitySpecs.Find(name) != nullptr)
	{
		FGameplayAbilitySpec* spec = AbilitySpecs.Find(name);
		spec->Level += upLevel;
		this->MarkAbilitySpecDirty(*spec);
		return;
	}
	UE_LOG(FGLog, Warning, TEXT("UpgradeAbility Failed!! Do not has this ability"))
}

bool UFGComponent::RPC_Ser_UpgradeAbilityByName_Validate(const FString& name, int32 upLevel)
{
	return true;
}

void UFGComponent::RPC_Ser_UpgradeAbilityByClass_Implementation(TSubclassOf<UFGGameplayAbility> AbilityClass,
	int32 upLevel)
{
	if (auto Spec = FindAbilitySpecFromClass(AbilityClass))
	{
		Spec->Level += upLevel;
		this->MarkAbilitySpecDirty(*Spec);
		return;
	}
	UE_LOG(FGLog, Warning, TEXT("UpgradeAbility Failed!! Do not has this ability"))
}

bool UFGComponent::RPC_Ser_UpgradeAbilityByClass_Validate(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 upLevel)
{
	return true;
}


FFGGameplayAbilitySpec::FFGGameplayAbilitySpec(const FString& Name, UGameplayAbility* InAbility, int32 InLevel)
{
	Spec = FGameplayAbilitySpec(InAbility, InLevel);
	AbilityName = Name;
}

void UFGComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGComponent, AbilitySpecs);
}

bool UFGComponent::AddNewAbility(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 level)
{
	if (GetOwnerRole() >= ROLE_AutonomousProxy)
	{
		RPC_Ser_AddAbility(AbilityClass, level);
		return true;
	}
	return false;
}

bool UFGComponent::RemoveAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	if (GetOwnerRole() >= ROLE_AutonomousProxy)
	{
		RPC_Ser_RemoveAbilityByClass(AbilityClass);
		return true;
	}
	return false;
}

bool UFGComponent::RemoveAbilityByName(const FString& name)
{
	if (GetOwnerRole() >= ROLE_AutonomousProxy)
	{
		RPC_Ser_RemoveAbilityByName(name);
		return true;
	}
	return false;
}

bool UFGComponent::UpgradeAbilityByName(const FString& name, int32 upLevel)
{
	if (GetOwnerRole() >= ROLE_AutonomousProxy)
	{
		RPC_Ser_UpgradeAbilityByName(name, upLevel);
		return true;
	}
	return false;
}

bool UFGComponent::UpgradeAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 upLevel)
{
	if (GetOwnerRole() >= ROLE_AutonomousProxy)
	{
		RPC_Ser_UpgradeAbilityByClass(AbilityClass, upLevel);
		return true;
	}
	return false;
}

int32 UFGComponent::GetAbilityLevelByName(const FString& name)
{
	const auto Spec = AbilitySpecs.Find(name) ;
	return Spec ==nullptr ?-1 : Spec->Level;
}

int32 UFGComponent::GetAbilityLevelByClass(TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	FGameplayAbilitySpec* spec = FindAbilitySpecFromClass(AbilityClass);
	if (spec)
	{
		return spec->Level;
	}
	return -1;
}

UFGGameplayAbility* UFGComponent::GetAbilityObjectByName(const FString& name)
{
	const auto Spec = AbilitySpecs.Find(name);
	return Cast<UFGGameplayAbility>(Spec->Ability);

}

bool UFGComponent::HasAbility(const FString& name)
{
	return AbilitySpecs.Find(name) != nullptr;
}

bool UFGComponent::HasAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	FGameplayAbilitySpec* spec = FindAbilitySpecFromClass(AbilityClass);
	return spec != nullptr;
}

void UFGComponent::BP_ExecuteGameplayCue(const FGameplayTag& GameplayCueTag,
	const FGameplayCueParameters& GameplayCueParameters)
{
	ExecuteGameplayCue(GameplayCueTag, GameplayCueParameters);
}

void UFGComponent::BP_RemoveGameplayCue(const FGameplayTag& GameplayCueTag)
{
	RemoveGameplayCue(GameplayCueTag);
}

void UFGComponent::BP_AddGameplayCue(const FGameplayTag& GameplayCueTag,
	const FGameplayCueParameters& GameplayCueParameters)
{
	AddGameplayCue(GameplayCueTag, GameplayCueParameters);
}

FGameplayTagContainer UFGComponent::GetAllTags()
{
	FGameplayTagContainer out;
	GetOwnedGameplayTags(out);
	return out;
}

void UFGComponent::OnRep_AbilitySpecMap(const FFGGameplayAbilitySpecContainer& Old)
{
}



void UFGComponent::PostDamage(UFGComponent* SourceASC, float Damage, FHitResult HitResult)
{
	if (bDebugLog)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 收到 %s 的 攻击, 伤害 = %f"), *GetAvatarActor()->GetName(), *SourceASC->GetAvatarActor()->GetName(),Damage);
	}
	AFGCharacter* role = Cast<AFGCharacter>(GetAvatarActor());
	if (role)
	{
		role->PostDamage(SourceASC, Damage, HitResult);
		if (role->GetHealth_Current() <= Damage)
		{
			role->PostDeath(SourceASC, Damage,HitResult);
		}
	}
}

void UFGComponent::PreDodge(UFGComponent* SourceASC, const FFGDamageParameter& Parameter)
{
}

void UFGComponent::PreBlock(UFGComponent* SourceASC, const FFGDamageParameter& Parameter)
{
}

void UFGComponent::PreDamage(UFGComponent* SourceASC, const FFGDamageParameter& Parameter)
{
	if (bDebugLog)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 收到 %s 的 [%s] 攻击, 税前伤害 = %f, 税后= %f"), *GetAvatarActor()->GetName(), *SourceASC->GetAvatarActor()->GetName(),
			*UFGBlueprintLibrary::DamageTypeToString(Parameter.Type), Parameter.UnmitigatedDamage, Parameter.MitigatedDamage);
	}
	AFGCharacter* role = Cast<AFGCharacter>(GetAvatarActor());
	if (role)
	{
		role->PreDamage(SourceASC, Parameter);
		if (role->GetHealth_Current() <= Parameter.MitigatedDamage)
		{
			role->PreDeath(SourceASC, Parameter);
		}
	}
	OnPreDamage.Broadcast(SourceASC, Parameter);
	
}


