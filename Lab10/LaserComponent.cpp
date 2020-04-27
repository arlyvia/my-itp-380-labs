//
//  LaserComponent.cpp
//  Lab10
//
//  Created by Arlyvia Chaialee on 4/15/20.
//

#include "LaserComponent.hpp"
#include "MeshComponent.h"
#include "Shader.h"
#include "Actor.h"
#include "Mesh.h"
#include "Game.h"
#include "Texture.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "SegmentCast.h"
#include "Player.hpp"
#include "Block.hpp"
#include "iostream"

LaserComponent::LaserComponent(class Actor* owner)
:MeshComponent(owner, true)
{
    SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}

void LaserComponent::Update(float deltaTime){
    //making the first line segment
    mLineSegments.clear();

    mLineSegment = LineSegment(mOwner->GetWorldPosition(), mOwner->GetWorldPosition() + mOwner->GetWorldForward() * 500.0f);
    
    //reflecting lasers off mirrors
    CastInfo OI;
    
    Actor* ignore = nullptr;
    bool shouldKeepGoing = true;
    
    while(shouldKeepGoing){
        bool seg_cast = SegmentCast(mOwner->GetGame()->mPlayer, mLineSegment, OI);
        ignore = OI.mActor;
        //for rotating block
        if(!ignore){
            ignore = mOwner->mParent;
        }
        if(seg_cast){
            mLineSegment.mEnd = OI.mPoint;
            shouldKeepGoing = false;
            mLineSegments.push_back(mLineSegment);
        } else if(SegmentCast(mOwner->GetGame()->mBlocks, mLineSegment, OI, ignore)){
            mLineSegment.mEnd = OI.mPoint;
            mLineSegments.push_back(mLineSegment);
            ignore = OI.mActor;
            Block* block = static_cast<Block*>(ignore);
            if(block->GetIsMirror()){
                Vector3 current_dir = mLineSegment.mEnd - mLineSegment.mStart;
                current_dir.Normalize();
                mLineSegment.mStart = mLineSegment.mEnd;
                mLineSegment.mEnd = mLineSegment.mStart + Vector3::Reflect(current_dir, OI.mNormal) * 500.0f;
            } else {
                shouldKeepGoing = false;
            }
        } else {
            mLineSegments.push_back(mLineSegment);
            shouldKeepGoing = false;
        }
    }

}

void LaserComponent::Draw(class Shader *shader){
    if (mMesh)
    {
        // Set the world transform
        for(int unsigned i = 0; i < mLineSegments.size(); i++){
            shader->SetMatrixUniform("uWorldTransform",
            worldTransform(mLineSegments[i]));
            // Set the active texture
            Texture* t = mMesh->GetTexture(mTextureIndex);
            if (t)
            {
                t->SetActive();
            }
            // Set the mesh's vertex array as active
            VertexArray* va = mMesh->GetVertexArray();
            va->SetActive();
            // Draw
            glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }
    }
}

Matrix4 LaserComponent::worldTransform(LineSegment lineSegment){
    Vector3 Scale = Vector3(lineSegment.LineSegment::Length(), 1.0f, 1.0f);
    Vector3 Position = lineSegment.LineSegment::PointOnSegment(0.5f);
    
    //new rotation
    //normalize each
    Vector3 ls = (lineSegment.mEnd - lineSegment.mStart);
    Vector3 normal_ls = Vector3::Normalize(ls);
    
    Vector3 normal_x = Vector3::UnitX;
    
    float check = Vector3::Dot(normal_x, normal_ls);
    
    float theta = Math::Acos(check);

    Quaternion new_rotation;

    if (check == 1){
        new_rotation = Quaternion::Identity;
    } else if (check == -1){
        new_rotation = Quaternion(Vector3::UnitZ, theta);
    } else {
        Vector3 cross = Vector3::Cross(normal_x, normal_ls);
        
        Vector3 axis = Vector3::Normalize(cross);
        
        new_rotation = Quaternion(axis, theta);
    }

    Matrix4 ScaleMatrix = Matrix4::CreateScale(Scale);
    Matrix4 RotationMatrix = Matrix4::CreateFromQuaternion(new_rotation);
    Matrix4 PositionMatrix = Matrix4::CreateTranslation(Position);
    
    Matrix4 WorldTransform = ScaleMatrix * RotationMatrix * PositionMatrix;
    return WorldTransform;
}
