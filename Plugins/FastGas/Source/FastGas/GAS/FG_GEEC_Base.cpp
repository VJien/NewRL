// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_GEEC_Base.h"

#include "FGComponent.h"
#include "FGAttributeSetBase.h"
#include "Kismet/KismetMathLibrary.h"


struct FRLDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Final);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritPro_Final);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritMul_Final);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health_Steal_Constant);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health_Steal_Percent);

	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPower_Final);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicBonus_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicBonus_Ice);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicBonus_Dark);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicBonus_Nature);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicBonus_Arcane);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicBonus_All);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Physics);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Ice);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Dark);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Nature);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack_Arcane);


	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor_Final);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health_Current);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageReduce);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Dodge_Final);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Block);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ControlReduce);


	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Ice);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Dark);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Nature);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Arcane);


	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage_Physics);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage_Ice);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage_Dark);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage_Nature);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage_Arcane);

	FRLDamageStatics()
	{
		//攻击力在创建GE时捕获, 因为技能可能有弹道, 需要在发射的时候就捕获而不是击中的时候,
		//类似的其他有关发射者的属性都所需要此时捕获
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Final, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, CritPro_Final, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, CritMul_Final, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Health_Steal_Constant, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Health_Steal_Percent, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicPower_Final, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicBonus_Fire, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicBonus_Ice, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicBonus_Dark, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicBonus_Nature, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicBonus_Arcane, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, MagicBonus_All, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Physics, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Fire, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Ice, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Dark, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Nature, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Attack_Arcane, Source, true);


		//目标的防御在应用的时候捕获
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Armor_Final, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Health_Current, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, DamageReduce, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Dodge_Final, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Block, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, ControlReduce, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Resistance_Fire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Resistance_Ice, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Resistance_Dark, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Resistance_Nature, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Resistance_Arcane, Target, false);


		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Damage_Physics, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Damage_Fire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Damage_Ice, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Damage_Dark, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Damage_Nature, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFGAttributeSetBase, Damage_Arcane, Target, false);
	}
};


static const FRLDamageStatics& DamageStatics()
{
	static FRLDamageStatics DmgStatics;
	return DmgStatics;
}


UFG_GEEC_Base::UFG_GEEC_Base()
{
	RelevantAttributesToCapture.Add(DamageStatics().Attack_FinalDef);

	RelevantAttributesToCapture.Add(DamageStatics().CritPro_FinalDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritMul_FinalDef);
	RelevantAttributesToCapture.Add(DamageStatics().Health_Steal_ConstantDef);

	RelevantAttributesToCapture.Add(DamageStatics().Attack_PhysicsDef);
	RelevantAttributesToCapture.Add(DamageStatics().Attack_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Attack_IceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Attack_DarkDef);
	RelevantAttributesToCapture.Add(DamageStatics().Attack_NatureDef);
	RelevantAttributesToCapture.Add(DamageStatics().Attack_ArcaneDef);

	RelevantAttributesToCapture.Add(DamageStatics().MagicPower_FinalDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicBonus_AllDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicBonus_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicBonus_IceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicBonus_DarkDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicBonus_NatureDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicBonus_ArcaneDef);

	/***********************************************************************/

	RelevantAttributesToCapture.Add(DamageStatics().Armor_FinalDef);
	RelevantAttributesToCapture.Add(DamageStatics().Health_CurrentDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageReduceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Dodge_FinalDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockDef);
	RelevantAttributesToCapture.Add(DamageStatics().ControlReduceDef);

	RelevantAttributesToCapture.Add(DamageStatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_IceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_DarkDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_NatureDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ArcaneDef);


	RelevantAttributesToCapture.Add(DamageStatics().Damage_PhysicsDef);
	RelevantAttributesToCapture.Add(DamageStatics().Damage_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Damage_IceDef);
	RelevantAttributesToCapture.Add(DamageStatics().Damage_DarkDef);
	RelevantAttributesToCapture.Add(DamageStatics().Damage_NatureDef);
	RelevantAttributesToCapture.Add(DamageStatics().Damage_ArcaneDef);
}

void UFG_GEEC_Base::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                               FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UFGComponent* TargetAbilitySystemComponent = Cast<UFGComponent>(
		ExecutionParams.GetTargetAbilitySystemComponent());
	UFGComponent* SourceAbilitySystemComponent = Cast<UFGComponent>(
		ExecutionParams.GetSourceAbilitySystemComponent());
	if (!TargetAbilitySystemComponent || !SourceAbilitySystemComponent)
		return;

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// 获取双方所有tag
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	FHitResult hit;
	if (Spec.GetContext().GetHitResult())
	{
		hit = *Spec.GetContext().GetHitResult(); //HitResult
	}


	//计算传入伤害值, 这个是基础伤害, 后续会计算加成和减免
	float PhysicsAttack = 0.f;
	float FireAttack = 0.f;
	float IceAttack = 0.f;
	float DarkAttack = 0.f;
	float NatureAttack = 0.f;
	float ArcaneAttack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Attack_PhysicsDef, EvaluationParameters,
	                                                           PhysicsAttack);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Attack_FireDef, EvaluationParameters,
	                                                           FireAttack);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Attack_IceDef, EvaluationParameters,
	                                                           IceAttack);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Attack_DarkDef, EvaluationParameters,
	                                                           DarkAttack);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Attack_NatureDef,
	                                                           EvaluationParameters, NatureAttack);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Attack_ArcaneDef, EvaluationParameters,
	                                                           ArcaneAttack);
	//法系加成
	float FireAttackBonus = 0.f;
	float IceAttackBonus = 0.f;
	float DarkAttackBonus = 0.f;
	float NatureAttackBonus = 0.f;
	float ArcaneAttackBonus = 0.f;
	float MagicAttackBonus = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicBonus_FireDef, EvaluationParameters,
	                                                           FireAttackBonus);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicBonus_IceDef, EvaluationParameters,
	                                                           IceAttackBonus);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicBonus_DarkDef, EvaluationParameters,
	                                                           DarkAttackBonus);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicBonus_NatureDef,
	                                                           EvaluationParameters, NatureAttackBonus);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicBonus_ArcaneDef,
	                                                           EvaluationParameters, ArcaneAttackBonus);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicBonus_AllDef, EvaluationParameters,
	                                                           MagicAttackBonus);

	float critPro = 0.f;
	float critMul = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritPro_FinalDef, EvaluationParameters,
	                                                           critPro);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritMul_FinalDef, EvaluationParameters,
	                                                           critMul);
	float ArmorValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Armor_FinalDef, EvaluationParameters,
	                                                           ArmorValue);
	float DamageReduceValue = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageReduceDef, EvaluationParameters,
	                                                           DamageReduceValue);


	float FireResistance = 0.f;
	float IceResistance = 0.f;
	float DarkResistance = 0.f;
	float NatureResistance = 0.f;
	float ArcaneResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Resistance_FireDef, EvaluationParameters,
	                                                           FireResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Resistance_IceDef, EvaluationParameters,
	                                                           IceResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Resistance_DarkDef,
	                                                           EvaluationParameters, DarkResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Resistance_NatureDef,
	                                                           EvaluationParameters, NatureResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Resistance_ArcaneDef,
	                                                           EvaluationParameters, ArcaneResistance);

	EFGDamageStatus damageStatus = EFGDamageStatus::Normal;

	//先计算法术伤害
	//fire
	FireAttack *= (1 + FireAttackBonus + MagicAttackBonus); //计算加成后的数值
	float FireDamage = CalcMagicMitigatedDamage(damageStatus, FireAttack, critPro, critMul, DamageReduceValue,
	                                            FireResistance);
	if (FireDamage > 0)
	{
		TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
		                                        FFGDamageParameter(hit, FireAttack, FireDamage, EFGDamageType::Fire,
		                                                           damageStatus));
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().Damage_FireProperty, EGameplayModOp::Additive, FireDamage));
	}
	//ice
	IceAttack *= (1 + IceAttackBonus + MagicAttackBonus);
	float IceDamage = CalcMagicMitigatedDamage(damageStatus, IceAttack, critPro, critMul, DamageReduceValue,
	                                           IceResistance);
	if (IceDamage > 0)
	{
		TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
		                                        FFGDamageParameter(hit, IceAttack, IceDamage, EFGDamageType::Ice,
		                                                           damageStatus));
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().Damage_IceProperty, EGameplayModOp::Additive, IceDamage));
	}
	//dark
	DarkAttack *= (1 + DarkAttackBonus + MagicAttackBonus);
	float DarkDamage = CalcMagicMitigatedDamage(damageStatus, DarkAttack, critPro, critMul, DamageReduceValue,
	                                            DarkResistance);
	if (DarkDamage > 0)
	{
		TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
		                                        FFGDamageParameter(hit, DarkAttack, DarkDamage,
		                                                           EFGDamageType::Dark, damageStatus));
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().Damage_DarkProperty, EGameplayModOp::Additive,
			                               DarkDamage));
	}
	//nature
	NatureAttack *= (1 + NatureAttackBonus + MagicAttackBonus);
	float NatureDamage = CalcMagicMitigatedDamage(damageStatus, NatureAttack, critPro, critMul,
	                                              DamageReduceValue, NatureResistance);
	if (NatureDamage > 0)
	{
		TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
		                                        FFGDamageParameter(hit, NatureAttack, NatureDamage,
		                                                           EFGDamageType::Nature, damageStatus));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			DamageStatics().Damage_NatureProperty, EGameplayModOp::Additive, NatureDamage));
	}
	//arcane
	ArcaneAttack *= (1 + ArcaneAttackBonus + MagicAttackBonus);
	float ArcaneDamage = CalcMagicMitigatedDamage(damageStatus, ArcaneAttack, critPro, critMul, DamageReduceValue,
	                                              ArcaneResistance);
	if (ArcaneDamage > 0)
	{
		TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
		                                        FFGDamageParameter(hit, ArcaneAttack, ArcaneDamage,
		                                                           EFGDamageType::Arcane, damageStatus));
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(DamageStatics().Damage_ArcaneProperty, EGameplayModOp::Additive,
			                               ArcaneDamage));
	}


	float PhysicsDamage = CalcPhysicsMitigatedDamage(damageStatus, PhysicsAttack, ArmorValue, critPro, critMul,
	                                                 DamageReduceValue, 0);
	if (PhysicsDamage > 0)
	{
		//先计算闪避
		float dodge = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Dodge_FinalDef, EvaluationParameters,
		                                                           dodge);
		if (dodge > 0)
		{
			bool bIsMiss = UKismetMathLibrary::RandomBoolWithWeight(dodge);
			if (bIsMiss)
			{
				if (TargetAbilitySystemComponent && SourceAbilitySystemComponent)
				{
					//如果闪避了, 那么不需要计算具体伤害
					TargetAbilitySystemComponent->PreDodge(SourceAbilitySystemComponent,
					                                       FFGDamageParameter(
						                                       hit, PhysicsAttack, 0, EFGDamageType::Physics,
						                                       damageStatus));
					return;
				}
			}
		}

		//再计算格挡;格挡计算在税后,如果是税前那么需要在计算物理伤害之前进行;
		//有些设定需要正面才能格挡, 那么还需要计算方向
		float block = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockDef, EvaluationParameters,
		                                                           block);
		if (block > 0)
		{
			if (block >= PhysicsDamage)
			{
				TargetAbilitySystemComponent->PreBlock(SourceAbilitySystemComponent,
				                                       FFGDamageParameter(
					                                       hit, PhysicsAttack, 0, EFGDamageType::Physics,
					                                       damageStatus));
			}
			else
			{
				float Unmi = PhysicsDamage;
				PhysicsDamage = PhysicsDamage - block;
				TargetAbilitySystemComponent->PreBlock(SourceAbilitySystemComponent,
				                                       FFGDamageParameter(
					                                       hit, PhysicsAttack, PhysicsDamage, EFGDamageType::Physics,
					                                       damageStatus));
				TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
				                                        FFGDamageParameter(
					                                        hit, PhysicsAttack, PhysicsDamage, EFGDamageType::Physics,
					                                        damageStatus));
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
					DamageStatics().Damage_PhysicsProperty, EGameplayModOp::Additive, PhysicsDamage));
			}
		}
		else
		{
			TargetAbilitySystemComponent->PreDamage(SourceAbilitySystemComponent,
			                                        FFGDamageParameter(hit, PhysicsAttack, PhysicsDamage,
			                                                           EFGDamageType::Physics, damageStatus));
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(DamageStatics().Damage_PhysicsProperty, EGameplayModOp::Additive,
				                               PhysicsDamage));
		}
	}
}


float UFG_GEEC_Base::CalcPhysicsMitigatedDamage_Implementation(EFGDamageStatus& OutDamageStatus,
                                                                   float UnmitigatedDamage, float TargetArmor,
                                                                   float critPro,
                                                                   float critMul, float ReducePercent,
                                                                   float PhysicsResistance) const
{
	float outDamage = 0.0f;
	bool bIsCrit = UKismetMathLibrary::RandomBoolWithWeight(critPro);
	float armorPerc = 1 - (TargetArmor / (TargetArmor + 500));
	float globlePerc = FMath::Clamp((1 - ReducePercent), 0.01f, 100.f);
	float resistancePerc = 1 - (PhysicsResistance / (PhysicsResistance + 50));
	float critValue = FMath::Clamp((bIsCrit ? critMul : 1.0f), 1.0f, 999.0f);
	OutDamageStatus = bIsCrit ? EFGDamageStatus::Crit : EFGDamageStatus::Normal;
	outDamage = UnmitigatedDamage * armorPerc * globlePerc * resistancePerc * critValue;
	if (bDebug && outDamage > 0)
	{
		UE_LOG(LogTemp, Log,
		       TEXT(
			       "GEEC::CalcPhysicsMitigatedDamage, SourceDamage = %f, ArmorReduce = %f, GlobleReduce = %f, ResistanceReduce = %f , CritValue = %f, \n OutDamage = %f"
		       ),
		       UnmitigatedDamage, 1 - armorPerc, 1 - globlePerc, 1 - resistancePerc, critValue, outDamage);
	}
	return outDamage;
}

float UFG_GEEC_Base::CalcMagicMitigatedDamage_Implementation(EFGDamageStatus& OutDamageStatus,
                                                                 float UnmitigatedDamage, float critPro, float critMul,
                                                                 float ReducePercent, float Resistance) const
{
	float outDamage = 0.0f;
	bool bIsCrit = UKismetMathLibrary::RandomBoolWithWeight(critPro);
	float globlePerc = FMath::Clamp((1 - ReducePercent), 0.01f, 100.f);
	float resistancePerc = 1 - (Resistance / (Resistance + 50));
	float critValue = FMath::Clamp((bIsCrit ? critMul : 1.0f), 1.0f, 999.0f);
	OutDamageStatus = bIsCrit ? EFGDamageStatus::Crit : EFGDamageStatus::Normal;
	outDamage = UnmitigatedDamage * globlePerc * resistancePerc * critValue;
	if (bDebug && outDamage > 0)
	{
		UE_LOG(LogTemp, Log,
		       TEXT(
			       "USRGEEC_Damage::CalcMagicMitigatedDamage, SourceDamage = %f, GlobleReduce = %f, ResistanceReduce = %f , CritValue = %f \n OutDamage = %f"
		       ),
		       UnmitigatedDamage, 1 - globlePerc, 1 - resistancePerc, critValue, outDamage);
	}
	return outDamage;
}
