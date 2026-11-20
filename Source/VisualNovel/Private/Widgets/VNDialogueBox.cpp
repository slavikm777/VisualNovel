// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNDialogueBox.h"
#include "Components/TextBlock.h"
#include "Core/VNDACharacterEmotion.h"
#include "Components/Image.h"


void UVNDialogueBox::SetNewDialogue_Implementation(const FDialogue& NewDialogue)
{
	const TSoftObjectPtr<UVNDACharacterEmotion>& SoftDA = NewDialogue.CharacterDataAsset;
	UVNDACharacterEmotion* CharacterDA = CurrentCharacterDataAsset;

	if (!SoftDA.IsNull())
	{
		if (UVNDACharacterEmotion* Loaded = SoftDA.Get())
		{
			CharacterDA = Loaded;
		}
		else if (UVNDACharacterEmotion* Loaded1 = SoftDA.LoadSynchronous())
		{
			CharacterDA = Loaded1;
		}
	}

	CurrentCharacterDataAsset = CharacterDA;
	
	TextBlock->SetText(NewDialogue.Text);
	FlipImage(ImageTextBlockBorder, NewDialogue.Side == ESide::Right);

	
	if (NewDialogue.HideName)
	{
		TextName->SetText(NewDialogue.CharacterName);
	}
	else
	{
		const FText DisplayName = CharacterDA? CharacterDA->GetNameCharacter() : NewDialogue.CharacterName; 

		TextName->SetText(DisplayName);
	}
	
	OnSpriteLoaded.Broadcast(
		CharacterDA ? CharacterDA->GetEmotionSprite(NewDialogue.Emotion) : nullptr,
		NewDialogue.Side);
}

void UVNDialogueBox::StartNewDialogue_Implementation(UDataTable* InDialogueTable)
{
	DialogueTable = InDialogueTable;
	Index = 0;
	ProgressDialogue();
}

void UVNDialogueBox::ProgressDialogue()
{
	if (HaveNextDialogue())
	{
		UE_LOG(LogTemp, Error, TEXT("SetNewDialogue: Диалог существует"));
		SetNewDialogue(GetNextDialogue());
		Index++;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnDialogueFinished: Диалог закончен"));
		OnDialogueFinished.Broadcast();
	}
}

bool UVNDialogueBox::HaveNextDialogue()
{
	if (!DialogueTable) return false;

	if (DialogueTable)
	{
		TArray<FDialogue*> AllDialogues;
		DialogueTable->GetAllRows<FDialogue>(TEXT("HaveNextDialogue"), AllDialogues);
		if (AllDialogues.Num() > Index)
			return true;
	}
	return false;
}

FDialogue UVNDialogueBox::GetNextDialogue()
{
	if (!DialogueTable) return FDialogue();

	if (DialogueTable)
	{
		TArray<FDialogue*> AllDialogues;
		DialogueTable->GetAllRows<FDialogue>(TEXT("HaveNextDialogue"), AllDialogues);
		if (AllDialogues.IsValidIndex(Index))
		{
			return *AllDialogues[Index];
		}
	}

	return FDialogue();
}

void UVNDialogueBox::FlipImage(UImage* Image, bool bFlip)
{
	FWidgetTransform CurrentTransform = Image->GetRenderTransform();
	CurrentTransform.Scale.X = bFlip ? -1.0f : 1.0f;
	Image->SetRenderTransform(CurrentTransform);
}

void UVNDialogueBox::RunDialogueTable_Implementation(UDataTable* InDialogueTable)
{
	StartNewDialogue(InDialogueTable);
}
