#include "GhostAI.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "PathNode.h"
#include "AnimatedSprite.h"
#include <SDL2/SDL.h>
#include <unordered_map>
#include "Ghost.h"
#include "PacMan.h"
#include "Random.h"
#include <iostream>
#include "MoveComponent.h"

GhostAI::GhostAI(class Actor* owner)
:Component(owner, 50)
{
	mGhost = static_cast<Ghost*>(owner);
}

void GhostAI::Update(float deltaTime)
{
	// TODO: Implement
    
    Vector2 pos = mGhost->GetPosition();
    pos += mMoveDir * mGhostSpeed * deltaTime;
    mGhost->SetPosition(pos);
    
    mStateTimer = deltaTime + mStateTimer;
    
    if(mNextNode == nullptr){
        return;
    }
    if(mGhost->GetComponent<CollisionComponent>()->Intersect(mNextNode->GetComponent<CollisionComponent>())){
            updatePathBOS(deltaTime);
    }
    
    if(mGhost->GetComponent<CollisionComponent>()->Intersect(mGhost->GetGame()->mPlayer->GetComponent<CollisionComponent>())){
            if(mState == State::Frightened) Die();
        }
}

void GhostAI::SetDirection(Vector2 pos){
    if(pos.x < mGhost->GetPosition().x){
        mMoveDir.y = 0.0f;
        mMoveDir.x = -1.0f;
        if(mState == State::Scatter){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("left");
        } else if (mState == State::Dead){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("deadleft");
        }
    } else if(pos.x > mGhost->GetPosition().x){
        mMoveDir.y = 0.0f;
        mMoveDir.x = 1.0f;
        //depending on state (3 states)
        if(mState == State::Scatter){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("right");
        } else if (mState == State::Dead){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("deadright");
        }
    }
    if(pos.y < mGhost->GetPosition().y){
        mMoveDir.y = -1.0f;
        mMoveDir.x = 0.0f;
       if(mState == State::Scatter){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("up");
        } else if (mState == State::Dead){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("deadup");
        }
    } else if(pos.y > mGhost->GetPosition().y){
        mMoveDir.y = 1.0f;
        mMoveDir.x = 0.0f;
        if(mState == State::Scatter){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("down");
        } else if (mState == State::Dead){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("deaddown");
        }
    }
}

void GhostAI::updatePathBOS(float deltaTime){
    
    
    if(mState == State::Scatter){
        updatePathScatter();
        if(mStateTimer > 5.0f){
            Chasin();
        }
    }
    if(mState == State::Frightened){
        mGhost->SetPosition(mNextNode->GetPosition());
    
        std::vector<PathNode*> possible_nodes;
        for(int i=0; i < (signed)mNextNode->mAdjacent.size(); i++){
            if(mNextNode->mAdjacent[i] != mPrevNode
               && mNextNode->mAdjacent[i]->GetType() != PathNode::Tunnel){
                possible_nodes.push_back(mNextNode->mAdjacent[i]);
            }
        }
        
        int r_index = rand() % possible_nodes.size();
        if(possible_nodes[r_index]->GetType() == PathNode::Ghost){
            for(int i=0; i < (signed)possible_nodes.size(); i++){
                if(possible_nodes[i]->GetType() != PathNode::Ghost){
                    r_index = i;
                }
            }
        }
    
        mPrevNode = mNextNode;
        mNextNode = possible_nodes[r_index];
        if(mStateTimer > 5.0f){
            mGhost->GetComponent<AnimatedSprite>()->SetAnimation("scared1");
        }
        
        if(mStateTimer > 7.0f){
            mStateTimer = 0;
            
            mState = State::Scatter; 
        }
        SetDirection(mNextNode->GetPosition());
    }
    if(mState == State::Dead){
        mGhost->SetPosition(mNextNode->GetPosition());
        if(mGhost->GetPosition().x == mGhost->GetGame()->mGhostPen->GetPosition().x
              && mGhost->GetPosition().y == mGhost->GetGame()->mGhostPen->GetPosition().y){
               Start(mGhost->GetGame()->mGhostPen);
            return;
        }
        mPrevNode = mNextNode;
        mNextNode = mPath[mPath.size()-1];
        mPath.pop_back();
        SetDirection(mNextNode->GetPosition());
    }
    if(mState == State::Chase){
        if(mGhost->GetType() == Ghost::Type::Blinky){
            blinkyChase();
        }
        if(mGhost->GetType() == Ghost::Type::Pinky){
            pinkyChase();
        }
        if(mGhost->GetType() == Ghost::Type::Inky){
            inkyChase();
        }
        if(mGhost->GetType() == Ghost::Type::Clyde){
            clydeChase();
        }
        if(mStateTimer > 20.0f){
            mStateTimer = 0;
            mState = State::Scatter;
        }
    }
}

void GhostAI::updatePathScatter(){
    mGhostSpeed = 90.0f;
    mGhost->SetPosition(mNextNode->GetPosition());
    if(mPath.empty()){
        A_Star(mNextNode, mGhost->GetScatterNode());
    } else {
        mPrevNode = mNextNode;
        mNextNode = mPath[mPath.size()-1];
        mPath.pop_back();
    }
    
    SetDirection(mNextNode->GetPosition());
}


void GhostAI::Frighten()
{
	// TODO: Implement
    mStateTimer = 0;
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("scared0");
    mGhostSpeed = 65.0f;
    mState = State::Frightened;
    PathNode* swap = mNextNode;
    mNextNode = mPrevNode;
    mPrevNode = swap;
    SetDirection(mNextNode->GetPosition());
    mPath.clear();
    
}

void GhostAI::Start(PathNode* startNode)
{
	// TODO: Implement
    mOwner->SetPosition(startNode->GetPosition());
    mState = State::Scatter;
    mPrevNode = nullptr;
    mNextNode = nullptr;
    mTargetNode = nullptr;
    A_Star(mGhost->GetSpawnNode(), mGhost->GetScatterNode());
    SetDirection(mNextNode->GetPosition());
}

void GhostAI::Die()
{
	// TODO: Implement
    mState = State::Dead;
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("deadright");
    mGhostSpeed = 125.0f;
    A_Star(mNextNode, mGhost->GetGame()->mGhostPen);
}

void GhostAI::Chasin(){
    mStateTimer = 0;
    mState = State::Chase;
}

void GhostAI::blinkyChase(){
    PathNode* pm_prev = mOwner->GetGame()->mPlayer->GetPrevNode();
    
    if(pm_prev->GetType() == PathNode::Tunnel){
        //pm_prev = closest pathnode::default;
        pm_prev = closest(mOwner->GetGame()->mPlayer->GetPosition());
    }
    
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("left");
    mGhostSpeed = 90.0f;
    mGhost->SetPosition(mNextNode->GetPosition());
    if(mPath.empty()){
        A_Star(mNextNode, pm_prev);
    } else {
        mPrevNode = mNextNode;
        mNextNode = mPath[mPath.size()-1];
        mPath.pop_back();
    }
    
    SetDirection(mNextNode->GetPosition());
}

void GhostAI::pinkyChase(){
    Vector2 target_pos = mOwner->GetGame()->mPlayer->GetPointInFrontOf(80.0f);
    PathNode* target = closest(target_pos);
    
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("left");
    mGhostSpeed = 90.0f;
    mGhost->SetPosition(mNextNode->GetPosition());
    if(mPath.empty()){
        A_Star(mNextNode, target);
    } else {
        mPrevNode = mNextNode;
        mNextNode = mPath[mPath.size()-1];
        mPath.pop_back();
    }
    
    SetDirection(mNextNode->GetPosition());
}

void GhostAI::inkyChase(){
    Vector2 target_pos = mOwner->GetGame()->mPlayer->GetPointInFrontOf(40.0f);
    Vector2 v = target_pos - mOwner->GetGame()->mGhosts[0]->GetPosition();
    Vector2 Q = (2 * v) + mOwner->GetGame()->mGhosts[0]->GetPosition();
    
    PathNode* target = closest(Q);
    
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("left");
    mGhostSpeed = 90.0f;
    mGhost->SetPosition(mNextNode->GetPosition());
    if(mPath.empty()){
        A_Star(mNextNode, target);
    } else {
        mPrevNode = mNextNode;
        mNextNode = mPath[mPath.size()-1];
        mPath.pop_back();
    }
    
    SetDirection(mNextNode->GetPosition());
}

void GhostAI::clydeChase(){
    float x = mOwner->GetGame()->mPlayer->GetPosition().x - mOwner->GetPosition().x;
    float y = mOwner->GetGame()->mPlayer->GetPosition().y - mOwner->GetPosition().y;
    float dist = pow(x, 2.0f) + pow(y, 2.0f);
    dist = sqrt(dist);
    
    PathNode* target;
    
    if(dist > 150.0f){
        target = mOwner->GetGame()->mPlayer->GetPrevNode();
    } else{
        target = mGhost->GetScatterNode();
    }
    
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("left");
    mGhostSpeed = 90.0f;
    mGhost->SetPosition(mNextNode->GetPosition());
    if(mPath.empty()){
        A_Star(mNextNode, target);
    } else {
        mPrevNode = mNextNode;
        mNextNode = mPath[mPath.size()-1];
        mPath.pop_back();
    }
    
    SetDirection(mNextNode->GetPosition());
    
}

PathNode* GhostAI::closest(Vector2 pos){
    float min = 100000;
    PathNode* minNode;
    
    for(int i=0; i < (signed)(int)mOwner->GetGame()->mPathNodes.size(); i++){
        float x = mOwner->GetGame()->mPathNodes[i]->GetPosition().x - pos.x;
        float y = mOwner->GetGame()->mPathNodes[i]->GetPosition().y - pos.y;
        float dist = pow(x, 2.0f) + pow(y, 2.0f);
        dist = sqrt(dist);
        if(dist < min &&
           mOwner->GetGame()->mPathNodes[i]->GetType() == PathNode::Type::Default){
            min = dist;
            minNode = mOwner->GetGame()->mPathNodes[i];
        }
    }
    return minNode;
}

void GhostAI::A_Star(PathNode* startNode, PathNode* goalNode){
    std::unordered_map<PathNode*, NodeInfo> info;
    openSet.clear();
    PathNode* currentNode = startNode;
    mTargetNode = goalNode;
    if(currentNode != goalNode) info[currentNode].IsClosed = true;
    info[currentNode].Unusuable.push_back(mNextNode);
    info[currentNode].Unusuable.push_back(mPrevNode);
    do {
        for(int i=0; i < (signed)currentNode->mAdjacent.size(); i++){
            PathNode* adj = currentNode->mAdjacent[i];
            if(adj->GetType() == PathNode::Tunnel ||
               std::find(info[currentNode].Unusuable.begin(), info[currentNode].Unusuable.end(), adj) != info[currentNode].Unusuable.end() ||
               info[adj].IsClosed) continue;
          
                if(std::find(openSet.begin(), openSet.end(), adj) != openSet.end()){
                    float new_g = info[currentNode].g + edgeCost(currentNode, adj);
                    if(new_g < info[adj].g){
                        info[adj].parent = currentNode;
                        info[adj].Unusuable = info[info[adj].parent].Unusuable;
                        if(!info[adj].Unusuable.empty()) info[adj].Unusuable.pop_back();
                        info[adj].g = new_g;
                        info[adj].f = info[adj].g + info[adj].h;
                    }
                    
                } else {
                        info[adj].parent = currentNode;
                        info[adj].Unusuable = info[info[adj].parent].Unusuable;
                        if(!info[adj].Unusuable.empty()) info[adj].Unusuable.pop_back();
                        info[adj].h = edgeCost(adj, goalNode);
                        info[adj].g = info[currentNode].g + edgeCost(currentNode, adj);
                        info[adj].f = info[adj].g + info[adj].h;
                        openSet.push_back(adj);
                    }

            }
        if(openSet.empty()) break;
        //currentNode = Node with lowest f in openSet
        float min = 10000000.0f;
        int index;
        for(int i = 0; i < (signed)openSet.size(); i++){
            if(min > info[openSet[i]].f){
                min = info[openSet[i]].f;
                index = i;
            }
        }
        currentNode = openSet[index];
        auto iter = std::find(openSet.begin(), openSet.end(), currentNode);
        openSet.erase(iter);
        info[currentNode].IsClosed = true;
    } while (currentNode != goalNode);
    PathNode* temp = goalNode;
    PathNode* s_node = temp;
    while(temp){
        mPath.push_back(temp);
        temp = info[temp].parent;
        if(s_node == temp) break;
    }
    mPrevNode = startNode;
    mNextNode = mPath[mPath.size()-1];
    mPath.pop_back();
}

float GhostAI::edgeCost(PathNode *curr, PathNode *adj){
    float x = curr->GetPosition().x - adj->GetPosition().x;
    float y = curr->GetPosition().y - adj->GetPosition().y;
    float dist;

    dist = pow(x, 2.0f) + pow(y, 2.0f);
    dist = sqrt(dist);

    return dist;
}

void GhostAI::DebugDrawPath(SDL_Renderer* render)
{
	// Draw a rectangle at the target node
	if (mTargetNode != nullptr)
	{
		const int SIZE = 16;
		SDL_Rect r;
		r.x = static_cast<int>(mTargetNode->GetPosition().x) - SIZE / 2;
		r.y = static_cast<int>(mTargetNode->GetPosition().y) - SIZE / 2;
		r.w = SIZE;
		r.h = SIZE;
		SDL_RenderDrawRect(render, &r);
	}

	// Line from ghost to next node
	if (mNextNode != nullptr)
	{
		SDL_RenderDrawLine(render,
			static_cast<int>(mOwner->GetPosition().x),
			static_cast<int>(mOwner->GetPosition().y),
			static_cast<int>(mNextNode->GetPosition().x),
			static_cast<int>(mNextNode->GetPosition().y));
	}

	// Exit if no path
	if (mPath.empty())
	{
		return;
	}

	if (mNextNode)
	{
		// Line from next node to subsequent on path
		SDL_RenderDrawLine(render,
			static_cast<int>(mNextNode->GetPosition().x),
			static_cast<int>(mNextNode->GetPosition().y),
			static_cast<int>(mPath.back()->GetPosition().x),
			static_cast<int>(mPath.back()->GetPosition().y));
	}

	// Lines for rest of path
	for (size_t i = 0; i < mPath.size() - 1; i++)
	{
		SDL_RenderDrawLine(render,
			static_cast<int>(mPath[i]->GetPosition().x),
			static_cast<int>(mPath[i]->GetPosition().y),
			static_cast<int>(mPath[i + 1]->GetPosition().x),
			static_cast<int>(mPath[i + 1]->GetPosition().y));
	}
}


