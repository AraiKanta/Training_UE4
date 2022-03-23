// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;
    CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	
    //新しく更新した関数の呼び出しを追加して ACountdown::BeginPlay のテキスト表示を初期化します。
    //そして 1 秒に一回カウントダウンを進め、更新を行うタイマーを設定します。
    UpdateTimerDisplay();
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//ACountdown::UpdateTimerDisplay はテキスト表示を更新して、残り時間、または時間切れの場合はゼロを表示します。
//ゲームに ACountdown を初めてスポーンした時にこのコードを実行して、 CountdownTime 変数がゼロになるまで 1 秒に一回コードを実行します。
void ACountdown::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        //We're done counting down, so stop running the timer.
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void ACountdown::CountdownHasFinished()
{
    //Change to a special readout
    CountdownText->SetText(TEXT("GO!"));
}