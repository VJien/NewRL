// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGComponent.h"
#include "FGAttributeSetBase.generated.h"

#define DAMAGE_HANDLE(Attribute,C,Name) \
{\
if(Attribute == GetDamage_##Name##Attribute()) \
{	\
float TempDamage = GetDamage_##Name(); \
SetDamage_##Name(0);	\
if(TempDamage>0)	\
{	\
AFGCharacter* character = Cast<AFGCharacter>(C);	\
if (character&&character->IsAlive())\
{\
CalcShieldAndHealth(TempDamage);\
}\
}	\
} \
}


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedMulDly, const FGameplayAttribute&,float,float);


UCLASS(BlueprintType, Blueprintable)
class FASTGAS_API UFGAttributeSetBase : public UAttributeSet
{
public:
	GENERATED_UCLASS_BODY()
	~UFGAttributeSetBase();


	float MAX_VALUE = 9999.f;
	float DEF_CRIT_PRO = 0.05f;
	float DEF_CRIP_MUL_MAX = 10.0f;
	float MAX_MOVE_SPEED = 1000.f;
	float MAX_ATTACK_SPEED = 3.0f;
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//预处理， 比如处理当前生命值与最大生命值的百分比关系
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)override;
	//应用GE以后的后处理， 一般处理不同属性之间的依赖关系， 比如修改了耐力属性，而耐力会影响生命值上限；或者clamp当前生命值保持在0和Max之间
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)override;

	FOnAttributeChangedMulDly& GetGameplayAttributeValueChangeDelegate(FGameplayAttribute Attribute);




	TArray<FGameplayAttributeData> ListAllAttributeData();
	TArray<FGameplayAttribute> ListAllAttribute();
	
protected:
	TMap<FGameplayAttribute, FOnAttributeChangedMulDly> AttributeValueChangeDelegates;
	void BroadcastValueChanged(FGameplayAttribute Attribute);
	//自适应当前属性与最大属性的百分比
	virtual void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	//处理属性修改， 某些属性修改会影响其他属性
	virtual void HandleAttributeChanged(FGameplayAttribute Attribute);
	virtual bool ShouldRecalculateHealth(FGameplayAttribute Attribute)const;
	virtual bool ShouldRecalculateHealthRegenRate(FGameplayAttribute Attribute)const;
	//限制属性不超过最大值， 比如Health不能超过MaxHealth
	virtual void ClampAttributes(FGameplayAttribute Attribute);

	bool ShouldRecalculateSheild(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateMana(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateEnergy(FGameplayAttribute Attribute) const;

	bool ShouldRecalculateAttack(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateAttackSpeed(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateMoveSpeed(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateCritPro(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateCritMul(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateArmor(FGameplayAttribute Attribute) const;
	bool ShouldRecalculateDodge(FGameplayAttribute Attribute)const;
	bool ShouldRecalculateMagicPower(FGameplayAttribute Attribute) const;

	bool IsAnyDamage(FGameplayAttribute Attribute) const;

	void HandleDamage(const FGameplayAttribute& Attribute, class AFGCharacter* TargetCharacter);

	void CalcShieldAndHealth(float Damage);
public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health_Current;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Current)
	/* 最大生命值
	 * 不要直接修改,通过下面3个参数修改
	 * Health_Max_Final = (Health_Max_Base + Health_Max_BonusConstant) * (1 + Health_Max_BonusPercent)
	 **/
		UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health_Max)
	FGameplayAttributeData Health_Max_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Max_Final)
		UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health_Max_Base)
	FGameplayAttributeData Health_Max_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Max_Base)
		UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health_Max_BonusConstant)
	FGameplayAttributeData Health_Max_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Max_BonusConstant)
		UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health_Max_BonusPercent)
	FGameplayAttributeData Health_Max_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Max_BonusPercent)
		//生命回复,不要直接修改,通过下面3个参数修改,类似MaxHealth
		UPROPERTY(BlueprintReadOnly, Category = "Health_Regen", ReplicatedUsing = OnRep_Health_RegenRate_Final)
	FGameplayAttributeData Health_RegenRate_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_RegenRate_Final)
		UPROPERTY(BlueprintReadOnly, Category = "Health_Regen", ReplicatedUsing = OnRep_Health_RegenRate_Base)
	FGameplayAttributeData Health_RegenRate_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_RegenRate_Base)
		UPROPERTY(BlueprintReadOnly, Category = "Health_Regen", ReplicatedUsing = OnRep_Health_RegenRate_BonusConstant)
	FGameplayAttributeData Health_RegenRate_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_RegenRate_BonusConstant)
		UPROPERTY(BlueprintReadOnly, Category = "Health_Regen", ReplicatedUsing = OnRep_Health_RegenRate_BonusPercent)
	FGameplayAttributeData Health_RegenRate_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_RegenRate_BonusPercent)

	


	
	UPROPERTY(BlueprintReadOnly, Category = "Level", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Level)



	
	
	//护盾
	UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_Shield)
	FGameplayAttributeData Shield_Current;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Shield_Current)
	UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_Shield_Max_Final)
	FGameplayAttributeData Shield_Max_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Shield_Max_Final)
	UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_Shield_Max_Base)
	FGameplayAttributeData Shield_Max_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Shield_Max_Base)
	UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_Shield_Max_BonusConstant)
	FGameplayAttributeData Shield_Max_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Shield_Max_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_Shield_Max_BonusPercent)
	FGameplayAttributeData Shield_Max_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Shield_Max_BonusPercent)

	//魔法
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana_Current;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Current)
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana_Max_Final)
	FGameplayAttributeData Mana_Max_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Max_Final)
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana_Max_Base)
	FGameplayAttributeData Mana_Max_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Max_Base)
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana_Max_BonusConstant)
	FGameplayAttributeData Mana_Max_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Max_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana_Max_BonusPercent)
	FGameplayAttributeData Mana_Max_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Max_BonusPercent)

	//能量
	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy)
	FGameplayAttributeData Energy_Current;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Energy_Current)
	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy_Max_Final)
	FGameplayAttributeData Energy_Max_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Energy_Max_Final)
	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy_Max_Base)
	FGameplayAttributeData Energy_Max_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Energy_Max_Base)
	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy_Max_BonusConstant)
	FGameplayAttributeData Energy_Max_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Energy_Max_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy_Max_BonusPercent)
	FGameplayAttributeData Energy_Max_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Energy_Max_BonusPercent)

#pragma region Bullet
	//子弹
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Default)
	FGameplayAttributeData BulletNum_Default;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Default)
	//最大子弹数量
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Default_Max)
	FGameplayAttributeData BulletNum_Default_Max;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Default_Max)
	//每个弹夹数量
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Default_PerMag)
	FGameplayAttributeData BulletNum_Default_PerMag;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Default_PerMag)


	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Default)
	FGameplayAttributeData BulletNum_Special_A;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Special_A)
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Special_A_Max)
	FGameplayAttributeData BulletNum_Special_A_Max;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Special_A_Max)
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Special_A_PerMag)
	FGameplayAttributeData BulletNum_Special_A_PerMag;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Special_A_PerMag)

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Special_B)
	FGameplayAttributeData BulletNum_Special_B;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Special_B)
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Special_B_Max)
	FGameplayAttributeData BulletNum_Special_B_Max;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Special_B_Max)
	UPROPERTY(BlueprintReadOnly, Category = "Weapon", ReplicatedUsing = OnRep_BulletNum_Special_B_PerMag)
	FGameplayAttributeData BulletNum_Special_B_PerMag;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, BulletNum_Special_B_PerMag)

#pragma endregion  Bullet


	//生命窃取
	UPROPERTY(BlueprintReadOnly, Category = "HealthSteal", ReplicatedUsing = OnRep_Health_Steal_Constant)
	FGameplayAttributeData Health_Steal_Constant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Steal_Constant)
	UPROPERTY(BlueprintReadOnly, Category = "HealthSteal", ReplicatedUsing = OnRep_Health_Steal_Percent)
	FGameplayAttributeData Health_Steal_Percent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Health_Steal_Percent)

	//魔法窃取
	UPROPERTY(BlueprintReadOnly, Category = "ManaSteal", ReplicatedUsing = OnRep_Mana_Steal_Constant)
	FGameplayAttributeData Mana_Steal_Constant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Steal_Constant)
	UPROPERTY(BlueprintReadOnly, Category = "ManaSteal", ReplicatedUsing = OnRep_Mana_Steal_Percent)
	FGameplayAttributeData Mana_Steal_Percent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Mana_Steal_Percent)


	/***************AttackParameter Begin***************/
	//攻击力总和,基础为0,不要直接修改,通过下面参数修改
	UPROPERTY(BlueprintReadOnly, Category = "Attack", ReplicatedUsing = OnRep_Attack_Final)
	FGameplayAttributeData Attack_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Final)
	UPROPERTY(BlueprintReadOnly, Category = "Attack", ReplicatedUsing = OnRep_Attack_Base)
	FGameplayAttributeData Attack_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Base)
	/** 伤害提升固定值  */
	UPROPERTY(BlueprintReadOnly, Category = "Attack", ReplicatedUsing = OnRep_Attack_BonusConstant)
	FGameplayAttributeData Attack_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_BonusConstant)
	/** 伤害提升系数,按百分比提升  */
	UPROPERTY(BlueprintReadOnly, Category = "Attack", ReplicatedUsing = OnRep_Attack_BonusPercent)
	FGameplayAttributeData Attack_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_BonusPercent)
	//攻速, 急速
	UPROPERTY(BlueprintReadOnly, Category = "AttackSpeed", ReplicatedUsing = OnRep_AttackSpeed_Final)
	FGameplayAttributeData AttackSpeed_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, AttackSpeed_Final)
	UPROPERTY(BlueprintReadOnly, Category = "AttackSpeed", ReplicatedUsing = OnRep_AttackSpeed_Base)
	FGameplayAttributeData AttackSpeed_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, AttackSpeed_Base)
	UPROPERTY(BlueprintReadOnly, Category = "AttackSpeed", ReplicatedUsing = OnRep_AttackSpeed_BonusPercent)
	FGameplayAttributeData AttackSpeed_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, AttackSpeed_BonusPercent)
	//暴击概率,基础为5%,不要直接修改,通过下面参数修改
	UPROPERTY(BlueprintReadOnly, Category = "CritPro_Final", ReplicatedUsing = OnRep_CritPro_Final)
	FGameplayAttributeData CritPro_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CritPro_Final)
	UPROPERTY(BlueprintReadOnly, Category = "CritPro_Final", ReplicatedUsing = OnRep_CritPro_BonusConstant)
	FGameplayAttributeData CritPro_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CritPro_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "CritPro_Final", ReplicatedUsing = OnRep_CritPro_BonusPercent)
	FGameplayAttributeData CritPro_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CritPro_BonusPercent)
	//暴击倍数,1.0=没有提升,基础为1.5,只有加值,没有乘值加成,不要直接修改,通过下面参数修改
	UPROPERTY(BlueprintReadOnly, Category = "CritMul", ReplicatedUsing = OnRep_CritMul_Final)
	FGameplayAttributeData CritMul_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CritMul_Final)
	UPROPERTY(BlueprintReadOnly, Category = "CritMul", ReplicatedUsing = OnRep_CritMul_BonusConstant)
	FGameplayAttributeData CritMul_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CritMul_BonusConstant)


	/****************Magic Bonus Begin********************/
	//法术强度, 并不直接加成技能, 通过技能本身属性体现在伤害上
	UPROPERTY(BlueprintReadOnly, Category = "MagicPower", ReplicatedUsing = OnRep_MagicPower_Final)
	FGameplayAttributeData MagicPower_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicPower_Final)
	UPROPERTY(BlueprintReadOnly, Category = "MagicPower", ReplicatedUsing = OnRep_MagicPower_Base)
	FGameplayAttributeData MagicPower_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicPower_Base)
	UPROPERTY(BlueprintReadOnly, Category = "MagicPower", ReplicatedUsing = OnRep_MagicPower_BonusConstant)
	FGameplayAttributeData MagicPower_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicPower_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "MagicPower", ReplicatedUsing = OnRep_MagicPower_BonusPercent)
	FGameplayAttributeData MagicPower_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicPower_BonusPercent)
	//法术增强, 直接参与计算
	UPROPERTY(BlueprintReadOnly, Category = "MagicBonus", ReplicatedUsing = OnRep_MagicBonus_Fire)
	FGameplayAttributeData MagicBonus_Fire;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicBonus_Fire)
	UPROPERTY(BlueprintReadOnly, Category = "MagicBonus", ReplicatedUsing = OnRep_MagicBonus_Ice)
	FGameplayAttributeData MagicBonus_Ice;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicBonus_Ice)
	UPROPERTY(BlueprintReadOnly, Category = "MagicBonus", ReplicatedUsing = OnRep_MagicBonus_Dark)
	FGameplayAttributeData MagicBonus_Dark;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicBonus_Dark)
	UPROPERTY(BlueprintReadOnly, Category = "MagicBonus", ReplicatedUsing = OnRep_MagicBonus_Nature)
	FGameplayAttributeData MagicBonus_Nature;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicBonus_Nature)
	UPROPERTY(BlueprintReadOnly, Category = "MagicBonus", ReplicatedUsing = OnRep_MagicBonus_Arcane)
	FGameplayAttributeData MagicBonus_Arcane;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicBonus_Arcane)
	UPROPERTY(BlueprintReadOnly, Category = "MagicBonus", ReplicatedUsing = OnRep_MagicBonus_All)
	FGameplayAttributeData MagicBonus_All;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MagicBonus_All)
	/***************Magic Bonus End***************/


#pragma region Defence
	/***********Defense   Begin*************/
	//护甲,不要直接修改,通过下面参数修改
	UPROPERTY(BlueprintReadOnly, Category = " Armor", ReplicatedUsing = OnRep_Armor_Final)
	FGameplayAttributeData Armor_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Armor_Final)
	UPROPERTY(BlueprintReadOnly, Category = " Armor", ReplicatedUsing = OnRep_Armor_Base)
	FGameplayAttributeData Armor_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Armor_Base)
	UPROPERTY(BlueprintReadOnly, Category = " Armor", ReplicatedUsing = OnRep_Armor_BonusConstant)
	FGameplayAttributeData Armor_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Armor_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = " Armor", ReplicatedUsing = OnRep_Armor_BonusPercent)
	FGameplayAttributeData Armor_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Armor_BonusPercent)

	
	//格挡值,来自装备和buff
	UPROPERTY(BlueprintReadOnly, Category = "Block", ReplicatedUsing = OnRep_Block)
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Block)

	/** 减免控制的百分比, 取值(0-1) */
	UPROPERTY(BlueprintReadOnly, Category = "ControlReduce", ReplicatedUsing = OnRep_ControlReduce)
	FGameplayAttributeData ControlReduce;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, ControlReduce)

	/** 伤害减免,应用到所有伤害的 */
	UPROPERTY(BlueprintReadOnly, Category = "DamageReduce", ReplicatedUsing = OnRep_DamageReduce)
	FGameplayAttributeData DamageReduce;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, DamageReduce)

	//闪避概率,基础为0,来自自身属性,buff和装备
	UPROPERTY(BlueprintReadOnly, Category = "Dodge", ReplicatedUsing = OnRep_Dodge_Final)
	FGameplayAttributeData Dodge_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Dodge_Final)
	UPROPERTY(BlueprintReadOnly, Category = "Dodge", ReplicatedUsing = OnRep_DodgeProBase)
	FGameplayAttributeData Dodge_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Dodge_Base)
	UPROPERTY(BlueprintReadOnly, Category = "Dodge", ReplicatedUsing = OnRep_Dodge_BonusConstant)
	FGameplayAttributeData Dodge_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Dodge_BonusConstant)


	//抗性,默认为0,只有加值
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_Resistance_Fire)
	FGameplayAttributeData Resistance_Fire;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Resistance_Fire)
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_Resistance_Ice)
	FGameplayAttributeData Resistance_Ice;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Resistance_Ice)
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_Resistance_Dark)
	FGameplayAttributeData Resistance_Dark;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Resistance_Dark)
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_Resistance_Nature)
	FGameplayAttributeData Resistance_Nature;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Resistance_Nature)
	UPROPERTY(BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_Resistance_Arcane)
	FGameplayAttributeData Resistance_Arcane;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Resistance_Arcane)

#pragma endregion Defence


	//当前经验值
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, XP)
	//经验获取增幅
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_XPBonusConstant)
	FGameplayAttributeData XPBonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, XPBonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_XPBonusPercent)
	FGameplayAttributeData XPBonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, XPBonusPercent)
	//玩家角色
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CharacterLevel)
	//职业等级
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_CareerLevel)
	FGameplayAttributeData CareerLevel;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, CareerLevel)
	//剩余技能点
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_SkillPoint)
	FGameplayAttributeData SkillPoint;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, SkillPoint)
	//剩余天赋点
	UPROPERTY(BlueprintReadOnly, Category = "Character", ReplicatedUsing = OnRep_TalentlPoint)
	FGameplayAttributeData TalentlPoint;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, TalentlPoint)


	

	//移动速度, 不要直接修改,通过下面参数修改
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed_Final)
	FGameplayAttributeData MoveSpeed_Final;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MoveSpeed_Final)
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeedBase)
	FGameplayAttributeData MoveSpeed_Base;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MoveSpeed_Base)
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeedBonusConstant)
	FGameplayAttributeData MoveSpeed_BonusConstant;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MoveSpeed_BonusConstant)
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeedBonusPercent)
	FGameplayAttributeData MoveSpeed_BonusPercent;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, MoveSpeed_BonusPercent)


	/************* Combat TempValue Begin************** */
	//临时攻击数据, 通过技能初始化, 用于结算最终伤害
	UPROPERTY(BlueprintReadOnly, Category = "AttackTemp", ReplicatedUsing = OnRep_Attack_Physics)
	FGameplayAttributeData Attack_Physics;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Physics)
	UPROPERTY(BlueprintReadOnly, Category = "AttackTemp", ReplicatedUsing = OnRep_Attack_Fire)
	FGameplayAttributeData Attack_Fire;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Fire)
	UPROPERTY(BlueprintReadOnly, Category = "AttackTemp", ReplicatedUsing = OnRep_Attack_Ice)
	FGameplayAttributeData Attack_Ice;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Ice)
	UPROPERTY(BlueprintReadOnly, Category = "AttackTemp", ReplicatedUsing = OnRep_Attack_Dark)
	FGameplayAttributeData Attack_Dark;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Dark)
	UPROPERTY(BlueprintReadOnly, Category = "AttackTemp", ReplicatedUsing = OnRep_Attack_Nature)
	FGameplayAttributeData Attack_Nature;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Nature)
	UPROPERTY(BlueprintReadOnly, Category = "AttackTemp", ReplicatedUsing = OnRep_Attack_Arcane)
	FGameplayAttributeData Attack_Arcane;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Attack_Arcane)

	//临时受伤数据
	UPROPERTY(BlueprintReadOnly, Category = "DamageTemp", ReplicatedUsing = OnRep_Damage_Physics)
	FGameplayAttributeData Damage_Physics;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Damage_Physics)
	UPROPERTY(BlueprintReadOnly, Category = "DamageTemp", ReplicatedUsing = OnRep_Damage_Fire)
	FGameplayAttributeData Damage_Fire;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Damage_Fire)
	UPROPERTY(BlueprintReadOnly, Category = "DamageTemp", ReplicatedUsing = OnRep_Damage_Ice)
	FGameplayAttributeData Damage_Ice;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Damage_Ice)
	UPROPERTY(BlueprintReadOnly, Category = "DamageTemp", ReplicatedUsing = OnRep_Damage_Dark)
	FGameplayAttributeData Damage_Dark;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Damage_Dark)
	UPROPERTY(BlueprintReadOnly, Category = "DamageTemp", ReplicatedUsing = OnRep_Damage_Nature)
	FGameplayAttributeData Damage_Nature;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Damage_Nature)
	UPROPERTY(BlueprintReadOnly, Category = "DamageTemp", ReplicatedUsing = OnRep_Damage_Arcane)
	FGameplayAttributeData Damage_Arcane;
	ATTRIBUTE_ACCESSORS(UFGAttributeSetBase, Damage_Arcane)
	/************* Combat TempValue End************** */

protected:
	//同步函数,万恶的UFUNCTION(), 只能手动创建所有
	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_Max(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_Max_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_Max_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_Max_BonusPercent(const FGameplayAttributeData& OldValue);


	UFUNCTION()
		virtual void OnRep_Health_RegenRate_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_RegenRate_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_RegenRate_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_Health_RegenRate_BonusPercent(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
		virtual void OnRep_Level(const FGameplayAttributeData& OldValue);


		UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Shield_Max_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Shield_Max_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Shield_Max_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Shield_Max_BonusPercent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana_Max_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana_Max_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana_Max_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana_Max_BonusPercent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Energy_Max_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Energy_Max_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Energy_Max_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Energy_Max_BonusPercent(const FGameplayAttributeData& OldValue);


	UFUNCTION()
	virtual void OnRep_BulletNum_Default(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_BulletNum_Default_Max(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_BulletNum_Default_PerMag(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BulletNum_Special_A(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_BulletNum_Special_A_Max(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_BulletNum_Special_A_PerMag(const FGameplayAttributeData& OldValue);


	UFUNCTION()
	virtual void OnRep_BulletNum_Special_B(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_BulletNum_Special_B_Max(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_BulletNum_Special_B_PerMag(const FGameplayAttributeData& OldValue);


	UFUNCTION()
	virtual void OnRep_Health_Steal_Constant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Health_Steal_Percent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana_Steal_Constant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Mana_Steal_Percent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Attack_Final(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_Attack_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_BonusPercent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_AttackSpeed_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_AttackSpeed_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_AttackSpeed_BonusPercent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CritPro_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CritPro_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CritPro_BonusPercent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CritMul_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CritMul_BonusConstant(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicPower_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MagicPower_Base(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
virtual void OnRep_MagicPower_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicPower_BonusPercent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicBonus_Fire(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicBonus_Ice(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicBonus_Dark(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicBonus_Nature(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicBonus_Arcane(const FGameplayAttributeData& OldValue);
	UFUNCTION()
virtual void OnRep_MagicBonus_All(const FGameplayAttributeData& OldValue);
	

	UFUNCTION()
	virtual void OnRep_Armor_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Armor_Base(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Armor_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Armor_BonusPercent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_DamageReduce(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Dodge_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_DodgeProBase(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Dodge_BonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Block(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_ControlReduce(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Resistance_Fire(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Resistance_Ice(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Resistance_Dark(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Resistance_Nature(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Resistance_Arcane(const FGameplayAttributeData& OldValue);



	UFUNCTION()
	virtual void OnRep_XP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_XPBonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_XPBonusPercent(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CharacterLevel(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_CareerLevel(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_SkillPoint(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_TalentlPoint(const FGameplayAttributeData& OldValue);


	UFUNCTION()
	virtual void OnRep_MoveSpeed_Final(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MoveSpeedBase(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MoveSpeedBonusConstant(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_MoveSpeedBonusPercent(const FGameplayAttributeData& OldValue);


	UFUNCTION()
	virtual void OnRep_Attack_Physics(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_Fire(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_Ice(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_Dark(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_Nature(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Attack_Arcane(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Damage_Physics(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage_Fire(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage_Ice(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage_Dark(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage_Nature(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	virtual void OnRep_Damage_Arcane(const FGameplayAttributeData& OldValue);
};
