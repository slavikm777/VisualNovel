// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNDialogueBox.h"
#include "Components/TextBlock.h"


void UVNDialogueBox::SetNewDialogue_Implementation(const FDialogue& NewDialogue)
{
	if (!NewDialogue.Name.IsEmpty())
		TextName->SetText(NewDialogue.Name);
	TextBlock->SetText(NewDialogue.Text);
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

void UVNDialogueBox::RunDialogueTable_Implementation(UDataTable* InDialogueTable)
{
	StartNewDialogue(InDialogueTable);
}
