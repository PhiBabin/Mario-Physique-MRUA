
//#include "includes.hpp"
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
class Player:public ImgAnim{
    public:
        Player(sf::Image &imgPlayer,float xInit,float yInit);
//        void Think(sf::RenderWindow &App);
       // void Move(const float x,const float y);
       // void Draw(sf::RenderWindow &App);
        sf::FloatRect GetViewRect();
        sf::IntRect GetPlayerRect();
        sf::IntRect GetMovedPlayerRect(const float moveX,const float moveY);
        void Gravity();
        void Jump();
        void UnlockJump();
        void Turn(bool left, bool right);
        void SetPoint(bool values);
        bool GetPoint();
        int GetVelx();
        int GetVely();
        void BottomCollision(bool is);
        void ResetVely();
      //void GetPosition();
    private:
        sf::Image m_imgPlayer;
        //ImgAnim m_spritePlayer;
        int m_velx;
        int m_vely;
        bool m_point;
        bool m_jumpLock;
        bool m_colBot;
};
#endif // PLAYER_HPP_INCLUDED
