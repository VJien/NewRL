// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTask_ListenTag.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagChanged, FGameplayTag, Tag);

UCLASS()
class FASTGAS_API UAsyncTask_ListenTagChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnTagChanged OnTagAdd;
	UPROPERTY(BlueprintAssignable)
	FOnTagChanged OnTagRemove;

	// 监听 tag 改变
	UFUNCTION(BlueprintCallable, Category = "FastGas|AbilityTasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAsyncTask_ListenTagChanged* ListenForTagChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag Tag);



	UFUNCTION(BlueprintCallable)
		void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayTag TagToListenFor;
	FDelegateHandle Handle; 

	void TagChanged(const FGameplayTag Tag, int32 Count);
};
