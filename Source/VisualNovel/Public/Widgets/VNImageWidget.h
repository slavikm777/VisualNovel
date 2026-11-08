// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/VNUserWidget.h"
#include "VNImageWidget.generated.h"

class UImage;

UCLASS()
class VISUALNOVEL_API UVNImageWidget : public UVNUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetImageFromSprite(TSoftObjectPtr<UPaperSprite> InSprite);
	
	UFUNCTION(BlueprintCallable)
	void SetImageVisible(bool bVisible);
};
