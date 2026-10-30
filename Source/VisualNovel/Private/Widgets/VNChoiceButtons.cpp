// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNChoiceButtons.h"
#include "Widgets/VNCustomButton.h"
#include "Core/VNBasicChoiceObject.h"
#include "Components/VerticalBox.h"

void UVNChoiceButtons::ConstructChoiceButtons(TSubclassOf<UVNCustomButton> InClassButton)
{
	if (!ButtonBox || !InClassButton)
	{
		return;
	}

	ButtonBox->ClearChildren();

	for (int32 i = 0; i < Options.Num()-1; ++i)
	{
		UVNBasicChoiceObject* Choice = Options[i];
		if (!Choice || !Choice->bCanChoice)
		{
			continue;
		}

		UVNCustomButton* ButtonChoice = CreateWidget<UVNCustomButton>(this, InClassButton);
		if (!ButtonChoice)
		{
			continue;
		}

		ButtonChoice->SetInfo(i, Choice->ChoiceName);
		ButtonBox->AddChildToVerticalBox(ButtonChoice);
		ButtonChoice->OnButtonClicked.AddDynamic(this, &ThisClass::HandleChoice);
	}
}

void UVNChoiceButtons::HandleChoice(int ChoiceIndex)
{
	OnChoiceMade.Broadcast(ChoiceIndex);
}
