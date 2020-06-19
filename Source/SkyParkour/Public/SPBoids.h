#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPBoids.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class SKYPARKOUR_API ASPBoids : public AActor
{
	GENERATED_BODY()

public:
	ASPBoids();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Boids")
		UHierarchicalInstancedStaticMeshComponent* m_Boids;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		int m_Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		int m_Amount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_StartSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_MinSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_MaxSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_CohesionMult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_AlignmentMult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_SeparationMult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		float m_TargetMult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boids")
		FVector m_Target;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Boids")
	FVector m_BoidCenter;

	FVector m_BoidCenterCounter;

	int m_IterationIndex;

	TArray<FVector> m_Velocities;

	void SpawnBoids();

	void UpdateBoids(float DeltaTime);

	void UpdateVelocities(float DeltaTime);

	void UpdatePositions(float DeltaTime);

public:
	virtual void Tick(float DeltaTime) override;

};
