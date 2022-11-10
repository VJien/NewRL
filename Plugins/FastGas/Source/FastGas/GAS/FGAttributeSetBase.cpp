// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/FGAttributeSetBase.h"

#include "GameplayEffectExtension.h"
#include "Core/FGCharacter.h"
#include "Net/UnrealNetwork.h"

UFGAttributeSetBase::UFGAttributeSetBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	
	
}

UFGAttributeSetBase::~UFGAttributeSetBase()
{
}

void UFGAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGAttributeSetBase, Health_Current);
	DOREPLIFETIME(UFGAttributeSetBase, Health_Max_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Health_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Health_Max_BonusPercent);
	DOREPLIFETIME(UFGAttributeSetBase, Health_RegenRate_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Health_RegenRate_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Health_RegenRate_BonusPercent);
	
	DOREPLIFETIME(UFGAttributeSetBase, Level);

	DOREPLIFETIME(UFGAttributeSetBase, Shield_Current);
	DOREPLIFETIME(UFGAttributeSetBase, Shield_Max_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Shield_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Shield_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Shield_Max_Base);

	DOREPLIFETIME(UFGAttributeSetBase, Mana_Current);
	DOREPLIFETIME(UFGAttributeSetBase, Mana_Max_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Mana_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Mana_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Mana_Max_Base);

	DOREPLIFETIME(UFGAttributeSetBase, Energy_Current);
	DOREPLIFETIME(UFGAttributeSetBase, Energy_Max_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Energy_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Energy_Max_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Energy_Max_Base);

	
	
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Default);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Default_Max);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Default_PerMag);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Special_A);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Special_A_Max);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Special_A_PerMag);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Special_B);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Special_B_Max);
	DOREPLIFETIME(UFGAttributeSetBase, BulletNum_Special_B_PerMag);

	DOREPLIFETIME(UFGAttributeSetBase, Health_Steal_Constant);
	DOREPLIFETIME(UFGAttributeSetBase, Health_Steal_Percent);
	DOREPLIFETIME(UFGAttributeSetBase, Mana_Steal_Constant);
	DOREPLIFETIME(UFGAttributeSetBase, Mana_Steal_Percent);
	
	DOREPLIFETIME(UFGAttributeSetBase, Attack_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_BonusPercent);
	DOREPLIFETIME(UFGAttributeSetBase, AttackSpeed_Final);
	DOREPLIFETIME(UFGAttributeSetBase, AttackSpeed_Base);
	DOREPLIFETIME(UFGAttributeSetBase, AttackSpeed_BonusPercent);
	DOREPLIFETIME(UFGAttributeSetBase, CritPro_Final);
	DOREPLIFETIME(UFGAttributeSetBase, CritPro_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, CritPro_BonusPercent);
	DOREPLIFETIME(UFGAttributeSetBase, CritMul_Final);
	DOREPLIFETIME(UFGAttributeSetBase, CritMul_BonusConstant);

	DOREPLIFETIME(UFGAttributeSetBase, MagicPower_Final);
	DOREPLIFETIME(UFGAttributeSetBase, MagicPower_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, MagicPower_BonusPercent);
	DOREPLIFETIME(UFGAttributeSetBase, MagicBonus_Fire);
	DOREPLIFETIME(UFGAttributeSetBase, MagicBonus_Ice);
	DOREPLIFETIME(UFGAttributeSetBase, MagicBonus_Dark);
	DOREPLIFETIME(UFGAttributeSetBase, MagicBonus_Nature);
	DOREPLIFETIME(UFGAttributeSetBase, MagicBonus_Arcane);


	
	DOREPLIFETIME(UFGAttributeSetBase, Armor_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Armor_Base);
	DOREPLIFETIME(UFGAttributeSetBase, Armor_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, Armor_BonusPercent);
	DOREPLIFETIME(UFGAttributeSetBase, DamageReduce);
	DOREPLIFETIME(UFGAttributeSetBase, Block);
	DOREPLIFETIME(UFGAttributeSetBase, Dodge_Final);
	DOREPLIFETIME(UFGAttributeSetBase, Dodge_Base);
	DOREPLIFETIME(UFGAttributeSetBase, Dodge_BonusConstant);


	DOREPLIFETIME(UFGAttributeSetBase, XP);
	DOREPLIFETIME(UFGAttributeSetBase, Level);
	DOREPLIFETIME(UFGAttributeSetBase, XPBonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, CareerLevel);
	DOREPLIFETIME(UFGAttributeSetBase, CharacterLevel);
	DOREPLIFETIME(UFGAttributeSetBase, SkillPoint);
	DOREPLIFETIME(UFGAttributeSetBase, TalentlPoint);
	

	DOREPLIFETIME(UFGAttributeSetBase, Resistance_Fire);
	DOREPLIFETIME(UFGAttributeSetBase, Resistance_Ice);
	DOREPLIFETIME(UFGAttributeSetBase, Resistance_Dark);
	DOREPLIFETIME(UFGAttributeSetBase, Resistance_Nature);
	DOREPLIFETIME(UFGAttributeSetBase, Resistance_Arcane);

	DOREPLIFETIME(UFGAttributeSetBase, MoveSpeed_Final);
	DOREPLIFETIME(UFGAttributeSetBase, MoveSpeed_Base);
	DOREPLIFETIME(UFGAttributeSetBase, MoveSpeed_BonusConstant);
	DOREPLIFETIME(UFGAttributeSetBase, MoveSpeed_BonusPercent);

	DOREPLIFETIME(UFGAttributeSetBase, Attack_Physics);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_Fire);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_Ice);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_Dark);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_Nature);
	DOREPLIFETIME(UFGAttributeSetBase, Attack_Arcane);
	
	DOREPLIFETIME(UFGAttributeSetBase, Damage_Physics);
	DOREPLIFETIME(UFGAttributeSetBase, Damage_Fire);
	DOREPLIFETIME(UFGAttributeSetBase, Damage_Ice);
	DOREPLIFETIME(UFGAttributeSetBase, Damage_Dark);
	DOREPLIFETIME(UFGAttributeSetBase, Damage_Nature);
	DOREPLIFETIME(UFGAttributeSetBase, Damage_Arcane);
}

void UFGAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealth_Max_FinalAttribute())
	{
		AdjustAttributeForMaxChange(Health_Current, Health_Max_Final, NewValue, GetHealth_CurrentAttribute());
	}
}

void UFGAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);




	
	UAttributeSet::PostGameplayEffectExecute(Data);
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UFGComponent* SourceASC = Cast<UFGComponent>(Context.GetOriginalInstigatorAbilitySystemComponent());
	UFGComponent* ASC = Cast<UFGComponent>(GetOwningAbilitySystemComponent());
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AFGCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AFGCharacter>(TargetActor);
	}
		
	HandleAttributeChanged(Data.EvaluatedData.Attribute);
	ClampAttributes(Data.EvaluatedData.Attribute);

	if (IsAnyDamage(Data.EvaluatedData.Attribute))
	{
		if (ASC)
		{
			FHitResult Hit;
			if (Data.EffectSpec.GetContext().IsValid())
			{
				auto pHit = Data.EffectSpec.GetContext().GetHitResult();
				if (pHit)
				{
					Hit = *pHit;
				}
				
			}
			ASC->PostDamage(SourceASC, Data.EvaluatedData.Magnitude, Hit);

		}
		//处理伤害
		HandleDamage(Data.EvaluatedData.Attribute, TargetCharacter);
	
	}

	BroadcastValueChanged(Data.EvaluatedData.Attribute);
}

FOnAttributeChangedMulDly& UFGAttributeSetBase::GetGameplayAttributeValueChangeDelegate(FGameplayAttribute Attribute)
{
	return AttributeValueChangeDelegates.FindOrAdd(Attribute);
}

void UFGAttributeSetBase::BroadcastValueChanged(FGameplayAttribute Attribute)
{
	if (FOnAttributeChangedMulDly* Delegate = AttributeValueChangeDelegates.Find(Attribute))
	{
		Delegate->Broadcast(Attribute, Attribute.GetGameplayAttributeData(this)->GetCurrentValue(), Attribute.GetGameplayAttributeData(this)->GetBaseValue());
	}
}

void UFGAttributeSetBase::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// 更改当前值以保持 Cur / Max 的百分比
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UFGAttributeSetBase::HandleAttributeChanged(FGameplayAttribute Attribute)
{
	if (ShouldRecalculateHealth(Attribute))
	{
		SetHealth_Max_Final(FMath::Clamp(
			(GetHealth_Max_Base() + GetHealth_Max_BonusConstant())*(1 + GetHealth_Max_BonusPercent()), 0.0f, MAX_VALUE));
	}
	else if (ShouldRecalculateHealthRegenRate(Attribute))
	{
		SetHealth_RegenRate_Final((GetHealth_RegenRate_Base() + GetHealth_RegenRate_BonusConstant())*(1 + GetHealth_RegenRate_BonusPercent()));
	}
	else if (ShouldRecalculateSheild(Attribute))
	{
		SetShield_Max_Final(FMath::Clamp(
			(GetShield_Max_Base() + GetShield_Max_BonusConstant()) * (1 + GetShield_Max_BonusPercent()), 0.0f, MAX_VALUE));
	}
	else if (ShouldRecalculateMana(Attribute))
	{
		SetMana_Max_Final(FMath::Clamp(
			(GetMana_Max_Base() + GetMana_Max_BonusConstant()) * (1 + GetMana_Max_BonusPercent()), 0.0f, MAX_VALUE));
	}
	else if (ShouldRecalculateEnergy(Attribute))
	{
		SetEnergy_Max_Final(FMath::Clamp(
			(GetEnergy_Max_Base() + GetEnergy_Max_BonusConstant()) * (1 + GetEnergy_Max_BonusPercent()), 0.0f, MAX_VALUE));
	}
	
	else if (ShouldRecalculateArmor(Attribute))
	{
		SetArmor_Final(((GetArmor_Base()+GetArmor_BonusConstant()) * (1 + GetArmor_BonusPercent())));
	}
	else if (ShouldRecalculateAttack(Attribute))
	{
		SetAttack_Final(FMath::Clamp((GetAttack_Base()+GetAttack_BonusConstant()) * (1 + GetAttack_BonusPercent()), 0.f, MAX_VALUE));
	}
	else if (ShouldRecalculateAttackSpeed(Attribute))
	{
		SetAttackSpeed_Final(FMath::Clamp(GetAttackSpeed_Base() * (1 + GetAttackSpeed_BonusPercent()), 0.1f, MAX_ATTACK_SPEED));
	}
	else if (ShouldRecalculateCritPro(Attribute))
	{
		SetCritPro_Final(
			FMath::Clamp((GetCritPro_BonusConstant() + DEF_CRIT_PRO) * (1 + GetCritPro_BonusPercent()), 0.0f, 1.0f));
	}
	else if (ShouldRecalculateCritMul(Attribute))
	{
		SetCritMul_Final(FMath::Clamp((1.5f + GetCritMul_BonusConstant()), 0.0f, DEF_CRIP_MUL_MAX));
	}
	else if (ShouldRecalculateMoveSpeed(Attribute))
	{
		SetMoveSpeed_Final(FMath::Clamp((GetMoveSpeed_Base() + GetMoveSpeed_BonusConstant()) * (1 + GetMoveSpeed_BonusPercent()), 0.f, MAX_MOVE_SPEED));
	}
	else if (ShouldRecalculateDodge(Attribute))
	{
		SetDodge_Final(FMath::Clamp(GetDodge_Base() + GetDodge_BonusConstant(),0.f,1.f));
	}
	else if (ShouldRecalculateMagicPower(Attribute))
	{
		SetMagicPower_Final(FMath::Clamp((GetMagicPower_Base()+GetMagicPower_BonusConstant()) * (1 + GetMagicPower_BonusPercent()), 0.f, MAX_VALUE));
	}
}

bool UFGAttributeSetBase::ShouldRecalculateHealth(FGameplayAttribute Attribute) const
{
	return  Attribute == this->GetHealth_Max_BaseAttribute()
	|| Attribute == this->GetHealth_Max_BonusConstantAttribute()
		|| Attribute == GetHealth_Max_BonusPercentAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateHealthRegenRate(FGameplayAttribute Attribute) const
{
	return Attribute == GetHealth_RegenRate_BaseAttribute() || Attribute == GetHealth_RegenRate_BonusConstantAttribute() 
		|| Attribute == GetHealth_RegenRate_BonusPercentAttribute();
}

void UFGAttributeSetBase::ClampAttributes(FGameplayAttribute Attribute)
{
	if (Attribute == GetHealth_CurrentAttribute())
	{
		SetHealth_Current(FMath::Clamp(GetHealth_Current(), 0.0f, GetHealth_Max_Final()));
	}
	else if (Attribute == GetShield_CurrentAttribute())
	{
		SetShield_Current(FMath::Clamp(GetShield_Current(), 0.0f, GetShield_Max_Final()));
	}
	else if (Attribute == GetMana_CurrentAttribute())
	{
		SetMana_Current(FMath::Clamp(GetMana_Current(), 0.0f, GetMana_Max_Final()));
	}
	else if (Attribute == GetEnergy_CurrentAttribute())
	{
		SetEnergy_Current(FMath::Clamp(GetEnergy_Current(), 0.0f, GetEnergy_Max_Final()));
	}
	else if (Attribute == GetBulletNum_DefaultAttribute())
	{
		SetBulletNum_Default(FMath::Clamp(GetBulletNum_Default(),0.0f, GetBulletNum_Default_PerMag()));
	}
}


bool UFGAttributeSetBase::ShouldRecalculateSheild(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetShield_Max_BonusConstantAttribute()
		|| Attribute == this->GetShield_Max_BonusPercentAttribute()
		|| Attribute == GetShield_Max_BaseAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateMana(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetMana_Max_BonusConstantAttribute()
		|| Attribute == this->GetMana_Max_BonusPercentAttribute()
		|| Attribute == GetMana_Max_BaseAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateEnergy(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetEnergy_Max_BonusConstantAttribute()
		|| Attribute == this->GetEnergy_Max_BonusPercentAttribute()
		|| Attribute == GetEnergy_Max_BaseAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateAttack(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetAttack_BonusConstantAttribute()
	|| Attribute == this->GetAttack_BonusPercentAttribute()
	|| Attribute == GetAttack_BaseAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateAttackSpeed(FGameplayAttribute Attribute) const
{
	return Attribute == GetAttackSpeed_BaseAttribute() || Attribute == GetAttackSpeed_BonusPercentAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateMoveSpeed(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetMoveSpeed_BonusConstantAttribute()
	|| Attribute == this->GetMoveSpeed_BonusPercentAttribute()
	|| Attribute == GetMoveSpeed_BaseAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateCritPro(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetCritPro_BonusConstantAttribute()
	|| Attribute == this->GetCritPro_BonusPercentAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateCritMul(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetCritMul_BonusConstantAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateArmor(FGameplayAttribute Attribute) const
{
	return Attribute == GetArmor_BaseAttribute() || Attribute == GetArmor_BonusConstantAttribute()||
		Attribute == GetArmor_BonusPercentAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateDodge(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetDodge_BonusConstantAttribute() || Attribute == GetDodge_BaseAttribute();
}

bool UFGAttributeSetBase::ShouldRecalculateMagicPower(FGameplayAttribute Attribute) const
{
	return Attribute == this->GetMagicPower_BonusConstantAttribute()
	|| Attribute == this->GetMagicPower_BonusPercentAttribute()
	|| Attribute == GetMagicPower_BaseAttribute();
}


bool UFGAttributeSetBase::IsAnyDamage(FGameplayAttribute Attribute) const
{
	return Attribute == GetDamage_NatureAttribute() ||
		Attribute == GetDamage_FireAttribute() ||
		Attribute == GetDamage_PhysicsAttribute() ||
		Attribute == GetDamage_IceAttribute() ||
		Attribute == GetDamage_DarkAttribute();
}

void UFGAttributeSetBase::HandleDamage(const FGameplayAttribute& Attribute, AFGCharacter* TargetCharacter)
{
	DAMAGE_HANDLE(Attribute, TargetCharacter, Physics);
	DAMAGE_HANDLE(Attribute, TargetCharacter, Fire);
	DAMAGE_HANDLE(Attribute, TargetCharacter, Ice);
	DAMAGE_HANDLE(Attribute, TargetCharacter, Dark);
	DAMAGE_HANDLE(Attribute, TargetCharacter, Nature);
	DAMAGE_HANDLE(Attribute, TargetCharacter, Arcane);
}

void UFGAttributeSetBase::CalcShieldAndHealth(float Damage)
{
	if (Damage >0)
	{
		if (Damage > GetShield_Current())
		{
			float NewDamage =  Damage - GetShield_Current();
			SetShield_Current(0);
			SetHealth_Current(GetHealth_Current() - NewDamage);
		}
		else
		{
			SetShield_Current(GetShield_Current() - Damage);
		}
	}
}

TArray<FGameplayAttributeData> UFGAttributeSetBase::ListAllAttributeData()
{
	TArray<FGameplayAttributeData> Out;
	for (TFieldIterator<FProperty> IT(UFGAttributeSetBase::StaticClass()); IT; ++IT)
	{
		if (FStructProperty* StructProperty = CastField<FStructProperty>(*IT))
		{
			if (StructProperty->Struct->GetFName() == TEXT("GameplayAttributeData"))
			{
				FGameplayAttributeData* Data = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
				if (Data)
				{
					Out.Emplace(*Data);
				}
			}
		}
	}
	return Out;
}

TArray<FGameplayAttribute> UFGAttributeSetBase::ListAllAttribute()
{
	TArray<FGameplayAttribute> Out;
	for (TFieldIterator<FProperty> IT(UFGAttributeSetBase::StaticClass()); IT; ++IT)
	{
		if (FStructProperty* StructProperty = CastField<FStructProperty>(*IT))
		{
			if (StructProperty->Struct->GetFName() == TEXT("GameplayAttributeData"))
			{
				FGameplayAttributeData* Data = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
				FName Name = StructProperty->GetFName();
				
				FProperty* Prop = FindFieldChecked<FProperty>(UFGAttributeSetBase::StaticClass(), Name);
				
				if (Prop)
				{
					FGameplayAttribute Attribute(Prop);
					Out.Emplace(Attribute);
				}
			}
		}
	}
	return Out;
}


void UFGAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Current, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_Max(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Max_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_Max_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Max_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_Max_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Max_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_Max_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Max_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_RegenRate_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_RegenRate_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_RegenRate_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_RegenRate_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_RegenRate_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_RegenRate_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_RegenRate_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_RegenRate_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Level, OldValue);
}


void UFGAttributeSetBase::OnRep_Shield(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Shield_Current, OldValue);
}

void UFGAttributeSetBase::OnRep_Shield_Max_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Shield_Max_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Shield_Max_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Shield_Max_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Shield_Max_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Shield_Max_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Shield_Max_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Shield_Max_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Current, OldValue);
}

void UFGAttributeSetBase::OnRep_Mana_Max_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Max_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Mana_Max_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Max_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Mana_Max_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Max_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Mana_Max_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Max_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_Energy(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Energy_Current, OldValue);
}

void UFGAttributeSetBase::OnRep_Energy_Max_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Energy_Max_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Energy_Max_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Energy_Max_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Energy_Max_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Energy_Max_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Energy_Max_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Energy_Max_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Default(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Default, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Default_Max(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Default_Max, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Default_PerMag(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Default_PerMag, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Special_A_PerMag(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Special_A_PerMag, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Special_B_PerMag(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Special_B_PerMag, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Special_A(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Special_A, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Special_A_Max(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Special_A_Max, OldValue);
}
void UFGAttributeSetBase::OnRep_BulletNum_Special_B(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Special_B, OldValue);
}

void UFGAttributeSetBase::OnRep_BulletNum_Special_B_Max(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, BulletNum_Special_B_Max, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_Steal_Constant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Steal_Constant, OldValue);
}

void UFGAttributeSetBase::OnRep_Health_Steal_Percent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Health_Steal_Percent, OldValue);

}
void UFGAttributeSetBase::OnRep_Mana_Steal_Constant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Steal_Constant, OldValue);
}

void UFGAttributeSetBase::OnRep_Mana_Steal_Percent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Mana_Steal_Percent, OldValue);

}


void UFGAttributeSetBase::OnRep_Attack_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_AttackSpeed_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, AttackSpeed_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_AttackSpeed_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, AttackSpeed_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_AttackSpeed_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, AttackSpeed_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_CritPro_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CritPro_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_CritPro_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CritPro_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_CritPro_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CritPro_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_CritMul_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CritMul_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_CritMul_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CritMul_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicPower_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicPower_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicPower_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicPower_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicPower_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicPower_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicPower_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicPower_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicBonus_Fire(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicBonus_Fire, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicBonus_Ice(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicBonus_Ice, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicBonus_Dark(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicBonus_Dark, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicBonus_Nature(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicBonus_Nature, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicBonus_Arcane(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicBonus_Arcane, OldValue);
}

void UFGAttributeSetBase::OnRep_MagicBonus_All(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MagicBonus_All, OldValue);
}

void UFGAttributeSetBase::OnRep_Dodge_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Dodge_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_DodgeProBase(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Dodge_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Dodge_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Dodge_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Block(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Block, OldValue);
}

void UFGAttributeSetBase::OnRep_ControlReduce(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, ControlReduce, OldValue);
}

void UFGAttributeSetBase::OnRep_CharacterLevel(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CharacterLevel, OldValue);
}

void UFGAttributeSetBase::OnRep_CareerLevel(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, CareerLevel, OldValue);
}

void UFGAttributeSetBase::OnRep_SkillPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, SkillPoint, OldValue);
}

void UFGAttributeSetBase::OnRep_TalentlPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, TalentlPoint, OldValue);
}


void UFGAttributeSetBase::OnRep_Armor_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Armor_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_Armor_Base(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Armor_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_Armor_BonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Armor_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_Armor_BonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Armor_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_DamageReduce(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, DamageReduce, OldValue);
}


void UFGAttributeSetBase::OnRep_XP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, XP, OldValue);
}


void UFGAttributeSetBase::OnRep_XPBonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, XPBonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_XPBonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, XPBonusPercent, OldValue);
}



void UFGAttributeSetBase::OnRep_Resistance_Fire(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Resistance_Fire, OldValue);
}

void UFGAttributeSetBase::OnRep_Resistance_Ice(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Resistance_Ice, OldValue);
}

void UFGAttributeSetBase::OnRep_Resistance_Dark(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Resistance_Dark, OldValue);
}

void UFGAttributeSetBase::OnRep_Resistance_Nature(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Resistance_Nature, OldValue);
}

void UFGAttributeSetBase::OnRep_Resistance_Arcane(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Resistance_Arcane, OldValue);
}




void UFGAttributeSetBase::OnRep_MoveSpeed_Final(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MoveSpeed_Final, OldValue);
}

void UFGAttributeSetBase::OnRep_MoveSpeedBase(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MoveSpeed_Base, OldValue);
}

void UFGAttributeSetBase::OnRep_MoveSpeedBonusConstant(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MoveSpeed_BonusConstant, OldValue);
}

void UFGAttributeSetBase::OnRep_MoveSpeedBonusPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, MoveSpeed_BonusPercent, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_Physics(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Physics, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_Fire(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Fire, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_Ice(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Ice, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_Dark(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Dark, OldValue);
}

void UFGAttributeSetBase::OnRep_Attack_Nature(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Nature, OldValue);
}
void UFGAttributeSetBase::OnRep_Attack_Arcane(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Attack_Arcane, OldValue);
}


void UFGAttributeSetBase::OnRep_Damage_Physics(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Damage_Physics, OldValue);
}

void UFGAttributeSetBase::OnRep_Damage_Fire(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Damage_Fire, OldValue);
}

void UFGAttributeSetBase::OnRep_Damage_Ice(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Damage_Ice, OldValue);
}

void UFGAttributeSetBase::OnRep_Damage_Dark(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Damage_Dark, OldValue);
}

void UFGAttributeSetBase::OnRep_Damage_Nature(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Damage_Nature, OldValue);
}
void UFGAttributeSetBase::OnRep_Damage_Arcane(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFGAttributeSetBase, Damage_Arcane, OldValue);
}