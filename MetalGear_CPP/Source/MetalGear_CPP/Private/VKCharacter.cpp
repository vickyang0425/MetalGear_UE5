// Fill out your copyright notice in the Description page of Project Settings.


#include "VKCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AVKCharacter::AVKCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");//��������һ�����ɱ����,���ǲ�û�а��ڸ��������
	SpringArm->SetupAttachment(RootComponent);



	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");//��������һ��������,������󶨸����ɱ����
	CameraComp->SetupAttachment(SpringArm);
	//�����������������ʵʱת�������������Լ�����ת
	this->bUseControllerRotationYaw = false;
	SpringArm->bUsePawnControlRotation = true;




}

// Called when the game starts or when spawned
void AVKCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVKCharacter::MoveForward(float value)
{
	if(Controller!=nullptr&&value!=0.0f)
	{
		FRotator Rotation = Controller->GetControlRotation();//�õ�����һ��controller����ת��

		//����ķ�������ù���������
		//FRotator YawRotation(0,Rotation.Yaw,0);//����һ���µ�rotation���͵ı���

		//������ʦ�̵ķ���������һ���µ�rotation����,����pitch��roll������Ӱ��
		FRotator RotationOnlyYaw =UKismetMathLibrary::MakeRotator(0,0, Rotation.Yaw);//�൱����ͼ���MakeRotator�ڵ㣬����Ҫ��ͷ�ļ�

		//��rotationת���ɾ���ͨ�������������X�᷽�������
		FVector Dir = FRotationMatrix(RotationOnlyYaw).GetUnitAxis(EAxis::X);

		AddMovementInput(Dir, value);
		
	}

}

void AVKCharacter::MoveLeftRight(float value)
{
	if(Controller!=nullptr&&value!=0.0f)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator RotationOnlyYaw = UKismetMathLibrary::MakeRotator(0,0, Rotation.Yaw);
		FVector Dir = FRotationMatrix(RotationOnlyYaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Dir, value);
	}

}

// Called every frame
void AVKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVKCharacter::MoveForward);//���������value����һ�������ľͿ���ֱ����������ʹ�ö��һ�ֻ�ṩ���������ɣ����ø�����������֣�������ʦ
	PlayerInputComponent->BindAxis("MoveRight",this,&AVKCharacter::MoveLeftRight);// ����ʱֻ�������������ʵ��ϵͳ�����Ÿ����ĺ�����ȥ�����������ڵĵط����ú���




	
	PlayerInputComponent->BindAxis("TurnLandR",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpDown", this, &APawn::AddControllerPitchInput);


}

