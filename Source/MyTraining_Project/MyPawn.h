#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class MYTRAINING_PROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	//4�̓��͊֐��͓��̓C�x���g�ƃo�C���h����܂��B
	//���s���ɁA�V�K�̓��͕ϐ��Ɋi�[�����l���X�V���܂��B
	//���̒l�� MyPawn ���C���Q�[���̓���𔻒f���邽�߂Ɏg�p���܂�
	//Input functions(���͊֐�)
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	//Input variables (���͕ϐ�)
	FVector CurrentVelocity;
	bool bGrowing;
};
