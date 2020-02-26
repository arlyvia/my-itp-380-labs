#include "AnimatedSprite.h"
#include "Actor.h"
#include "Game.h"

AnimatedSprite::AnimatedSprite(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
}

void AnimatedSprite::Update(float deltaTime)
{
	// TODO: Implement
    if(mAnimName.empty()){
        return;
    }
    if(mAnims.find(mAnimName)->second.size() != 0){
        if(!mIsPaused){
            mAnimTimer = mAnimTimer + mAnimFPS * deltaTime;
            if(mAnimTimer >= mAnims.find(mAnimName)->second.size()){
                while(mAnimTimer >= mAnims.find(mAnimName)->second.size()){
                    mAnimTimer = mAnimTimer - mAnims.find(mAnimName)->second.size();
                }
            }
        }
        SetTexture(mAnims[mAnimName][(signed)mAnimTimer]);
    }
}

void AnimatedSprite::SetAnimation(const std::string& name, bool resetTimer)
{
	if (mAnimName != name)
	{
		mAnimName = name;
	}
	
	if (resetTimer)
	{
		mAnimTimer = 0.0f;
	}
}

void AnimatedSprite::AddAnimation(const std::string& name,
								  const std::vector<SDL_Texture*>& images)
{
	mAnims.emplace(name, images);
}
