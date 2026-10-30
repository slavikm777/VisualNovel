// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/VNUserWidget.h"
#include "VNCustomButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, int, Index);

class UButton;
class UTextBlock;


UCLASS()
class VISUALNOVEL_API UVNCustomButton : public UVNUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInfo(const int InIndex, const FText InText);
	
	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClicked;
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
	
	int Index = 0;
	FText Text;
	
private:
	UFUNCTION()
	void OnClickedButton();
};
