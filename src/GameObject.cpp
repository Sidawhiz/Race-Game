#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y){
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

void GameObject::Update(){

    xpos++;
    ypos++;
    srcR.h = srcR.w = 320;
    srcR.x = srcR.y = 0;

    dstR.h = dstR.w = 64;
    dstR.x = xpos;
    dstR.y = ypos;
}

void GameObject::Render(){
    TextureManager::Draw(objTexture, srcR, dstR);
}