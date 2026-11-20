// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperSprite.h"
#include "Core/VNBaseTypes.h"
#include "VNDACharacterEmotion.generated.h"

UCLASS()
class VISUALNOVEL_API UVNDACharacterEmotion : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	TSoftObjectPtr<UPaperSprite> GetEmotionSprite(EEmotion Emotion) const;
	void PreloadAllEmotions(FSimpleDelegate OnComplete = FSimpleDelegate());
	
	FText GetNameCharacter() const
	{
		return NameCharacter;
	};
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TMap<EEmotion, TSoftObjectPtr<UPaperSprite>> EmotionTextures;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	FText NameCharacter;
};
