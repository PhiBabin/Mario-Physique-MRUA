
#include "Map.hpp"

MapTile::MapTile(sf::RenderWindow &App,const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop, Player &newPlayer):m_app(App),m_player(newPlayer){
   loadMap( tileset,image_schema,image_corr,tileprop);
}
 bool MapTile::collisionTile(float x, float y){
    return m_tileSet[x][y].solid;
 }
 void MapTile::thinkPlayer(){
     float movHor=0;
     float movVer=0;
     float movHorTest=m_player.GetVelx()*m_app.GetFrameTime()/1000;
     float movVerTest=m_player.GetVely()*m_app.GetFrameTime()/1000;

    if(!collisionPlayerHorizontal(m_player.GetMovedPlayerRect(movHorTest,0))){
       movHor=movHorTest;
    }
    if(!collisionPlayerVertical(m_player.GetMovedPlayerRect(0,movVerTest))){
        m_player.Gravity();
       movVer=movVerTest;
    }
    if(!collisionPlayerGeneral(m_player.GetMovedPlayerRect(movHor,movVer)))m_player.Move(movHor,movVer);
 }

 bool MapTile::collisionPlayerGeneral(const sf::FloatRect playerRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    maxWidth=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;
    if(minHeight<0)minHeight=0;
    if(maxHeight>m_height)maxHeight=m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>m_width)maxWidth=m_width;

     for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=m_width or y>=m_height)){
                if(m_tileSet[x][y].solid){
                   sf::FloatRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,TILEWIDTH,TILEHEIGHT);
                    if(playerRect.Intersects(theTile)){
                       return true;
                    }
                }
            }
        }
    }
    return false;
 }

 bool MapTile::collisionPlayerHorizontal(const sf::FloatRect playerRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    bool CollisionHorizontal=false;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    maxWidth=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;

    if(minHeight<0)minHeight=0;
    if(maxHeight>m_height)maxHeight=m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>m_width)maxWidth=m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=m_width or y>=m_height)){
                if(m_tileSet[x][y].solid){
                    if(x*TILEWIDTH>=playerRect.Left&&x*TILEWIDTH<=playerRect.Left+playerRect.Width){
                        CollisionHorizontal= true;
                    }
                    if((x+1)*TILEWIDTH<=playerRect.Left+playerRect.Width&&(x+1)*TILEWIDTH>=playerRect.Left){
                        CollisionHorizontal= true;
                    }
                }
            }
        }
    }
    return CollisionHorizontal;
 }
 bool MapTile::collisionPlayerVertical(const sf::FloatRect playerRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    bool CollisionVertical=false;

    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Top+playerRect.Height-1)/TILEHEIGHT;
    maxWidth=(playerRect.Left+playerRect.Width-1)/TILEWIDTH;

    if(minHeight<0)minHeight=0;
    if(maxHeight>m_height)maxHeight=m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>m_width)maxWidth=m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=m_width or y>=m_height)){
                if(m_tileSet[x][y].solid){
                    if(y*TILEHEIGHT<=playerRect.Top+playerRect.Height&&y*TILEHEIGHT>=playerRect.Top){
                        m_player.UnlockJump();
                        m_player.BottomCollision(true);
                        CollisionVertical= true;
                    }
                    if((y+1)*TILEHEIGHT>=playerRect.Top&&(y+1)*TILEHEIGHT<=playerRect.Top+playerRect.Height){
                        m_player.ResetVely();
                        CollisionVertical=true;
                    }
                }
            }
        }
    }
    return CollisionVertical;
 }
void MapTile::draw(){
    cout<<"x"<<m_player.GetPosition().x<<"y"<<m_player.GetPosition().y<<"Velx"<<m_player.GetVelx()<<"Vely"<<m_player.GetVely()<<endl;
    //! On affiche les tile de la carte
    m_app.Draw(sf::Sprite(m_map.GetTexture()));
}
 unsigned char MapTile::findType(sf::Color Pix){
        for(unsigned char it=0;it<m_typeList.size();it++){
            if(m_typeList[it].colorPix==Pix) return it;
        }
        cerr<<"[Fatal Error]Impossible de trouver un type correspondant."<<endl;
        exit(0);
        return 0;
 }
//Tileset: image du niveau image_schema: Liste des tiles (petit) image_corr: liste des tiles correspondant tileprop: fichier des propriété
void MapTile::loadMap(const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop){
    //! Initiation des images temporaire
    sf::Texture tilesetImg,image_schemaImg;
    tilesetImg.LoadFromFile(tileset);
    //! On supprime les vectors
	m_typeList.erase(m_typeList.begin(),m_typeList.end());
	m_tileSet.erase(m_tileSet.begin(),m_tileSet.end());
    image_schemaImg.LoadFromFile(image_schema);
    //! Initiation des images des tiles
    m_ImgTypeTile.LoadFromFile(image_corr);
    m_ImgTypeTile.SetSmooth(false);
    m_width=tilesetImg.GetWidth();
    m_height=tilesetImg.GetHeight();
    //! On crée un vector de tile et on les fait corresponds à un pixel
    for(unsigned int it=0;it<image_schemaImg.GetWidth();it++){
        for(unsigned int it2=0;it2<image_schemaImg.GetHeight();it2++){
            Type newTile;
            newTile.colorPix = image_schemaImg.CopyToImage().GetPixel(it, it2);
            newTile.zoneRect=sf::IntRect(it*TILEWIDTH, it2*TILEHEIGHT, TILEWIDTH, TILEHEIGHT);
            m_typeList.insert(m_typeList.end(),newTile);
        }
    }
    //! On charge le fichier des propriétés de la map
    FILE* tilePropFile = NULL;
	tilePropFile = fopen(tileprop, "r");
	if(tilePropFile==NULL){ cerr<<"[FATAL ERROR] Map not found."<<endl; exit(1);}
	int Visible,Solid,Spawn,typeSpawn1;
	for(unsigned int it=0;it<m_typeList.size();it++){
        fscanf(tilePropFile, "%d  %d  %d",&Visible,&Solid,&Spawn);
        if(Spawn==1)typeSpawn1=it;
        if(Visible==1)m_typeList[it].visible=true;
        else m_typeList[it].visible=false;
        if(Solid==1)m_typeList[it].solid=true;
        else m_typeList[it].solid=false;
	}

	int theTile;
    for(int it=0;it<m_width;it++){
        vector<Type> tileList2;
        m_tileSet.insert(m_tileSet.end(),tileList2);
        for(int it2=0;it2< m_height;it2++){
            theTile=findType(tilesetImg.CopyToImage().GetPixel(it, it2));
            if(theTile==typeSpawn1){
                sf::Vector2f m_spawnLocationOne(it*TILEWIDTH ,(it2+1)*TILEHEIGHT-PLAYERCOLLISIONHEIGHT);
                m_player.SetPosition(m_spawnLocationOne);
            }
            Type theNewTile= m_typeList[theTile];
            theNewTile.tile.SetPosition(it*TILEWIDTH,it2*TILEHEIGHT);
            theNewTile.tile.SetTexture(m_ImgTypeTile);
            theNewTile.tile.SetSubRect(m_typeList[theTile].zoneRect);
             m_tileSet[it].insert( m_tileSet[it].end(),theNewTile);
        }
    }
    m_map.Create(m_width*TILEWIDTH,m_height*TILEHEIGHT);
    m_drawSprite.SetTexture(m_ImgTypeTile);
    for(int y=0;y<m_height;y++){
        for(int x=0;x<m_width;x++){
            if(m_tileSet[x][y].visible)m_map.Draw(m_tileSet[x][y].tile);
        }
    }
    m_map.Display();
}

