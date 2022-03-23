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

	//�֐��̎��s�� Timer �����蓖�Ă�ƁA�K�� Timer Handle ���^�����܂��B
	//�J�E���g�_�E���I������ Timer ���V���b�g�_�E���ł���悤�ɂ��̃n���h������������ƈێ����܂��B
	//���Ԃ��J�E���g�_�E������֐��ƁA���̊֐����R���g���[�����邽�߂ɕK�v�� Timer Handle �� Countdown.h �̃N���X��`�ɒǉ����܂��傤�B
	//���̍�Ƃ��s�����łɁA�J�E���g�_�E���I�����ɉ������ʂȂ��Ƃ��s���֐����ǉ����܂��傤�B
	void AdvanceTimer();
	void CountdownHasFinished();
	FTimerHandle CountdownTimerHandle;
};
