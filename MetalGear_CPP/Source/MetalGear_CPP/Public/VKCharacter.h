// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Camera/CameraComponent.h"
//#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "VKCharacter.generated.h"
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class METALGEAR_CPP_API AVKCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVKCharacter();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float value);
	void MoveLeftRight(float value);



	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;//声明一个相机组件指针
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;//声明一个弹簧臂组件指针



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
