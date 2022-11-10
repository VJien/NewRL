// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTask_ListenTag.h"

#include "AbilitySystemComponent.h"


UAsyncTask_ListenTagChanged* UAsyncTask_ListenTagChanged::ListenForTagChange(
	UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag Tag)
{
	UAsyncTask_ListenTagChanged* WaitForTagChangedTask = NewObject<UAsyncTask_ListenTagChanged>();
	WaitForTagChangedTask->ASC = AbilitySystemComponent;
	WaitForTagChangedTask->TagToListenFor = Tag;

	if (!IsValid(AbilitySystemComponent) || !Tag.IsValid())
	{
		WaitForTagChangedTask->RemoveFromRoot();
		return nullptr;
	}

	WaitForTagChangedTask->Handle = AbilitySystemComponent->RegisterGameplayTagEvent(Tag,EGameplayTagEventType::NewOrRemoved).AddUObject(WaitForTagChangedTask, &UAsyncTask_ListenTagChanged::TagChanged);

	return WaitForTagChangedTask;
}

void UAsyncTask_ListenTagChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->UnregisterGameplayTagEvent(Handle,TagToListenFor,EGameplayTagEventType::NewOrRemoved);
		
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UAsyncTask_ListenTagChanged::TagChanged(const FGameplayTag Tag, int32 Count)
{
	if (Count >= 1)
	{
		OnTagAdd.Broadcast(Tag);
	}
	else
	{
		OnTagRemove.Broadcast(Tag);
	}
	
}
