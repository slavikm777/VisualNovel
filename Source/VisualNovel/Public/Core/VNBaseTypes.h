// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "VNBaseTypes.generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class ESide : uint8
{
	Left, 
	Right, 
	Center
};

USTRUCT(BlueprintType)
struct FDialogue : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	ESide Side = ESide::Center;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	UTexture2D* Face = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	FText Name;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueSettings")
	FText Text;
};
