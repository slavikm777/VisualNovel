// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/VNUserWidget.h"
#include "Core/VNBaseTypes.h"
#include "Core/VNBasicChoiceObject.h"
#include "VNDialogueDisplay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDisplayChoiceMade, int, ChoiceIndex);

class UVNCustomButton;
class UVNDialogueBox;
class UImage;
class UVerticalBox;
class UVNChoiceButtons;

UCLASS()
class VISUALNOVEL_API UVNDialogueDisplay : public UVNUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UVNDialogueBox* DialogueBox;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ImageLeft;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ImageRight;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UVNCustomButton> ButtonClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UVNChoiceButtons> ButtonChoiceClass;
	
	UPROPERTY()
	TObjectPtr<UVNCustomButton> NextButton;
	
public:
	UPROPERTY(BlueprintAssignable)
	FDisplayChoiceMade OnChoiceMade;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RunDialogueTable(UDataTable* InDialogueTable);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RunDialogWithChoice(const FDialogue& NewDialogue, const TArray<UVNBasicChoiceObject*>& InOptions);
	
	UFUNCTION(BlueprintPure)
	UVNDialogueBox* GetDialogueBox() const { return DialogueBox; }

private:
	UPROPERTY()
	TObjectPtr<UVNChoiceButtons> ChoiceButtons;
	
	void SetImageDialogue(const ESide Side, UTexture2D* Face);
	
	UFUNCTION()
	void OnNextButtonClicked(int InIndex);
	
	UFUNCTION()
	void OnChoiceMadeEvent(int ChoiceIndex);
};
