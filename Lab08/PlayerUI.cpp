#include "PlayerUI.h"
#include "Texture.h"
#include "Shader.h"
#include "Game.h"
#include "Enemy.hpp"
#include "VehicleMove.hpp"
#include "Player.hpp"
#include "Renderer.h"
#include "Actor.h"

PlayerUI::PlayerUI(Actor* owner)
	:UIComponent(owner)
{
	Renderer* r = owner->GetGame()->GetRenderer();
	mLapTextures = std::vector<Texture*>{
		r->GetTexture("Assets/UI/Lap1.png"),
		r->GetTexture("Assets/UI/Lap2.png"),
		r->GetTexture("Assets/UI/Lap3.png"),
		r->GetTexture("Assets/UI/FinalLap.png"),
	};
	
	mFirstTexture = r->GetTexture("Assets/UI/1st.png");
	mSecondTexture = r->GetTexture("Assets/UI/2nd.png");
	
	mGoTexture = r->GetTexture("Assets/UI/Go.png");
	mReadyTexture = r->GetTexture("Assets/UI/Ready.png");
}

void PlayerUI::Update(float deltaTime)
{
	mGoDisplayTimer -= deltaTime;
	mLapDisplayTimer -= deltaTime;
}

void PlayerUI::Draw(Shader* shader)
{
	if (mGoDisplayTimer > 0.0f)
	{
		if (mOwner->GetState() == ActorState::Paused)
		{
			DrawTexture(shader, mReadyTexture, Vector2(0.0f, 100.0f));
		}
		else if (mOwner->GetState() == ActorState::Active)
		{
			DrawTexture(shader, mGoTexture, Vector2(0.0f, 100.0f));
		}
	}
	
	if (mLapDisplayTimer > 0.0f)
	{
		DrawTexture(shader, mLapTextures[mLapIndex], Vector2(0.0f, 200.0f), 0.75f);
	}
	
	if (mRaceState == Won)
	{
		DrawTexture(shader, mFirstTexture, Vector2(0.0f, 100.0f));
	}
	else if (mRaceState == Lost)
	{
		DrawTexture(shader, mSecondTexture, Vector2(0.0f, 100.0f));
	}
	
	// Figure out what place to show
	if (mOwner->GetState() == ActorState::Active)
	{
		bool inFirst = IsPlayerInFirst();
		if (inFirst)
		{
			DrawTexture(shader, mFirstTexture, Vector2(400.0f, 320.0f), 0.5f);
		}
		else
		{
			DrawTexture(shader, mSecondTexture, Vector2(400.0f, 320.0f), 0.5f);
		}
	}
}

void PlayerUI::OnLapChange(int lapNum)
{
	mLapIndex = lapNum - 1;
	mLapDisplayTimer = 3.0f;
}

bool PlayerUI::IsPlayerInFirst() const
{
	// TODO: Implement correctly!!
    class Player* p = mOwner->GetGame()->GetPlayer();
    class Enemy* e = mOwner->GetGame()->GetEnemy();
    
    int p_lap = p->GetComponent<VehicleMove>()->GetCurrentLap();
    int e_lap = e->GetComponent<VehicleMove>()->GetCurrentLap();
    int p_checkpoint = p->GetComponent<VehicleMove>()->GetCheckPoint();
    int e_checkpoint = e->GetComponent<VehicleMove>()->GetCheckPoint();
    
    Vector2 p_pos = Vector2(p->GetPosition().x, p->GetPosition().y);
    Vector2 e_pos = Vector2(e->GetPosition().x, e->GetPosition().y);
    float p_dist = p->GetComponent<VehicleMove>()->distToCP(p_pos, p_checkpoint);
    float e_dist = e->GetComponent<VehicleMove>()->distToCP(e_pos, e_checkpoint);
    
    if(p_lap > e_lap || p_checkpoint > e_checkpoint){
        return true;
    } else if (p_lap == e_lap && p_checkpoint == e_checkpoint){
        if(p_dist < e_dist) return true;
    } else {
        return false;
    }
}


