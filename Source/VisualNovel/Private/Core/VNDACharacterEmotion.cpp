// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VNDACharacterEmotion.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

TSoftObjectPtr<UPaperSprite> UVNDACharacterEmotion::GetEmotionSprite(EEmotion Emotion) const
{
	if (const TSoftObjectPtr<UPaperSprite>* Found = EmotionTextures.Find(Emotion))
		return *Found;
	return nullptr;
}

void UVNDACharacterEmotion::PreloadAllEmotions(FSimpleDelegate OnComplete)
{
	TArray<FSoftObjectPath> Paths;
	for (const auto& Pair : EmotionTextures)
	{
		if (!Pair.Value.IsNull() && !Pair.Value.IsValid())
			Paths.Add(Pair.Value.ToSoftObjectPath());
	}

	if (Paths.Num() == 0)
	{
		OnComplete.ExecuteIfBound();
		return;
	}

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	Streamable.RequestAsyncLoad(Paths, FStreamableDelegate::CreateLambda([OnComplete]()
	{
		OnComplete.ExecuteIfBound();
	}));
}
