#include "SPBoids.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASPBoids::ASPBoids()
{
	m_Boids = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Boids"));
	m_Boids->bEditableWhenInherited = true;

	m_Radius = 5000;
	m_Amount = 30;
	m_StartSpeed = 100;
	m_MinSpeed = 100;
	m_MaxSpeed = 3000;
	m_CohesionMult = 0.1f;
	m_AlignmentMult = 0.01f;
	m_SeparationMult = 2000;
	m_TargetMult = 300;
	m_Target = FVector::ZeroVector;
	m_IterationIndex = 0;
}

void ASPBoids::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	Super::BeginPlay();
	SpawnBoids();
}

void ASPBoids::SpawnBoids()
{
	m_Boids->ClearInstances();
	m_Velocities.Empty();

	for (size_t i = 0; i < m_Amount; i++)
	{
		FVector position = UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(0.2f, 1) * m_Radius;
		FRotator rotation = UKismetMathLibrary::RandomRotator();
		FVector scale = UKismetMathLibrary::RandomFloat() * FVector::OneVector;
		FTransform transform = FTransform(rotation, position, scale);

		m_Boids->AddInstance(transform);
		m_Velocities.Add(rotation.Vector() * m_StartSpeed);
	}
}

void ASPBoids::UpdateBoids(float DeltaTime)
{
	UpdateVelocities(DeltaTime);
	UpdatePositions(DeltaTime);
}

void ASPBoids::UpdateVelocities(float DeltaTime)
{
	m_IterationIndex++;
	if (m_IterationIndex >= m_Amount)
		m_IterationIndex = 0;

	FTransform Current;
	m_Boids->GetInstanceTransform(m_IterationIndex, Current);
	FVector Center = Current.GetLocation();
	FVector Alignment = m_Velocities[m_IterationIndex] * m_AlignmentMult;

	for (size_t i = 0; i < m_Amount; i++)
	{
		if (i == m_IterationIndex)
			continue;

		FTransform Local;
		m_Boids->GetInstanceTransform(i, Local);

		FVector MyPos = Local.GetLocation();
		FVector Dir = Center - MyPos;
		FVector Separation = (Dir / Dir.SizeSquared()) * m_SeparationMult;
		FVector Cohesion = (Center - MyPos) * m_CohesionMult;
		FVector TargetDir = (m_Target - (GetActorLocation() + MyPos)).GetSafeNormal() * m_TargetMult;
		FVector Force = Separation + Alignment + Cohesion + TargetDir;
		m_Velocities[i] = UKismetMathLibrary::ClampVectorSize(m_Velocities[i] + Force * DeltaTime, m_MinSpeed, m_MaxSpeed);
	}
}

void ASPBoids::UpdatePositions(float DeltaTime)
{
	for (size_t i = 0; i < m_Amount; i++)
	{
		FTransform Transform;
		m_Boids->GetInstanceTransform(i, Transform);
		FVector Velocity = m_Velocities[i];

		Transform.SetLocation(Transform.GetLocation() + Velocity * DeltaTime);
		Transform.SetRotation(UKismetMathLibrary::MakeRotFromZ(Velocity).Quaternion());
		m_Boids->UpdateInstanceTransform(i, Transform, false);
	}
}

void ASPBoids::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateBoids(DeltaTime);
}