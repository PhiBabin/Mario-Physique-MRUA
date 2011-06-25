
//#include "includes.hpp"
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
class Player:public ImgAnim{
    public:
        Player(sf::Image &imgPlayer,sf::RenderWindow *app,float xInit,float yInit);
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
        float GetVelx();
        float GetVely();
        void BottomCollision(bool is);
        void ResetVely();
      //void GetPosition();
    private:
        sf::Image m_imgPlayer;
        sf::RenderWindow *m_app;
        //ImgAnim m_spritePlayer;
        float m_velx;
        float m_vely;
        bool m_point;
        bool m_jumpLock;
        bool m_colBot;
};
#endif // PLAYER_HPP_INCLUDED
