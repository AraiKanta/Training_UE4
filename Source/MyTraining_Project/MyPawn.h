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

	//4つの入力関数は入力イベントとバインドされます。
	//実行時に、新規の入力変数に格納した値を更新します。
	//この値は MyPawn がインゲームの動作を判断するために使用します
	//Input functions(入力関数)
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	//Input variables (入力変数)
	FVector CurrentVelocity;
	bool bGrowing;
};
