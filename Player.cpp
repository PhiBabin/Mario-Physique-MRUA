#include "Player.hpp"

Player::Player(sf::Image &imgPlayer,sf::RenderWindow *app,float xInit=100.f,float yInit=200.f)
: ImgAnim::ImgAnim(imgPlayer,3,4),m_app(app){
    setDelay(0.1);
    m_colBot=false;
    m_point=false;
    m_velx=0;
    m_vely=0;
    SetX(xInit);
    SetY(yInit);
}
sf::IntRect Player::GetPlayerRect(){
    return sf::IntRect(GetPosition().x,GetPosition().y,PLAYERCOLLISIONWIDTH,PLAYERCOLLISIONHEIGHT);
}
sf::FloatRect Player::GetViewRect(){
    return sf::FloatRect(GetPosition().x-SCREENWIDTH/4,GetPosition().y-SCREENHEIGHT/4,SCREENWIDTH/2,SCREENHEIGHT/2);
}
sf::IntRect Player::GetMovedPlayerRect(const float moveX,const float moveY){
  return sf::IntRect(GetPosition().x+moveX,GetPosition().y+moveY,PLAYERCOLLISIONWIDTH,PLAYERCOLLISIONHEIGHT);
}
void Player::Gravity(){
    if(m_vely<200)m_vely+=GRAVITY*m_app->GetFrameTime()/1000;
}
void Player::Jump(){
    if(!m_jumpLock&&m_vely>-500){
        m_jumpLock=true;
        m_vely+=-200;
        BottomCollision(false);
        cout<<"jump"<<endl;
    }
}
//direction=true=left
void Player::Turn(bool left, bool right){
    if(left&&!right){
        if(m_colBot){
            setAnimRow(1);
            cout<<"left turn"<<endl;
        }
        else {
            setAnimRow(3);
            cout<<"left jump turn"<<endl;
        }
		play();
        m_velx=-150.f;
    }
    else if(!left&&right){
        //cout<<"no move"<<endl;
        if(m_colBot)setAnimRow(0);
        else setAnimRow(2);
		play();
        m_velx=150.f;
    }
    else{
        if(m_colBot)setAnimRow(0);
        else if(animRow()<2) setAnimRow(animRow()+2);
        else setAnimRow(animRow());
        stop();
        m_velx=0;
    }
}
void Player::SetPoint(bool values){
    m_point=values;
}
bool Player::GetPoint(){
    return m_point;
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
