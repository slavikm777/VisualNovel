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
class UVerticalBox;
class UVNChoiceButtons;
class UVNImageWidget;
class UPaperSprite;

UCLASS()
class VISUALNOVEL_API UVNDialogueDisplay : public UVNUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UVNDialogueBox* DialogueBox;
	
	UPROPERTY(meta = (BindWidget))
	UVNImageWidget* ImageLeft;
	
	UPROPERTY(meta = (BindWidget))
	UVNImageWidget* ImageRight;
	
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
	
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TObjectPtr<UVNChoiceButtons> ChoiceButtons;
	
	UFUNCTION()
	void OnNextButtonClicked(int InIndex);
	
	UFUNCTION()
	void OnChoiceMadeEvent(int ChoiceIndex);
	
	UFUNCTION()
	void SetImageDialogue(TSoftObjectPtr<UPaperSprite> InSprite, ESide InSide);
};
