#include "pch.h"
#include "MovementComponent.h"

#include"Input.h"

float MovementComponent::dashElapsedTime = 0;
Vector2D MovementComponent::Move(Vector2D vec)
{
	m_move = vec * m_moveSpeed;
	return m_move;
}

Vector2D MovementComponent::Jump()
{
	m_move = Vector2D(0, -1) * m_jumpPower;
	return m_move;
}

Vector2D MovementComponent::Dash(Vector2D vec)
{
	
	vec.Normalize();
	m_move = vec * m_dashSpeed;
	return m_move;
}




void MovementComponent::AddLocation()
{
	m_pParentComponent->AddRelativeTranslation(m_move);
}
