// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//�e�q�t���\�ȃ_�~�[�̃��[�g�R���|�[�l���g���쐬
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//�J�����Ɖ��I�u�W�F�N�g���쐬 
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	//�J�����Ɖ��I�u�W�F�N�g�����[�g�R���|�[�l���g�ɐe�q�t��.�J�������ʂ��Ώۂ̈ʒu�Ɉˑ�����悤�ɔz�u
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

// Called every frame ���t���[���Ăяo�����
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Grow �A�N�V�����Ɋ�Â��Ċg��Ək��������
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		// 1�b�Ԃɔ{�̃T�C�Y�ɐ���
		CurrentScale += DeltaTime;
	}
	else
	{
		// �g��Ɠ��������Ŕ����ɏk��
		CurrentScale -= (DeltaTime * 0.5f);
	}
	//�J�n�T�C�Y�ȉ��܂��̓_�u���T�C�Y�ȏ�ɂ��Ȃ�
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	// MoveX �� MoveY ���Ɋ�Â��Ĉړ�������
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input �@�\����͂Ƀo�C���h���邽�߂ɌĂяo����܂�
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Grow" key is pressed or released.
	//�uGrow�v�L�[�������ꂽ�Ƃ��A�܂��͗����ꂽ�Ƃ��ɉ������܂��B
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	// ���ׂẴt���[�����A2�̈ړ����uMoveX�v�ƁuMoveY�v�̒l�ɉ������܂��B
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	//1�b�ԂɑO��� 100�P�ʈړ�
	//���͂���󂯎��l���u�|1�v����u�{1�v�͈̔͂ɐ������邽�߂� FMath::Clamp ���g�p���܂��B
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	//1�b�Ԃɍ��E�� 100�P�ʈړ�
	//���͂���󂯎��l���u�|1�v����u�{1�v�͈̔͂ɐ������邽�߂� FMath::Clamp ���g�p���܂��B
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