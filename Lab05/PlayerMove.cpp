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
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState) {
    /*if (keyState[SDL_SCANCODE_LEFT]) {
        std::vector<SDL_Texture*> runLeftAnim{
            mOwner->GetGame()->GetTexture("Assets/Mario/RunLeft0.png"),
            mOwner->GetGame()->GetTexture("Assets/Mario/RunLeft1.png"),
            mOwner->GetGame()->GetTexture("Assets/Mario/RunLeft2.png")
        };
        Player_Animate("runLeft", runLeftAnim);
        SetForwardSpeed(-player_walk_speed);
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        std::vector<SDL_Texture*> runRightAnim{
            mOwner->GetGame()->GetTexture("Assets/Mario/RunRight0.png"),
            mOwner->GetGame()->GetTexture("Assets/Mario/RunRight1.png"),
            mOwner->GetGame()->GetTexture("Assets/Mario/RunRight2.png")
        };
        Player_Animate("runRight", runRightAnim);
        SetForwardSpeed(player_walk_speed);
    } else {
        std::vector<SDL_Texture*> idleAnim{
            mOwner->GetGame()->GetTexture("Assets/Mario/Idle.png"),
        };
        Player_Animate("idle", idleAnim);
        SetForwardSpeed(0);
    }*/
    
}

void PlayerMove::Update(float deltaTime){
  std::cout << "made it"<< std::endl;
  //Vector2 velocity = mDirection * GetForwardSpeed();
  //mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
  
  float cam_pos_x = mOwner->GetGame()->camera_pos.x;
  float cam_pos_y = mOwner->GetGame()->camera_pos.y;
  
  mOwner->SetPosition(Vector2(cam_pos_x + half_screen_w,
                                      cam_pos_y + half_screen_h));
  Vector2 pos = Vector2(cam_pos_x + half_screen_w,
                        cam_pos_y + half_screen_h);
  //std::cout << "pos x " << pos.x << "pos y "<< pos.y << std::endl;
  std::cout << "posx: " << mOwner->GetPosition().x << std::endl;
}


void PlayerMove::Player_Animate(std::string mAnimName, std::vector<SDL_Texture *> Anims){
    mOwner->GetComponent<AnimatedSprite>()->AddAnimation(mAnimName, Anims);
    mOwner->GetComponent<AnimatedSprite>()->SetAnimation(mAnimName);
}

