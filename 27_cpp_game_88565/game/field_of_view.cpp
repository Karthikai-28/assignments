#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <math.h>

using namespace std;

void GetShortestAngularDisplacement(float first, float second);

void GetShortestAngularDisplacement(float first, float second)
{
    180.0 - std::fabs(std::fmod(std::fabs(first - second), 360.0) - 180.0);
}

float GetTurnedToward( float currentDegrees, float goalDegrees, float maxDeltaDegrees )
{
	float displacement = GetShortestAngularDisplacement( currentDegrees, goalDegrees );

	if( displacement <= maxDeltaDegrees && displacement >= -maxDeltaDegrees )
		return goalDegrees;
	else if( displacement > maxDeltaDegrees )
		return currentDegrees+maxDeltaDegrees;
	else 
		return currentDegrees-maxDeltaDegrees;
}

//every tick check and change Enemy status
void Enemy::Update( float deltaSeconds )
{
	if( !IsAlive() )
		return;

	//check if see enemy
	Entity* visibleEnemy = m_theMap->RaycastForEnemyFaction( m_faction, m_position, ENEMY_DETECT_LENGTH );
	if( visibleEnemy!=nullptr ){//can see enemy
		m_goalPosReached = false;
		m_goalAngleReached = true;
		m_goalPos = visibleEnemy->m_position;
		CheckToShoot(deltaSeconds);		
	}
	else {//can't see enemy
		//check if see pickup
		EntityFaction oppoFaction = m_faction == FACTION_GOOD ? FACTION_EVIL : FACTION_GOOD;
		Entity* visiblePickup = m_theMap->RaycastForEnemyType( oppoFaction, ENTITY_TYPE_PICKUP, m_position, ENEMY_DETECT_LENGTH );
		if( visiblePickup != nullptr ){
			m_goalPosReached = false;
			m_goalPosReached = true;
			m_goalPos = visiblePickup->m_position;
		}
	}
	
	//move toward goal position
	if( !m_goalPosReached ){
		UpdateForGoalPosNotReached();
	}
	//Revise orientation to avoid prolonged collision with solid tiles
	if( m_goalAngleReached ){
		UpdateWhiskerDetection();
	}
	//no goal position, turn to randomized goal orientation
	if(m_goalPosReached){
		UpdateForGoalPosReached( deltaSeconds );
	}
	//check if reach goal angle
	if( m_goalOrientation == m_orientationDegrees ){
		m_goalAngleReached = true;
    }
	
	//set orientation
	m_orientationDegrees = GetTurnedToward( m_orientationDegrees, m_goalOrientation, ENEMY_TURN_SPEED * deltaSeconds );
	//set velocity
	float deltaDegreesToGoal = m_goalOrientation - m_orientationDegrees;
	if( deltaDegreesToGoal > ENEMY_FORWARD_DEGREES || deltaDegreesToGoal < -ENEMY_FORWARD_DEGREES ){
		m_velocity = .4f * m_speedLimit * Vec2::MakeFromPolarDegrees( m_orientationDegrees );
    }
	else{ 
        m_velocity = m_speedLimit * Vec2::MakeFromPolarDegrees( m_orientationDegrees );
    }
    
	//update
	Entity::Update( deltaSeconds );
}

//check if should shoot
void Enemy::CheckToShoot(float deltaSeconds)
{
	float enemyToGoalDegrees = (m_goalPos - m_position).GetAngleDegrees();
	float deltaDegreesToGoal = enemyToGoalDegrees - m_orientationDegrees;
	if( deltaDegreesToGoal<ENEMY_SHOOT_DEGREES && deltaDegreesToGoal>-ENEMY_SHOOT_DEGREES ){//could shoot
		if( m_shootCountdown <= 0.f ){
			ShootBullet();
			m_shootCountdown = ENEMY_SHOOT_COOLDOWN;
		}
		else{   //cool down
			m_shootCountdown -= deltaSeconds;
		}
	}
	else{
		m_shootCountdown = 0.f;
	}
}

//check if goal pos reached
void Enemy::UpdateForGoalPosNotReached()
{
	Vec2 enemyToPlayer = (m_goalPos - m_position);
	if( enemyToPlayer.GetLength() < m_physicsRadius ){
		m_goalPosReached = true;
	}
	else{
		m_goalOrientation = enemyToPlayer.GetAngleDegrees();
	}
}

//when goal position already reached
void Enemy::UpdateForGoalPosReached( float deltaSeconds )
{
	if( m_resetGoalOrienCountdown <= 0.f ){
		m_goalOrientation = g_theGame->m_RNG->RollRandomFloatInRange( 0.f, 360.f );
		m_resetGoalOrienCountdown = ENEMY_TURN_COUNTDOWN;
	}
	else {
        m_resetGoalOrienCountdown -= deltaSeconds;
    }
}


//Avoid constant collision with solid tiles
void Enemy::UpdateWhiskerDetection()
{
	Vec2 forward = Vec2::MakeFromPolarDegrees( m_orientationDegrees );
	Vec2 side = forward.GetRotated90Degrees();
	m_leftWhiskerResult = m_theMap->Raycast( m_position + side * m_physicsRadius, forward, 1.f );
	m_rightWhiskerResult = m_theMap->Raycast( m_position - side * m_physicsRadius, forward, 1.f );
	m_centerWhiskerResult = m_theMap->Raycast( m_position, forward, 1.f );

	if( m_leftWhiskerResult.m_impacted || m_rightWhiskerResult.m_impacted || m_centerWhiskerResult.m_impacted )	{		
		if( m_leftWhiskerResult.m_impacted && m_rightWhiskerResult.m_impacted && m_centerWhiskerResult.m_impacted ){//stuck in corner
			m_goalOrientation = -m_orientationDegrees;
			m_goalAngleReached = false;
		}
		else if( m_leftWhiskerResult.m_impacted && !m_rightWhiskerResult.m_impacted ) {//should turn right
			m_goalOrientation = m_leftWhiskerResult.m_impactNormal.GetAngleDegrees() + 70.f;
		}
		else if( m_rightWhiskerResult.m_impacted && !m_leftWhiskerResult.m_impacted ) {// should turn left
			m_goalOrientation = m_rightWhiskerResult.m_impactNormal.GetAngleDegrees() - 70.f;
		}		
		else {//both stuck
			float m_leftWhiskerRevised = m_leftWhiskerResult.m_impactNormal.GetAngleDegrees() + 70.f;
			float m_rightWhiskerRevised = m_rightWhiskerResult.m_impactNormal.GetAngleDegrees() - 70.f;
			if( m_goalPosReached ){
				if( m_leftWhiskerResult.m_impactDist < m_rightWhiskerResult.m_impactDist ){
					m_goalOrientation = m_leftWhiskerRevised;
				}
				else{
					m_goalOrientation = m_rightWhiskerRevised;
				}
			}
			else{
				float enemyToPlayerDegrees = (m_goalPos - m_position).GetAngleDegrees();
				//right better
				if( IsAbsValueBigger( GetShortestAngularDisplacement(m_leftWhiskerRevised,enemyToPlayerDegrees), 
					GetShortestAngularDisplacement(m_rightWhiskerRevised, enemyToPlayerDegrees ) ))	{
					m_goalOrientation = m_rightWhiskerRevised;
				}
				else {
                    m_goalOrientation = m_leftWhiskerRevised;
                }
			}
		}
	}
}