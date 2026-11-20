// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNUserWidget.h"

void UVNUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ShowAnimation)
	{
		PlayAnimation(ShowAnimation);
	}
}
