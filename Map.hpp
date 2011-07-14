//#include "includes.hpp"
#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
struct Type{
	bool		visible;	//is the tile visible
	bool		solid;	//is the tile solid
	sf::Color   colorPix;
	sf::IntRect zoneRect;
	sf::Sprite tile;};
class MapTile{
	public:
        MapTile(sf::RenderWindow &App,const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop, Player &newPlayer);
		void loadMap(const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop);		//loads the map from a file
		void draw();
        unsigned char findType(sf::Color Pix);
        bool collisionTile(const float x, const float y);
        void thinkPlayer();

        bool collisionPlayerGeneral(const sf::FloatRect playerRect);
        bool collisionPlayerHorizontal(const sf::FloatRect playerRect);
        bool collisionPlayerVertical(const sf::FloatRect playerRect);
	private:
        sf::RenderWindow &m_app;
		int m_width, m_height;
		sf::Image m_ImgTypeTile;
		sf::Sprite m_drawSprite;
		vector <vector<Type> > m_tileSet;
		vector <Type> m_typeList;
		sf::Vector2f m_spawnLocationOne;
		Player &m_player;
		sf::RenderImage m_map;
};


#endif // MAP_HPP_INCLUDED
