#include "Bullet.hpp"

Bullet::Bullet(Vector2f pos, Vector2f dire, float rot, Texture &texture){
    dir=dire;
    sprite.setTexture(texture);
    sprite.setScale(0.25,0.25);
    sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    sprite.setPosition(pos);
    sprite.setRotation(rot);
    vel=10;
}

void Bullet::Update(){
    Movement();
}

void Bullet::Movement(){
    sprite.move(dir.x*vel,dir.y*vel);
}

Vector2f Bullet::GetPosition(){
    return sprite.getPosition();
}

void Bullet::draw(RenderTarget &rt, RenderStates rs) const{
    rt.draw(sprite,rs);
}