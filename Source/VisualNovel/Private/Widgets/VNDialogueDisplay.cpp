// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNDialogueDisplay.h"
#include "Widgets/VNDialogueBox.h"
#include "Widgets/VNCustomButton.h"
#include "Components/VerticalBox.h"
#include "Widgets/VNChoiceButtons.h"
#include "Components/Image.h"
#include "Widgets/VNImageWidget.h"

void UVNDialogueDisplay::RunDialogueTable_Implementation(UDataTable* InDialogueTable)
{
	DialogueBox->StartNewDialogue(InDialogueTable);
	NextButton = CreateWidget<UVNCustomButton>(this, ButtonClass);
	if (NextButton)
	{
		NextButton->SetInfo(0, FText::FromString("Next"));
		ButtonBox->ClearChildren();
		ButtonBox->AddChild(NextButton);
		NextButton->OnButtonClicked.AddDynamic(this, &UVNDialogueDisplay::OnNextButtonClicked);
	}
}

void UVNDialogueDisplay::RunDialogWithChoice_Implementation(const FDialogue& NewDialogue,
	const TArray<UVNBasicChoiceObject*>& InOptions)
{
	ButtonBox->ClearChildren();
	DialogueBox->SetNewDialogue(NewDialogue);
	ChoiceButtons = CreateWidget<UVNChoiceButtons>(this, ButtonChoiceClass);
	ChoiceButtons->Options = InOptions;
	ChoiceButtons->ConstructChoiceButtons(ButtonClass);
	ChoiceButtons->OnChoiceMade.AddDynamic(this, &ThisClass::OnChoiceMadeEvent);
	ButtonBox->AddChildToVerticalBox(ChoiceButtons);
}

void UVNDialogueDisplay::NativeConstruct()
{
	Super::NativeConstruct();
	if (DialogueBox)
	{
		DialogueBox->OnSpriteLoaded.AddDynamic(this, &UVNDialogueDisplay::SetImageDialogue);
	}
}

void UVNDialogueDisplay::OnNextButtonClicked(int InIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnNextButtonClicked: %d"), InIndex);
	DialogueBox->ProgressDialogue();
}

void UVNDialogueDisplay::OnChoiceMadeEvent(int ChoiceIndex)
{
	OnChoiceMade.Broadcast(ChoiceIndex);
	ChoiceButtons->RemoveFromParent();
}

void UVNDialogueDisplay::SetImageDialogue(TSoftObjectPtr<UPaperSprite> InSprite, ESide InSide)
{
	 switch (InSide)
	 {
	 case ESide::Left:
	 	ImageLeft->SetImageFromSprite(InSprite);
	 	ImageLeft->SetVisibility(ESlateVisibility::Visible);
	 	ImageRight->SetVisibility(ESlateVisibility::Hidden);
	 	break;
	 case ESide::Right:
	 	ImageRight->SetImageFromSprite(InSprite);
	 	ImageLeft->SetVisibility(ESlateVisibility::Hidden);
	 	ImageRight->SetVisibility(ESlateVisibility::Visible);
	 	break;
	 default: 
	 	ImageRight->SetVisibility(ESlateVisibility::Hidden);
	 	ImageLeft->SetVisibility(ESlateVisibility::Hidden);
	 }
}
