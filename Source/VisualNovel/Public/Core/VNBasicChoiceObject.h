// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VNBasicChoiceObject.generated.h"


UCLASS(BlueprintType, Blueprintable)
class VISUALNOVEL_API UVNBasicChoiceObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bCanChoice;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bWasChosen;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FText ChoiceName;
};
