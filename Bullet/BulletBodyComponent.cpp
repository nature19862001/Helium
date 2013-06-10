#include "BulletPch.h"
#include "Bullet/BulletBodyComponent.h"
#include "Reflect/TranslatorDeduction.h"
#include "Components/TransformComponent.h"

#include "Bullet/BulletWorldComponent.h"
#include "Framework/ComponentQuery.h"

using namespace Helium;

HELIUM_IMPLEMENT_ASSET(Helium::BulletBodyComponentDefinition, Bullet, 0);

void Helium::BulletBodyComponentDefinition::PopulateStructure( Reflect::Structure& comp )
{
	comp.AddField(&BulletBodyComponentDefinition::m_BodyDefinition, "m_BodyDefinition");
}

HELIUM_DEFINE_COMPONENT(Helium::BulletBodyComponent, 32);

void Helium::BulletBodyComponent::PopulateStructure( Reflect::Structure& comp )
{

}

void Helium::BulletBodyComponent::Finalize( const BulletBodyComponentDefinition *pDefinition )
{
	BulletWorldComponent *pBulletWorldComponent = GetWorld()->GetComponents().GetFirst<BulletWorldComponent>();
	HELIUM_ASSERT( pBulletWorldComponent );

	TransformComponent *pTransform = GetComponentCollection()->GetFirst<TransformComponent>();
	HELIUM_ASSERT( pTransform );
	
	m_Body.Initialize(
		*pBulletWorldComponent->GetBulletWorld(), 
		*pDefinition->m_BodyDefinition, 
		pTransform->GetPosition(), 
		pTransform->GetRotation());
}

Helium::BulletBodyComponent::~BulletBodyComponent()
{
	if (m_Body.HasBody())
	{
		BulletWorldComponent *pBulletWorldComponent = GetWorld()->GetComponents().GetFirst<BulletWorldComponent>();

		m_Body.Destruct( *pBulletWorldComponent->GetBulletWorld() );
	}
}

void Helium::BulletBodyComponent::Impulse()
{
	m_Body.GetBody()->applyForce(btVector3(0.0f, 15.0f, 0.0f), btVector3(0.05f, 0.0f, 0.0f));
}

//////////////////////////////////////////////////////////////////////////

void DoPreProcessPhysics( BulletBodyComponent *pBodyComponent, Helium::TransformComponent *pTransformComponent )
{
	pBodyComponent->m_Body.SetPosition(pTransformComponent->GetPosition());
	pBodyComponent->m_Body.SetRotation(pTransformComponent->GetRotation());
};

HELIUM_DEFINE_TASK( PreProcessPhysics, (ForEachWorld< QueryComponents< BulletBodyComponent, TransformComponent, DoPreProcessPhysics > >) )

void PreProcessPhysics::DefineContract( Helium::TaskContract &rContract )
{
	rContract.Fulfills<Helium::StandardDependencies::ProcessPhysics>();
	rContract.ExecuteBefore<Helium::ProcessPhysics>();
}

//////////////////////////////////////////////////////////////////////////

void DoPostProcessPhysics( BulletBodyComponent *pBodyComponent, Helium::TransformComponent *pTransformComponent )
{
	Simd::Vector3 position;
	Simd::Quat rotation;

	// TODO: This extra copy is lame, either make a mutable Get on transform component or refactor motion state to talk straight to transform component
	pBodyComponent->m_Body.GetPosition(position);
	pTransformComponent->SetPosition(position);

	pBodyComponent->m_Body.GetRotation(rotation);
	pTransformComponent->SetRotation(rotation);
};

HELIUM_DEFINE_TASK( PostProcessPhysics, (ForEachWorld< QueryComponents< BulletBodyComponent, TransformComponent, DoPostProcessPhysics > >) )

void PostProcessPhysics::DefineContract( Helium::TaskContract &rContract )
{
	rContract.Fulfills<Helium::StandardDependencies::ProcessPhysics>();
	rContract.ExecuteAfter<Helium::ProcessPhysics>();
}
