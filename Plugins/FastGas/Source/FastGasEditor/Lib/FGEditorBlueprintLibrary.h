// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FastGas/GAS/FGAttributeSetBase.h"
#include "FGEditorBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FASTGASEDITOR_API UFGEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
#if WITH_EDITOR

	
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|DataTable")
	static void CreateAttributeSetDataTable(TSubclassOf<UAttributeSet> AtttributeSetClass);
	
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|DataTable")
	static UDataTable* CreateDatatable_GameplayTag();

	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|DataTable", DisplayName="Add Data Table Row(Gameplay Tag Table Row)")
	static void AddDataTableNewRow_GameplayTagName(UDataTable* DataTable, FName RowName, FName Tag);

	//创建传入属性的ByCaller类型的GE, 需要匹配属性的名称和tag
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|DataTable")
	static void CreateGameplayEffects(TArray<FGameplayAttribute> Attributes, const FString& Path,bool bCreateAdditive=true, bool bCreateMulti=true, bool bCreateOverride=true);
	//创建所有属性的ByCaller类型的GE, 需要匹配属性的名称和tag
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|DataTable")
	static void CreateGameplayEffectsAllAttributes(TSubclassOf<UAttributeSet> AtttributeSetClass, const FString& Path,bool bCreateAdditive=true, bool bCreateMulti=true, bool bCreateOverride=true);

	
	static FString OpenWindowsDirectory(const FString& Path);






	//**********************作废
	UFUNCTION(BlueprintCallable, CustomThunk, DisplayName="Add Data Table Row",meta = (CustomStructureParam = "RowData", BlueprintAutocast), Category = "FastGas|Lib|DataTable")
	static void BP_AddDataTableRow(const FTableRowBase& RowData, UDataTable* DataTable, FName RowName);
	static void GenericAddDataTableRow(const void* Data, UDataTable* DataTable, FName RowName);


	
	DECLARE_FUNCTION(execBP_AddDataTableRow)
	{
		//Stack.Step(Stack.Object, NULL);
		Stack.StepCompiledIn<FStructProperty>(NULL);
		FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		
		P_GET_OBJECT_REF(UDataTable, DataTable)
		P_GET_PROPERTY_REF(FNameProperty, RowName)
		P_FINISH;

		P_NATIVE_BEGIN;
		if (DataTable)
		{
			GenericAddDataTableRow(StructProperty->Struct, DataTable, RowName);
		}
		
		P_NATIVE_END;
	}
	//**********************作废
#endif
	
};
