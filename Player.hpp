
//#include "includes.hpp"
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
class Player:public ImgAnim{
    public:
        Player(sf::Image &imgPlayer,sf::RenderWindow *app,int grav);
        sf::FloatRect GetPlayerRect();
        sf::FloatRect GetMovedPlayerRect(const float moveX,const float moveY);
        void Gravity();
        void Jump();
        void UnlockJump();
        void Turn(bool left, bool right);
        float GetVelx();
        float GetVely();
        void BottomCollision(bool is);
        void ResetVely();
    private:
        sf::Image m_imgPlayer;
        sf::RenderWindow *m_app;
        float m_velx;
        float m_vely;
        bool m_jumpLock;
        bool m_colBot;
        bool m_direction;
        int m_gravity;
};
#endif // PLAYER_HPP_INCLUDED
