// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "Gun.h"


// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-13.f, -9.f, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	MeshArms = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MeshArms"));
	MeshArms->SetupAttachment(FirstPersonCameraComponent);
	MeshArms->bOnlyOwnerSee = true; // Only visible by the Player.
	MeshArms->bCastDynamicShadow = false;
	MeshArms->CastShadow = false;
	MeshArms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	MeshArms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ensure(GunBlueprint)) { return; }
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	/* Correctly attach the Gun: AI or Player */
	if (IsPlayerControlled()) { // GetController()->GetClass()->IsChildOf<AAIController>()
		Gun->AttachToComponent(MeshArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->FirstPersonAnimInstance = MeshArms->GetAnimInstance();
	} else {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("GripPoint"));
		Gun->ThirdPersonAnimInstance = GetMesh()->GetAnimInstance();
	}
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AThirdPersonCharacter::PullTrigger);
}

void AThirdPersonCharacter::UnPossessed() {
	Super::UnPossessed();
	if (!Gun) { return; }
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("GripPoint"));
}

void AThirdPersonCharacter::PullTrigger() {
	if(!Gun) { return; }
	Gun->OnFire();

}

