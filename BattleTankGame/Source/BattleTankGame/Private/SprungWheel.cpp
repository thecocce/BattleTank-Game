// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsContraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsContraint"));
	SetRootComponent(PhysicsContraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(PhysicsContraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupContraint();

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASprungWheel::SetupContraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	if (!BodyRoot) { return; }
	PhysicsContraint->SetConstrainedComponents(
		BodyRoot,
		NAME_None,
		Axle,
		NAME_None);

	AxleWheelConstraint->SetConstrainedComponents(
		Axle,
		NAME_None,
		Wheel,
		NAME_None
	);

}



void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}