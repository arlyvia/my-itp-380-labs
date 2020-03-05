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
    } else if(pos.x > mGhost->GetPosition().x){
        mMoveDir.y = 0.0f;
        mMoveDir.x = 1.0f;
    }
    if(pos.y < mGhost->GetPosition().y){
        mMoveDir.y = -1.0f;
        mMoveDir.x = 0.0f;
    } else if(pos.y > mGhost->GetPosition().y){
        mMoveDir.y = 1.0f;
        mMoveDir.x = 0.0f;
    }
}

void GhostAI::updatePathBOS(float deltaTime){
    
    if(mState == State::Scatter){
        updatePathScatter();
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
            mStateTimer = 0.0f;
            
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
}

void GhostAI::updatePathScatter(){
    mGhost->GetComponent<AnimatedSprite>()->SetAnimation("left");
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
    std::cout << "fright2" << std::endl;
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
    mGhostSpeed = 125.0f;
    A_Star(mNextNode, mGhost->GetGame()->mGhostPen);
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
