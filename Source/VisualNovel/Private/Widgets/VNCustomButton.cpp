// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNCustomButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UVNCustomButton::SetInfo(const int InIndex, const FText InText)
{
	Index = InIndex;
	Text = InText;
	TextBlock->SetText(Text);
}

void UVNCustomButton::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &UVNCustomButton::OnClickedButton);
}

void UVNCustomButton::OnClickedButton()
{
	OnButtonClicked.Broadcast(Index);
}
