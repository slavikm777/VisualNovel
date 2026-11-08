// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VNImageWidget.h"

#include "PaperSprite.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"

void UVNImageWidget::SetImageFromSprite(TSoftObjectPtr<UPaperSprite> InSprite)
{
	if (!Image)
	{
		return;
	}

	if (UPaperSprite* Sprite = InSprite.LoadSynchronous())
	{
		// 1. Устанавливаем кисть из спрайта без автоматического изменения размера
		Image->SetBrushFromAtlasInterface(Sprite, true);

		// 2. Получаем копию кисти, меняем размер и применяем обратно
		FSlateBrush NewBrush = Image->GetBrush();
		//NewBrush.SetImageSize(FVector2D(90.f, 256.f)); // ваши размеры
		Image->SetBrush(NewBrush);
	}
	else
	{
		Image->SetBrush(FSlateBrush());
	}
}

void UVNImageWidget::SetImageVisible(bool bVisible)
{
	if (Image)
		Image->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
