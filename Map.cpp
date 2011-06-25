
#include "Map.hpp"

MapTile::MapTile(sf::RenderWindow &App,const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop, Player &newPlayer):m_app(App),m_player(newPlayer),m_triangle(true){
   m_triangleSprite.AddPoint(100, 511,  sf::Color(255, 0, 0), sf::Color(0, 128, 128));
   m_triangleSprite.AddPoint(150, 460,  sf::Color(255, 0, 0), sf::Color(0, 128, 128));
   m_triangleSprite.AddPoint(230, 511,  sf::Color(255, 0, 0), sf::Color(0, 128, 128));
   m_triangleSprite.SetColor(sf::Color(255, 255, 255, 200));
    loadMap( tileset,image_schema,image_corr,tileprop,false);
}
 bool MapTile::collisionTile(const float x, const float y){
    return m_typeList[m_tileSet[x/TILESETWIDTH][y/TILEHEIGHT]].solid;
 }
 void MapTile::thinkPlayer(){
//
//    if(m_player.GetVelx()>=0)m_player.setAnimRow(2);
//    else m_player.setAnimRow(3);
//    m_player.BottomCollision(false);
     float movHor=0;
     float movVer=0;
     float movHorTest=m_player.GetVelx()*m_app.GetFrameTime()/1000;
     float movVerTest=m_player.GetVely()*m_app.GetFrameTime()/1000;

    if(!collisionPlayerHorizontal(m_player.GetMovedPlayerRect(movHorTest,0))){
       //m_player.Move(m_player.GetVelx()*m_app.GetFrameTime(),0);
       movHor=movHorTest;
    }//cout<<"help"<<endl;
    if(!collisionPlayerVertical(m_player.GetMovedPlayerRect(0,movVerTest))){
        m_player.Gravity();
       // m_player.Move(0,m_player.GetVely()*m_app.GetFrameTime());
       movVer=movVerTest;
    }
    if(!collisionPlayerGeneral(m_player.GetMovedPlayerRect(movHor,movVer)))m_player.Move(movHor,movVer);
  //  collisionPlayer();
 }

 bool MapTile::collisionPlayerGeneral(const sf::IntRect playerRect){
    int maxHeight, minHeight, maxWidth, minWidth;
  //  bool Collision=false;
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
                if(m_typeList[m_tileSet[x][y]].solid){
                   sf::IntRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,TILEWIDTH,TILEHEIGHT);
                    if(playerRect.Intersects(theTile)){
                       return true;
                    }
                }
            }
        }
    }
    //cout<<"Stop Blabla2"<<endl;
    //return Collision;
    return false;
 }

 bool MapTile::collisionPlayerHorizontal(const sf::IntRect playerRect){
   // cout<< "hor x1="<<playerRect.Left<<" y1="<<playerRect.Top<<" x2="<<playerRect.Right<<" y2="<<playerRect.Bottom<<endl;
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
                if(m_typeList[m_tileSet[x][y]].solid){
                   // cout<<playerRect.Left<<","<<playerRect.Right<<endl;
                    //cout<<playerRect.Left<<"p<"<<(x+1)*TILEWIDTH<<" "<<playerRect.Right<<"p>"<<x*TILEWIDTH;
                    if(x*TILEWIDTH>=playerRect.Left&&x*TILEWIDTH<=playerRect.Left+playerRect.Width){
                        cout<<" ====Droit==";
                        CollisionHorizontal= true;
                    }
                    if((x+1)*TILEWIDTH<=playerRect.Left+playerRect.Width&&(x+1)*TILEWIDTH>=playerRect.Left){
                        cout<<" ====Gauche==";
                        CollisionHorizontal= true;
                    }
                    cout<<endl;
                }
            }
        }
    }
    //cout<<"Stop Blabla2"<<endl;
    return CollisionHorizontal;
 }
 bool MapTile::collisionPlayerVertical(const sf::IntRect playerRect){
    //cout<< "ver x1="<<playerRect.Left<<" y1="<<playerRect.Top<<" x2="<<playerRect.Right<<" y2="<<playerRect.Bottom<<endl;
    int maxHeight, minHeight, maxWidth, minWidth;
    bool CollisionVertical=false;
 //   cout<<"Start"<<endl;
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
//            cout<<y*TILEWIDTH<<" "<<(y+1)*TILEWIDTH<<endl;
//            cout<<y*TILEWIDTH<<"<"<<playerRect.Bottom<<">"<<playerRect.Top<<endl;
//            cout<<(y+1)*TILEWIDTH<<"<"<<playerRect.Bottom<<">"<<playerRect.Top<<endl;
            if(!(x>=m_width or y>=m_height)){
                if(m_typeList[m_tileSet[x][y]].solid){
                   // cout<<playerRect.Bottom<<"p<"<<(x+1)*TILEWIDTH<<" "<<playerRect.Right<<"p>"<<x*TILEWIDTH;
                    if(y*TILEHEIGHT<=playerRect.Top+playerRect.Height&&y*TILEHEIGHT>=playerRect.Top){
                        m_player.UnlockJump();
                        m_player.BottomCollision(true);
                        //if(m_player.GetVelx()>=0)m_player.setAnimRow(0);
                        //else m_player.setAnimRow(1);
                        //else m_player.animRow(1);
                        CollisionVertical= true;
                    }
                    if((y+1)*TILEHEIGHT>=playerRect.Top&&(y+1)*TILEHEIGHT<=playerRect.Top+playerRect.Height){
                        cout<<" ====tete==";
                        m_player.ResetVely();
                        CollisionVertical=true;
                    }
                    cout<<endl;
                }
            }
        }
    }
    //cout<<"Stop Blabla2"<<endl;
    return CollisionVertical;
 }
void MapTile::draw(){
    cout<<"x"<<m_player.GetPosition().x<<"y"<<m_player.GetPosition().y<<"Velx"<<m_player.GetVelx()<<"Vely"<<m_player.GetVely()<<endl;
    unsigned char typeNbr;
    //sf::FloatRect views=m_app.GetView().GetViewport();
    sf::FloatRect views=sf::FloatRect(0,0,600,600);
    int maxHeight, minHeight, maxWidth, minWidth;
    // (10*40+80-(10*40))/40
    //(400+80-400)/40
    minHeight=views.Top/TILEHEIGHT-1;
    maxHeight=views.Top+views.Height/TILEHEIGHT+1;
    minWidth=views.Left/TILEWIDTH-1;
    maxWidth=views.Left+views.Width/TILEWIDTH+1;
    if(minHeight<0)minHeight=0;
    if(maxHeight>m_height)maxHeight=m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>m_width)maxWidth=m_width;
    bool DeclarTypeNbr=true;
		for(int y=minHeight;y<maxHeight;y++){
			for(int x=minWidth;x<maxWidth;x++){
				m_drawSprite.SetPosition(x*TILEWIDTH,y*TILEHEIGHT);
				if(m_tileSet[x][y]!=typeNbr||DeclarTypeNbr){
				    typeNbr=m_tileSet[x][y];
                    m_drawSprite.SetSubRect(m_typeList[typeNbr].zoneRect);
				}
				if(DeclarTypeNbr)DeclarTypeNbr=false;
				if(m_typeList[typeNbr].visible)m_app.Draw(m_drawSprite);
			}
		}
    if(m_triangle)m_app.Draw(m_triangleSprite);
}
Type & MapTile::operator () (int X, int Y){
    return m_typeList[m_tileSet[X][Y]];
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
void MapTile::loadMap(const char* tileset,const char* image_schema,const char* image_corr,const char* tileprop,const bool triangle){
    m_triangle=triangle;
    sf::Image tilesetImg,image_schemaImg;
    tilesetImg.LoadFromFile(tileset);
	m_typeList.erase(m_typeList.begin(),m_typeList.end());
	m_tileSet.erase(m_tileSet.begin(),m_tileSet.end());
    image_schemaImg.LoadFromFile(image_schema);
    m_ImgTypeTile.LoadFromFile(image_corr);
    m_ImgTypeTile.SetSmooth(false);
    m_width=tilesetImg.GetWidth();
    m_height=tilesetImg.GetHeight();
    for(unsigned int it=0;it<image_schemaImg.GetWidth();it++){
        for(unsigned int it2=0;it2<image_schemaImg.GetHeight();it2++){
            Type newTile;
            newTile.colorPix = image_schemaImg.GetPixel(it, it2);
            newTile.zoneRect=sf::IntRect(it*TILEWIDTH, it2*TILEHEIGHT, TILEWIDTH*(it+1), TILEHEIGHT*(it2+1));
            m_typeList.insert(m_typeList.end(),newTile);
        }
    }
    FILE* tilePropFile = NULL;
	tilePropFile = fopen(tileprop, "r");
	if(tilePropFile==NULL){ cerr<<"[FATAL ERROR] Map not found."<<endl; exit(1);}
	int Visible,Solid;
	for(unsigned int it=0;it<m_typeList.size();it++){
        fscanf(tilePropFile, "%d  %d",&Visible,&Solid);
        if(Visible==1)m_typeList[it].visible=true;
        else m_typeList[it].visible=false;
        if(Solid==1)m_typeList[it].solid=true;
        else m_typeList[it].solid=false;
	}
    for(int it=0;it<m_width;it++){
        vector<unsigned char> tileList;
        m_tileSet.insert(m_tileSet.end(),tileList);
        for(int it2=0;it2< m_height;it2++){
             m_tileSet[it].insert( m_tileSet[it].end(),findType(tilesetImg.GetPixel(it, it2)));
        }
    }

    m_drawSprite.SetImage(m_ImgTypeTile);
}
//void MapTile::gravity(){
//    m_player.Move(0,GRAVITY*m_app.GetFrameTime());
//}
void MapTile::setPlayer(Player &newPlayer){
    m_player=newPlayer;
}
