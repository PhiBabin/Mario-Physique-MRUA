//#include "includes.hpp"
#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
struct Type{
	bool		visible;	//is the tile visible
	bool		solid;	//is the tile solid
	sf::Color   colorPix;
	sf::IntRect zoneRect;};
class MapTile{
	public:
        MapTile(sf::RenderWindow &App,const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop, Player &newPlayer);
		void loadMap(const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop,const bool triangle);		//loads the map from a file
		void setPlayer(Player &newPlayer);
		void draw();
        Type & operator () (int X, int Y);
        unsigned char findType(sf::Color Pix);
        bool collisionTile(const float x, const float y);
        void thinkPlayer();
//        void gravity();
        bool collisionTriangle(const sf::IntRect playerRect);

        bool collisionPlayerGeneral(const sf::IntRect playerRect);
        bool collisionPlayerHorizontal(const sf::IntRect playerRect);
        bool collisionPlayerVertical(const sf::IntRect playerRect);
 //       void collisionPlayer();
      //  bool collisionPlayer(const sf::IntRect playerRect);
	private:
        sf::RenderWindow &m_app;
		int m_width, m_height;
		sf::Image m_ImgTypeTile;
		sf::Sprite m_drawSprite;
		vector <vector<unsigned char> > m_tileSet;
		vector <Type> m_typeList;
		Player &m_player;
		bool m_triangle;
		sf::Shape m_triangleSprite;

};


#endif // MAP_HPP_INCLUDED
