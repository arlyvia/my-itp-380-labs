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
    if(mAnimName.empty()){}
    if(!this->mIsPaused){
        mAnimTimer = mAnimTimer * deltaTime;
        if(mAnimTimer >= mAnims.find(mAnimName)->second.size()){
            //need to store the result
            //mAnims.find(mAnimName);
            while(mAnimTimer >= mAnims.size()){
                mAnimTimer = mAnimTimer - 1;
            }
        }
    }
    //SetTexture(mAnimName);
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
