// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "VNBaseTypes.generated.h"

class UTexture2D;
class UVNDACharacterEmotion;

UENUM(BlueprintType)
enum class ESide : uint8
{
	Left, 
	Right, 
	Center
};

UENUM(BlueprintType)
enum class EEmotion : uint8
{
	Neutral   UMETA(DisplayName = "Нейтральный/Нейтральная"),
	Happy     UMETA(DisplayName = "Радостный/Радостная"),
	Sad       UMETA(DisplayName = "Грустный/Грустная"),
	Angry     UMETA(DisplayName = "Злой/Злая"),
	Surprised UMETA(DisplayName = "Удивлён/Удивлённая"),
	Scared    UMETA(DisplayName = "Испуган/Испуганная"),
	Embarrassment UMETA(DisplayName = "Смущение"),
	Seriousness   UMETA(DisplayName = "Серьёзность/Сосредоточенность")
};

USTRUCT(BlueprintType)
struct FDialogue : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	ESide Side = ESide::Center;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	TSoftObjectPtr<UVNDACharacterEmotion> CharacterDataAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	EEmotion Emotion = EEmotion::Neutral;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	FText Name;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	FText Text;
};
