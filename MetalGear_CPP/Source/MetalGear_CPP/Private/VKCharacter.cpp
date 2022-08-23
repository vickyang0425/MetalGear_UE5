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
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");//真正创建一个弹簧臂组件,但是并没有绑定在根组件下面
	SpringArm->SetupAttachment(RootComponent);



	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");//真正创建一个相机组件,把相机绑定给弹簧臂组件
	CameraComp->SetupAttachment(SpringArm);
	//控制是人物随着鼠标实时转，还是人物有自己的旋转
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
		FRotator Rotation = Controller->GetControlRotation();//拿到的是一个controller的旋转量

		//下面的方法是虚幻官网给出的
		//FRotator YawRotation(0,Rotation.Yaw,0);//创建一个新的rotation类型的变量

		//这是老师教的方法，创建一个新的rotation变量,消除pitch和roll带来的影响
		FRotator RotationOnlyYaw =UKismetMathLibrary::MakeRotator(0,0, Rotation.Yaw);//相当于蓝图里的MakeRotator节点，但是要加头文件

		//将rotation转换成矩阵，通过矩阵求得面向X轴方向的向量
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

	PlayerInputComponent->BindAxis("MoveForward", this, &AVKCharacter::MoveForward);//好像参数是value且是一个参数的就可以直接在这里面使用而且还只提供函数名即可，不用给参数，好奇怪？问王老师
	PlayerInputComponent->BindAxis("MoveRight",this,&AVKCharacter::MoveLeftRight);// 调用时只需给出函数名，实际系统会随着给出的函数名去函数真正存在的地方调用函数




	
	PlayerInputComponent->BindAxis("TurnLandR",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpDown", this, &APawn::AddControllerPitchInput);


}

