// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Countdown.generated.h"

UCLASS()
class MYTRAINING_PROJECT_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 CountdownTime;
	UTextRenderComponent* CountdownText;
	void UpdateTimerDisplay();

	//関数の実行に Timer を割り当てると、必ず Timer Handle が与えられます。
	//カウントダウン終了時に Timer をシャットダウンできるようにこのハンドルをしっかりと維持します。
	//時間をカウントダウンする関数と、この関数をコントロールするために必要な Timer Handle を Countdown.h のクラス定義に追加しましょう。
	//この作業を行うついでに、カウントダウン終了時に何か特別なことを行う関数も追加しましょう。
	void AdvanceTimer();
	void CountdownHasFinished();
	FTimerHandle CountdownTimerHandle;
};
