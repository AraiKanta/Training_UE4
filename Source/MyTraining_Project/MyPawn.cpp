// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//親子付け可能なダミーのルートコンポーネントを作成
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//カメラと可視オブジェクトを作成 
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	//カメラと可視オブジェクトをルートコンポーネントに親子付け.カメラが写す対象の位置に依存するように配置
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame 毎フレーム呼び出される
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Grow アクションに基づいて拡大と縮小を処理
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		// 1秒間に倍のサイズに成長
		CurrentScale += DeltaTime;
	}
	else
	{
		// 拡大と同じ速さで半分に縮小
		CurrentScale -= (DeltaTime * 0.5f);
	}
	//開始サイズ以下またはダブルサイズ以上にしない
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	// MoveX や MoveY 軸に基づいて移動を処理
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input 機能を入力にバインドするために呼び出されます
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Grow" key is pressed or released.
	//「Grow」キーが押されたとき、または離されたときに応答します。
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	// すべてのフレームを、2つの移動軸「MoveX」と「MoveY」の値に応答します。
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	//1秒間に前後へ 100単位移動
	//入力から受け取る値を「－1」から「＋1」の範囲に制限するために FMath::Clamp を使用します。
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	//1秒間に左右へ 100単位移動
	//入力から受け取る値を「－1」から「＋1」の範囲に制限するために FMath::Clamp を使用します。
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}