// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"
//�R���W�����`������o�I�ɕ\������ Static Mesh �R���|�[�l���g
#include "UObject/ConstructorHelpers.h"
//�Ӑ}�I�ɃI��/�I�t�ɏo���� Particle System �R���|�[�l���g
#include "Particles/ParticleSystemComponent.h"
//�������[���h�ƃC���^���N�V�������s�� Sphere �R���|�[�l���g
#include "Components/SphereComponent.h"
//�C���Q�[�� �p�[�X�y�N�e�B�u���R���g���[�����邽�߂� Camera �R���|�[�l���g ��e�q�t�����Ďg�p�ł��� Spring Arm �R���|�[�l���g
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

	//���a 50 �� Static Mesh �A�Z�b�g����ڂɌ�����X�t�B�A���쐬���Ă����e�q�t�����܂��B
	// ���O�ɍ쐬�������a 40 �� Sphere �R���|�[�l���g�Ɗ��S�ɂ����Ȃ��̂ŁA80 ���ɏk�����܂��B
	// ����ɁA���S�� Sphere �R���|�[�l���g�̒��S�ƕ��ׂ邽�߂� 40 �P�ʈړ������Ȃ��Ă͂����܂���B
	// ���̂̈ʒu��������悤�Ƀ��b�V�� �R���|�[�l���g���쐬���Ĕz�u���܂�
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	//�K�w�ɔ�A�N�e�B�u�� Particle System �R���|�[�l���g�̐e�q�t�����ł���悤�ɂȂ�܂����B
	//���̃R���|�[�l���g�̓R�[�h�ő���\�ŁA��ɃI��/�I�t��؂�ւ�����͂�ݒ肷�邱�Ƃ��ł��܂��B
	//Particle System �R���|�[�l���g�̓��[�g�ɂł͂Ȃ� Static Mesh �R���|�[�l���g�ɒ��ڐe�q�t���ł��邱�Ƃɒ��ڂ��Ă��������B
	//�v���C���̕\������茩�₷�����邽�߂ɁA���b�V���̉����������班�������I�t�Z�b�g���Ă��܂��B
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	//Spring Arm �R���|�[�l���g�́A�ǐՂ��Ă���|�[�������������ƃJ���������������茸�������邽�߁A���X���[�Y�ȌŒ�_���쐬���܂��B
	//�T�[�h�p�[�\�� �Q�[���Ńv���C���[���R�[�i�[�֒ǂ��߂���󋵂ȂǁA�J�������\���b�h�ȃI�u�W�F�N�g��ʂ蔲���Ă��܂����Ƃ�h�~��������@�\��������Ă��܂��B
	//�K�{�ł͂���܂��񂪁A�Q�[�����̃J�������[�N�ɃX���[�X�Ȋ��o���쐬����v�����ȒP�ȕ��@�ł��B
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	//Camera �R���|�[�l���g�͍쐬���ȒP�ł���A���[�X�P�[�X�p�ɓ��ʂȐݒ������K�v�͂���܂���B
	//Spring Arm Component �R���|�[�l���g�ɂ́A�x�[�X�ȊO�ɐe�q�t�����o������ʂȓ����\�P�b�g������܂��B
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//�|�[�����f�t�H���g �v���C���[���R���g���[������悤�ɐݒ肵�܂��B
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

