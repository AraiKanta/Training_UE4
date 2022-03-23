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

	//Particle System Component を追跡
	//コードでこのコンポーネントを使用する場合は、以下のようにクラスメンバ変数に保存しなくてはいけません
	UPROPERTY()
		class UParticleSystemComponent* OurParticleSystem;
	//カスタム仕様の Pawn Movement コンポーネントを使用するために、まずコンポーネントを追跡する Pawn クラスを追加します。
	UPROPERTY()
		class UCollidingPawnMovementComponent* OurMovementComponent;

	//Pawns には GetMovementComponent という関数があります。
	//この関数はエンジン内のその他のクラスが、Pawn が現在使用中の Pawn Movement コンポーネントにアクセスできるようにします。
	//カスタムの Pawn Movement コンポーネント を返すようにこの関数をオーバーライドする必要があります
	virtual UPawnMovementComponent* GetMovementComponent() const override;


	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void ParticleToggle();
};
