// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"
//コリジョン形状を視覚的に表現する Static Mesh コンポーネント
#include "UObject/ConstructorHelpers.h"
//意図的にオン/オフに出来る Particle System コンポーネント
#include "Particles/ParticleSystemComponent.h"
//物理ワールドとインタラクションを行う Sphere コンポーネント
#include "Components/SphereComponent.h"
//インゲーム パースペクティブをコントロールするために Camera コンポーネント を親子付けして使用できる Spring Arm コンポーネント
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponet = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("RootComponet"));
	RootComponent = SphereComponet;
	SphereComponet->InitSphereRadius(40.0f);
	SphereComponet->SetCollisionProfileName(TEXT("Pawn"));

	//半径 50 の Static Mesh アセットから目に見えるスフィアを作成してこれを親子付けします。
	// 直前に作成した半径 40 の Sphere コンポーネントと完全にそろわないので、80 ％に縮小します。
	// さらに、中心を Sphere コンポーネントの中心と並べるために 40 単位移動させなくてはいけません。
	// 球体の位置が分かるようにメッシュ コンポーネントを作成して配置します
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	//階層に非アクティブな Particle System コンポーネントの親子付けができるようになりました。
	//このコンポーネントはコードで操作可能で、後にオン/オフを切り替える入力を設定することができます。
	//Particle System コンポーネントはルートにではなく Static Mesh コンポーネントに直接親子付けできることに注目してください。
	//プレイ中の表示をより見やすくするために、メッシュの下部中央から少しだけオフセットしています。
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	//Spring Arm コンポーネントは、追跡しているポーンよりもゆっくりとカメラを加速したり減速させるため、よりスムーズな固定点を作成します。
	//サードパーソン ゲームでプレイヤーがコーナーへ追いつめられる状況など、カメラがソリッドなオブジェクトを通り抜けてしまうことを防止する内蔵機能も備わっています。
	//必須ではありませんが、ゲーム内のカメラワークにスムースな感覚を作成する迅速かつ簡単な方法です。
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	//Camera コンポーネントは作成が簡単であり、ユースケース用に特別な設定をする必要はありません。
	//Spring Arm Component コンポーネントには、ベース以外に親子付けが出来る特別な内蔵ソケットがあります。
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//ポーンをデフォルト プレイヤーがコントロールするように設定します。
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

