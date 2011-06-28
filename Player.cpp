#include "Player.hpp"

Player::Player(sf::Image &imgPlayer,sf::RenderWindow *app,int grav)
: ImgAnim::ImgAnim(imgPlayer,3,4),m_app(app),m_gravity(grav){
    setDelay(0.1);
    m_colBot=false;
    m_velx=0;
    m_vely=0;
}
sf::IntRect Player::GetPlayerRect(){
    return sf::IntRect(GetPosition().x,GetPosition().y,PLAYERCOLLISIONWIDTH,PLAYERCOLLISIONHEIGHT);
}
sf::IntRect Player::GetMovedPlayerRect(const float moveX,const float moveY){
  return sf::IntRect(GetPosition().x+moveX,GetPosition().y+moveY,PLAYERCOLLISIONWIDTH,PLAYERCOLLISIONHEIGHT);
}
void Player::Gravity(){
    m_vely+=m_gravity*m_app->GetFrameTime()/1000;
}
void Player::Jump(){
    if(!m_jumpLock&&m_vely>-500){
        m_jumpLock=true;
        m_vely+=-200;
        BottomCollision(false);
        cout<<"jump"<<endl;
    }
}
void Player::Turn(bool left, bool right){


    if(left&&!right){
        m_direction=LEFT;
        if(m_colBot){
            setAnimRow(1);
        }
        else {
            setAnimRow(3);
        }
		play();
        m_velx=-150.f;
    }
    else if(!left&&right){
        m_direction=RIGHT;
        if(m_colBot)setAnimRow(0);
        else setAnimRow(2);
		play();
        m_velx=150.f;
    }
    else{
        if(m_colBot&& m_direction==LEFT)setAnimRow(1);
        else if(m_colBot&& m_direction==RIGHT)setAnimRow(0);
        else if(animRow()<2) setAnimRow(animRow()+2);
        else setAnimRow(animRow());
        stop();
        m_velx=0;
    }
}
float Player::GetVelx(){
    return m_velx;
}
float Player::GetVely(){
    return m_vely;
}
void Player::BottomCollision(bool is){
    m_colBot=is;
}
void Player::ResetVely(){
    m_vely=0;
}
void Player::UnlockJump(){
    m_jumpLock=false;
    m_vely=0;
}
