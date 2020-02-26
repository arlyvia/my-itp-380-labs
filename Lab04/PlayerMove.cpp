//
//  PlayerMove.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "PlayerMove.hpp"
#include "MoveComponent.h"
#include "Goomba.hpp"
#include "Math.h"
#include "CollisionComponent.h"
#include "Block.hpp"
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState) {
    if (keyState[SDL_SCANCODE_LEFT]) {
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
    }
    
    if(keyState[SDL_SCANCODE_SPACE]){
        if(!last_frame && keyState[SDL_SCANCODE_SPACE] && !mInAir){
            mYSpeed = -700.0f;
            mInAir = true;
            Mix_Chunk* jump_sound = mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav");
            if(Mix_PlayChannel(-1, jump_sound, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
        if(GetForwardSpeed() > 0){
             std::vector<SDL_Texture*> jumpRightAnim{
                   mOwner->GetGame()->GetTexture("Assets/Mario/JumpRight.png"),
             };
             Player_Animate("jumpRight", jumpRightAnim);
        } else if(GetForwardSpeed() < 0){
            std::vector<SDL_Texture*> jumpLeftAnim{
                  mOwner->GetGame()->GetTexture("Assets/Mario/JumpLeft.png"),
            };
            Player_Animate("jumpLeft", jumpLeftAnim);
        } else {
            std::string curr_anim = mOwner->GetComponent<AnimatedSprite>()->GetAnimName();
            if(curr_anim == "runRight" ||
               curr_anim == "jumpRight" ||
               curr_anim == "idle"){
                std::vector<SDL_Texture*> jumpRightAnim{
                      mOwner->GetGame()->GetTexture("Assets/Mario/JumpRight.png"),
                };
                Player_Animate("jumpRight", jumpRightAnim);
            } else {
                std::vector<SDL_Texture*> jumpLeftAnim{
                      mOwner->GetGame()->GetTexture("Assets/Mario/JumpLeft.png"),
                };
                Player_Animate("jumpLeft", jumpLeftAnim);
            }
        }
    }
    
    last_frame = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::Update(float deltaTime){
    Vector2 velocity = mOwner->GetForward() * GetForwardSpeed();
    mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
    
    mYSpeed = mYSpeed + 1500.0f * deltaTime;
    
    Vector2 local_offset(0, 0);
    for(int i=0; i < (signed)mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>(), local_offset);
        
        if(side != CollSide::None){
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = 0;
                mInAir = false;
            } else if(side == CollSide::Bottom && mYSpeed < 0.0f){
                mOwner->SetPosition(mOwner->GetPosition()-local_offset);
                mYSpeed = 0;
                mInAir = false;
                Mix_Chunk* bump_sound = mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav");
                if(Mix_PlayChannel(-1, bump_sound, 0)==-1) {
                    printf("Mix_PlayChannel: %s\n",Mix_GetError());
                }
            }else if(side == CollSide::Left){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
            } else if(side == CollSide::Right){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
            }
        }
    }
    
    for(int i=0; i < (signed)mOwner->GetGame()->mEnemies.size(); i++){
        CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mEnemies[i]->GetComponent<CollisionComponent>(), local_offset);
        
        if(side != CollSide::None){
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = -jump_speed;
                mInAir = true;
                
                mOwner->GetGame()->mEnemies[i]->stomp();
                Mix_Chunk* stomp_sound = mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav");
                if(Mix_PlayChannel(-1, stomp_sound, 0)==-1) {
                    printf("Mix_PlayChannel: %s\n",Mix_GetError());
                }
                
            } else if(side == CollSide::Left && mInAir){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = -jump_speed;
                mOwner->GetGame()->mEnemies[i]->stomp();
                
            } else if(side == CollSide::Right && mInAir){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = -jump_speed;
                mOwner->GetGame()->mEnemies[i]->stomp();
                
            }else {
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                std::vector<SDL_Texture*> deadAnim{
                      mOwner->GetGame()->GetTexture("Assets/Mario/Dead.png"),
                };
                Player_Animate("dead", deadAnim);
                mOwner->SetState(ActorState::Paused);
                Mix_HaltChannel(mOwner->GetGame()->mChannel);
                Mix_Chunk* dead_sound = mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav");
                int channel = Mix_PlayChannel(-1, dead_sound, 0);
                if(channel ==-1) {
                    printf("Mix_PlayChannel: %s\n",Mix_GetError());
                }
            }
        }
    }

    if(mOwner->GetPosition().y < bottom_of_screen){
        Vector2 velocity_y(0, mYSpeed);
        mOwner->SetPosition(mOwner->GetPosition() + velocity_y * deltaTime);
    } else {
        if(mOwner->GetPosition().y > bottom_of_screen+1.0f){
            mOwner->SetPosition(mOwner->GetPosition()+local_offset);
            std::vector<SDL_Texture*> deadAnim{
                  mOwner->GetGame()->GetTexture("Assets/Mario/Dead.png"),
            };
            Player_Animate("dead", deadAnim);
            Mix_HaltChannel(mOwner->GetGame()->mChannel);
            mOwner->SetState(ActorState::Paused);
            Mix_Chunk* dead_sound = mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav");
            if(Mix_PlayChannel(-1, dead_sound, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
    }
    
    float temp_camera_pos = mOwner->GetGame()->camera_pos.x;
    
    if(GetForwardSpeed() <= 0.0f){
        if(mOwner->GetGame()->camera_pos.x > mOwner->GetPosition().x){
            mOwner->SetPosition(Vector2(mOwner->GetGame()->camera_pos.x,
                                        mOwner->GetPosition().y));
        }
    } else {
        if(mOwner->GetPosition().x - temp_camera_pos < player_walk_speed){
            mOwner->GetGame()->camera_pos.x = temp_camera_pos;
        } else {
            mOwner->GetGame()->camera_pos.x = mOwner->GetPosition().x - player_walk_speed;
        }
    }
    
    if(mOwner->GetPosition().x >  pole_x_pos){
        Mix_HaltChannel(mOwner->GetGame()->mChannel);
        Mix_Chunk* win_sound = mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav");
        if(Mix_PlayChannel(-1, win_sound, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        mOwner->SetState(ActorState::Paused);
    }
}


void PlayerMove::Player_Animate(std::string mAnimName, std::vector<SDL_Texture *> Anims){
    mOwner->GetComponent<AnimatedSprite>()->AddAnimation(mAnimName, Anims);
    mOwner->GetComponent<AnimatedSprite>()->SetAnimation(mAnimName);
}

