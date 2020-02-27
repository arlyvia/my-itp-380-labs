//
//  PlayerMove.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "PlayerMove.hpp"
#include "MoveComponent.h"
#include "Math.h"
#include "CollisionComponent.h"
#include "Collider.hpp"
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState) {
    
    if(keyState[SDL_SCANCODE_LEFT]){
        mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
        //mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkLeft");
        SetForwardSpeed(player_walk_speed);
        mDirection=Vector2(-1,0);
        std::vector<SDL_Texture*> walkLeftAnim{
             mOwner->GetGame()->GetTexture("Assets/Link/WalkLeft0.png"),
             mOwner->GetGame()->GetTexture("Assets/Link/WalkLeft1.png")
        };
        Player_Animate("walkLeft", walkLeftAnim);
    } else if(keyState[SDL_SCANCODE_RIGHT]){
        mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
        //mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkRight");
        SetForwardSpeed(player_walk_speed);
        mDirection=Vector2(1,0);
        std::vector<SDL_Texture*> walkRightAnim{
             mOwner->GetGame()->GetTexture("Assets/Link/WalkRight0.png"),
             mOwner->GetGame()->GetTexture("Assets/Link/WalkRight1.png")
        };
        Player_Animate("walkRight", walkRightAnim);
    } else if(keyState[SDL_SCANCODE_UP]){
        mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
        //mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkUp");
        SetForwardSpeed(player_walk_speed);
        mDirection=Vector2(0, -1);
        std::vector<SDL_Texture*> walkUpAnim{
             mOwner->GetGame()->GetTexture("Assets/Link/WalkUp0.png"),
             mOwner->GetGame()->GetTexture("Assets/Link/WalkUp1.png")
        };
        Player_Animate("walkUp", walkUpAnim);
    } else if(keyState[SDL_SCANCODE_DOWN]){
        mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(false);
        //mOwner->GetComponent<AnimatedSprite>()->SetAnimation("walkDown");
        SetForwardSpeed(player_walk_speed);
        mDirection=Vector2(0, 1);
        std::vector<SDL_Texture*> walkDownAnim{
             mOwner->GetGame()->GetTexture("Assets/Link/WalkDown0.png"),
             mOwner->GetGame()->GetTexture("Assets/Link/WalkDown1.png")
        };
        Player_Animate("walkDown", walkDownAnim);
    } else {
        mOwner->GetComponent<AnimatedSprite>()->SetIsPaused(true);
        SetForwardSpeed(0);
    }
    
}

void PlayerMove::Update(float deltaTime){
    Vector2 velocity = mDirection * GetForwardSpeed();
    mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
  
    float cam_pos_x = mOwner->GetPosition().x;
    float cam_pos_y = mOwner->GetPosition().y;

    Vector2 pos = Vector2(cam_pos_x - half_screen_w,
                        cam_pos_y - half_screen_h);
    mOwner->GetGame()->camera_pos = pos;

    Vector2 local_offset(0, 0);
    for(int i=0; i < (signed)mOwner->GetGame()->mColliders.size(); i++){
      CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mColliders[i]->GetComponent<CollisionComponent>(), local_offset);
      if(side != CollSide::None){
          mOwner->SetPosition(mOwner->GetPosition()+local_offset);
          SetForwardSpeed(0);
          mOwner->GetGame()->camera_pos = mOwner->GetGame()->camera_pos+local_offset;
      }
    }
    
}


void PlayerMove::Player_Animate(std::string mAnimName, std::vector<SDL_Texture *> Anims){
    mOwner->GetComponent<AnimatedSprite>()->AddAnimation(mAnimName, Anims);
    mOwner->GetComponent<AnimatedSprite>()->SetAnimation(mAnimName);
}

