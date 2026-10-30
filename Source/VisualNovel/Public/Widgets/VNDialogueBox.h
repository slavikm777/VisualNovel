// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/VNUserWidget.h"
#include "Core/VNBaseTypes.h"
#include "VNDialogueBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueFinishedDelegate);

class UTextBlock;
class UImage;


UCLASS()
class VISUALNOVEL_API UVNDialogueBox : public UVNUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetNewDialogue(const FDialogue& NewDialogue);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDialogueFinishedDelegate OnDialogueFinished;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartNewDialogue(UDataTable* InDialogueTable);
	
	UFUNCTION()
	void ProgressDialogue();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextName;
	
	int Index = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (RequiredAssetDataTags = "RowStructure=/Script/VisualNovel.Dialogue"))
	TObjectPtr<UDataTable> DialogueTable;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RunDialogueTable(UDataTable* InDialogueTable);
	
	bool HaveNextDialogue();
	FDialogue GetNextDialogue();
};
