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
#include "Player.hpp"
#include "iostream"

LaserComponent::LaserComponent(class Actor* owner)
:MeshComponent(owner, true)
{
    SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}

void LaserComponent::Update(float deltaTime){
    //Vector3 dir = mOwner->GetForward();
    Vector3 dir = mOwner->GetQuatForward();
    mLineSegment = LineSegment(mOwner->GetPosition(), mOwner->GetPosition() + dir * 500.0f);
    
    CastInfo OI;
    
    if(SegmentCast(mOwner->GetGame()->mPlayer, mLineSegment, OI)){
        mLineSegment.mEnd = OI.mPoint;
    } else if(SegmentCast(mOwner->GetGame()->mBlocks, mLineSegment, OI)){
        mLineSegment.mEnd = OI.mPoint;
    }
}

void LaserComponent::Draw(class Shader *shader){
    if (mMesh)
    {
        // Set the world transform
        shader->SetMatrixUniform("uWorldTransform",
            worldTransform(mLineSegment));
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

Matrix4 LaserComponent::worldTransform(LineSegment lineSegment){
    //std::cout << "length: " << lineSegment.LineSegment::Length() << std::endl;
    Vector3 Scale = Vector3(lineSegment.LineSegment::Length(), 1.0f, 1.0f);
    Vector3 Position = Vector3(lineSegment.LineSegment::PointOnSegment(0.5f));
    
    //new rotation
    //normalize each
    Vector3 ls = (lineSegment.mEnd - lineSegment.mStart);
    Vector3 normal_ls = Vector3::Normalize(ls);
    
    Vector3 normal_x = Vector3::Normalize(Vector3::UnitX);
    
    float theta = Math::Acos(Vector3::Dot(normal_x, normal_ls));
    
    float check = Vector3::Dot(normal_x, normal_ls);

    Quaternion new_rotation;
    
    if(check != 1 && check != -1){
        Vector3 cross = Vector3::Cross(normal_x, normal_ls);
        
        Vector3 axis = Vector3(cross.x / cross.Length(),
            cross.y / cross.Length(),
            cross.z / cross.Length());
        
        new_rotation = Quaternion(axis, theta);
    } else if (check == 1){
        new_rotation = Quaternion::Identity;
    } else if (check == -1){
        new_rotation = Quaternion(Vector3::UnitZ, theta);
    }

    
    

    Matrix4 ScaleMatrix = Matrix4::CreateScale(Scale);
    //Matrix4 RotationMatrix = Matrix4::CreateRotationZ(mOwner->GetRotation());
    Matrix4 RotationMatrix = Matrix4::CreateFromQuaternion(new_rotation);
    Matrix4 PositionMatrix = Matrix4::CreateTranslation(Position);
    
    Matrix4 WorldTransform = ScaleMatrix * RotationMatrix * PositionMatrix;
    return WorldTransform;
}
