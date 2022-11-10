// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_PlayMontage.generated.h"

class UGameplayAbility;
class UFGComponent;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSRPlayMontageWaitEventDlg, FGameplayTag, EventTag, FGameplayEventData, EventData);
/**
 * 
 */
UCLASS()
class FASTGAS_API UAbilityTask_PlayMontage : public UAbilityTask
{
	GENERATED_UCLASS_BODY()
public:
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;


	UPROPERTY(BlueprintAssignable)
		FSRPlayMontageWaitEventDlg OnCompleted;
	UPROPERTY(BlueprintAssignable)
		FSRPlayMontageWaitEventDlg OnBlendOut;
	//打断
	UPROPERTY(BlueprintAssignable)
		FSRPlayMontageWaitEventDlg OnInterrupted;

	/** 被执行 CancelAbility */
	UPROPERTY(BlueprintAssignable)
		FSRPlayMontageWaitEventDlg OnCancelled;

	/** 触发匹配Tag的Event*/
	UPROPERTY(BlueprintAssignable)
		FSRPlayMontageWaitEventDlg EventReceived;


	UFUNCTION(BlueprintCallable, Category = "FastGas|AbilityTasks", meta = (DisplayName= "Play Montage And Wait For Event",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAbilityTask_PlayMontage* CreatPlayMontageProxy(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			UAnimMontage* MontageToPlay,
			FGameplayTagContainer EventTags,
			float Rate = 1.f,
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.f);

private:

	UPROPERTY()
		UAnimMontage* MontageToPlay;

	/** 需要匹配的Event的tag*/
	UPROPERTY()
		FGameplayTagContainer EventTags;


	UPROPERTY()
		float Rate;


	UPROPERTY()
		FName StartSection;

	/** RootMotion位移缩放*/
	UPROPERTY()
		float AnimRootMotionTranslationScale;


	UPROPERTY()
		bool bStopWhenAbilityEnds;

	
	bool StopPlayingMontage();


	UFGComponent* GetTargetASC();

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;
};
