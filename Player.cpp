#include "Player.hpp"

Player::Player(sf::Image &imgPlayer,float xInit=100.f,float yInit=200.f)
: ImgAnim::ImgAnim(imgPlayer,3,4)
{
    setDelay(0.1);
    m_colBot=false;
    m_point=false;

    //ImgAnim(imgPlayer,1,3);
    m_velx=0;
    m_vely=0;
	//sf::Image imgPlayer;
//	m_imgPla;r.LoadFromFile("sprite.png");
//	m_imgPlayer.SetSmooth(false);
//	m_imgPlayer.CreateMaskFromColor(sf::Color(0,0,0));

	//Créer 4 animation de 8 frame chaque à partir de l'image imgZelda
	//ImgAnim PlayerAnim(m_imgPlayer,1,3);
	//m_spritePlayer= PlayerAnim;
	//setFrameDim(1,3);
   // SetImage(m_imgPlayer);
    SetX(xInit);
   SetY(yInit);
}
//void Player::Move(const float x,const float y){
//   Move(x,y);
//}
//void Player::Draw(sf::RenderWindow &App){
//    //cout<<"x"<<GetPosition().x<<"y"<<GetPosition().y<<"Velx"<<m_velx<<"Vely"<<m_vely<<endl;
//   // App.Draw(m_spritePlayer);
//}
sf::IntRect Player::GetPlayerRect(){
    if(m_point) return sf::IntRect(GetPosition().x+(PLAYERCOLLISIONWIDTH/2),GetPosition().y,GetPosition().x+PLAYERCOLLISIONWIDTH*0.6,GetPosition().y+PLAYERCOLLISIONHEIGHT);
    else return  sf::IntRect(GetPosition().x,GetPosition().y,GetPosition().x+PLAYERCOLLISIONWIDTH,GetPosition().y+PLAYERCOLLISIONHEIGHT);
}
sf::FloatRect Player::GetViewRect(){
    //cout<<GetPosition().x<<" x modifer="<<GetPosition().x+(PLAYERCOLLISIONWIDTH/2)<<" x2 modifer="<<GetPosition().x+1+(PLAYERCOLLISIONWIDTH/2)<<" y "<<GetPosition().y<<" y modifier"<<GetPosition().y-1+PLAYERCOLLISIONHEIGHT<<" y modifier"<<GetPosition().y+PLAYERCOLLISIONHEIGHT<<endl;
    return sf::FloatRect(GetPosition().x-SCREENWIDTH/8,GetPosition().y-SCREENHEIGHT/8,GetPosition().x+SCREENWIDTH/8,GetPosition().y+SCREENHEIGHT/8);
}
sf::IntRect Player::GetMovedPlayerRect(const float moveX,const float moveY){
    // m_colBot=false;
    if(m_point){
//        sf::IntRect movedRect = GetPlayerRect();
//        movedRect.Move(moveX,moveY);
//        return movedRect;
        return sf::IntRect(GetPosition().x+(PLAYERCOLLISIONWIDTH/2)+moveX,GetPosition().y+moveY,GetPosition().x+PLAYERCOLLISIONWIDTH*0.6+moveX,GetPosition().y+PLAYERCOLLISIONHEIGHT+moveY);
    }
    else return sf::IntRect(GetPosition().x+moveX,GetPosition().y+moveY,GetPosition().x+PLAYERCOLLISIONWIDTH+moveX,GetPosition().y+PLAYERCOLLISIONHEIGHT+moveY);
}
//void Player::Think(sf::RenderWindow &App){
//
//
//}
void Player::Gravity(){
    if(m_vely<100){
        m_vely+=5;
    }
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
        cout<<"no move"<<endl;
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
int Player::GetVelx(){
    return m_velx;
}
int Player::GetVely(){
    return m_vely;
}
void Player::BottomCollision(bool is){
    m_colBot=is;
}
void Player::ResetVely(){
    m_vely=0;
}
//void Player::GetPosition(){
//    cout<<GetPosition().x<<" y"<<GetPosition().y<<endl;
//}

       // if(m_vely==0)setAnimRow(0);
void Player::UnlockJump(){
    m_jumpLock=false;
    m_vely=0;
}
