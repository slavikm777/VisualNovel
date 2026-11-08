// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNDialogueBox.h"
#include "Components/TextBlock.h"
#include "Core/VNDACharacterEmotion.h"
#include "Components/Image.h"


void UVNDialogueBox::SetNewDialogue_Implementation(const FDialogue& NewDialogue)
{
	if (!NewDialogue.Name.IsEmpty())
		TextName->SetText(NewDialogue.Name);
	TextBlock->SetText(NewDialogue.Text);
	
	FlipImage(ImageTextBlockBorder, NewDialogue.Side == ESide::Right);

	const TSoftObjectPtr<UVNDACharacterEmotion>& SoftDA = NewDialogue.CharacterDataAsset;

	// 1. На входе пустой DA — используем уже загруженный
	if (SoftDA.IsNull())
	{
		if (CurrentCharacterDataAsset)
		{
			OnSpriteLoaded.Broadcast(CurrentCharacterDataAsset->GetEmotionSprite(NewDialogue.Emotion), NewDialogue.Side);
		}
		else
		{
			OnSpriteLoaded.Broadcast(nullptr, NewDialogue.Side);
		}
		return;
	}

	// 2. DA уже в памяти и совпадает с текущим — ничего не грузим
	if (UVNDACharacterEmotion* Loaded = SoftDA.Get())
	{
		if (Loaded == CurrentCharacterDataAsset)
		{
			OnSpriteLoaded.Broadcast(Loaded->GetEmotionSprite(NewDialogue.Emotion), NewDialogue.Side);
			return;
		}
		
		CurrentCharacterDataAsset = Loaded;
		OnSpriteLoaded.Broadcast(Loaded->GetEmotionSprite(NewDialogue.Emotion), NewDialogue.Side);
		return;
	}

	// 3. DA ещё не в памяти — грузим
	if (UVNDACharacterEmotion* Loaded = SoftDA.LoadSynchronous())
	{
		CurrentCharacterDataAsset = Loaded;
		OnSpriteLoaded.Broadcast(Loaded->GetEmotionSprite(NewDialogue.Emotion), NewDialogue.Side);
	}
	else
	{
		// Путь битый — оставляем то, что было
		UE_LOG(LogTemp, Warning, TEXT("VNDialogueBox: failed to load CharacterDataAsset '%s'"), *SoftDA.ToSoftObjectPath().ToString());

		if (CurrentCharacterDataAsset)
		{
			OnSpriteLoaded.Broadcast(
				CurrentCharacterDataAsset->GetEmotionSprite(NewDialogue.Emotion), NewDialogue.Side);
		}
		else
		{
			OnSpriteLoaded.Broadcast(nullptr,NewDialogue.Side);
		}
	}
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
