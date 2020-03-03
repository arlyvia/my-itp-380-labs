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

GhostAI::GhostAI(class Actor* owner)
:Component(owner, 50)
{
	mGhost = static_cast<Ghost*>(owner);
}

void GhostAI::Update(float deltaTime)
{
	// TODO: Implement
}


void GhostAI::Frighten()
{
	// TODO: Implement
}

void GhostAI::Start(PathNode* startNode)
{
	// TODO: Implement
    mOwner->SetPosition(startNode->GetPosition());
    mState = State::Scatter;
    mPrevNode = nullptr;
    mNextNode = nullptr;
    mTargetNode = nullptr;
}

void GhostAI::Die()
{
	// TODO: Implement
}

void GhostAI::A_Star(PathNode* targetNode, PathNode* prevNode, PathNode* nextNode){
    std::unordered_map<PathNode*, NodeInfo> info;
    PathNode* currentNode = prevNode;
    nextNode = currentNode->mAdjacent[0];
    info[currentNode].IsClosed = true;
    do {
        for(int i=1; i < (signed)currentNode->mAdjacent.size(); i++){
            PathNode* adj = currentNode->mAdjacent[i];
            if(adj->GetType() == PathNode::Tunnel) continue;
            if(!info[adj].IsClosed){
                if(std::find(openSet.begin(), openSet.end(), currentNode->mAdjacent[i]) != openSet.end()){ // Check for adoption
                    float new_g = info[currentNode].g + edgeCost(currentNode, adj);
                    if(new_g < info[adj].g){
                        info[adj].parent = currentNode;
                        info[adj].g = new_g;
                        info[adj].f = info[currentNode->mAdjacent[i]].g + info[adj].h;
                    }
                    
                } else {
                        info[adj].parent = currentNode;
                        info[adj].h = edgeCost(adj, targetNode);
                        info[adj].g = info[currentNode].g + edgeCost(currentNode, adj);
                        info[adj].f = info[adj].g + info[adj].h;
                        openSet.push_back(adj);
                    }
                }
            }
        if(openSet.empty()) break;
        //currentNode = Node with lowest f in openSet
        for(int i = 0; i < (signed)openSet.size(); i++){
            if(info[openSet[i+1]].f > info[openSet[i]].f){
                mMin = openSet[i];
            }
        }
        currentNode = mMin;
        auto iter = std::find(openSet.begin(), openSet.end(), currentNode);
        openSet.erase(iter);
        info[currentNode].IsClosed = true;
    } while (currentNode != targetNode);
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
