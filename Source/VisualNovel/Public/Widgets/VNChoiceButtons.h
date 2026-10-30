// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/VNUserWidget.h"
#include "VNChoiceButtons.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChoiceMade, int, ChoiceIndex);

class UVerticalBox;
class UVNBasicChoiceObject;
class UVNCustomButton;


UCLASS()
class VISUALNOVEL_API UVNChoiceButtons : public UVNUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TArray<UVNBasicChoiceObject*> Options;
	
	UPROPERTY(BlueprintAssignable)
	FChoiceMade OnChoiceMade;
	
	void ConstructChoiceButtons(TSubclassOf<UVNCustomButton> InClassButton);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonBox;
	
private:
	UFUNCTION()
	void HandleChoice(int ChoiceIndex);
	
};
