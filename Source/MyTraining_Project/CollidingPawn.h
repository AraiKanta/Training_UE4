// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class MYTRAINING_PROJECT_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Particle System Component ��ǐ�
	//�R�[�h�ł��̃R���|�[�l���g���g�p����ꍇ�́A�ȉ��̂悤�ɃN���X�����o�ϐ��ɕۑ����Ȃ��Ă͂����܂���
	UPROPERTY()
		class UParticleSystemComponent* OurParticleSystem;
	//�J�X�^���d�l�� Pawn Movement �R���|�[�l���g���g�p���邽�߂ɁA�܂��R���|�[�l���g��ǐՂ��� Pawn �N���X��ǉ����܂��B
	UPROPERTY()
		class UCollidingPawnMovementComponent* OurMovementComponent;

	//Pawns �ɂ� GetMovementComponent �Ƃ����֐�������܂��B
	//���̊֐��̓G���W�����̂��̑��̃N���X���APawn �����ݎg�p���� Pawn Movement �R���|�[�l���g�ɃA�N�Z�X�ł���悤�ɂ��܂��B
	//�J�X�^���� Pawn Movement �R���|�[�l���g ��Ԃ��悤�ɂ��̊֐����I�[�o�[���C�h����K�v������܂�
	virtual UPawnMovementComponent* GetMovementComponent() const override;


	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void ParticleToggle();
};
