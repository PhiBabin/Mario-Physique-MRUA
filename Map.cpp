
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
     float movHorTest=m_player.GetVelx()*m_app.GetFrameTime();
     float movVerTest=m_player.GetVely()*m_app.GetFrameTime();
//    if(collisionPlayerHorizontal(m_player.GetPlayerRect())||collisionPlayerVertical(m_player.GetPlayerRect())){
//        cout<<m_player.GetPosition().x<<"maman"<<m_player.GetPosition().y<<endl;
//    }
//

    //if(!collisionPlayerGeneral(m_player.GetMovedPlayerRect(movHorTest,movVerTest))){
//        m_player.Gravity();
//       //m_player.Move(m_player.GetVelx()*m_app.GetFrameTime(),0);
//       movHor=movHorTest;
//       movVer=movVerTest;
//    }
  //  else{
//DEGRES(ASIN(
//            (SIN(RADIANS(180-E7))*D4)/E4
//            ))
//DEGRES(ASIN((D4/E4)*SIN(RADIANS(97,7))))
         if(!collisionPlayerHorizontal(m_player.GetMovedPlayerRect(movHorTest,0))){
           //m_player.Move(m_player.GetVelx()*m_app.GetFrameTime(),0);
           movHor=movHorTest;
        }//cout<<"help"<<endl;
        if(!collisionPlayerVertical(m_player.GetMovedPlayerRect(0,movVerTest))){
            m_player.Gravity();
           // m_player.Move(0,m_player.GetVely()*m_app.GetFrameTime());
           movVer=movVerTest;
        }
        if(collisionTriangle(m_player.GetMovedPlayerRect(movHorTest,0))/*&&collisionPlayerVertical(m_player.GetMovedPlayerRect(0,movVerTest))*/){
            sf::IntRect playerRect=m_player.GetMovedPlayerRect(movHorTest,0);
            float x= (playerRect.Right-playerRect.Left)/2+playerRect.Left;
            float y= playerRect.Bottom;
            float a1=(m_triangleSprite.GetPointPosition(0).y-m_triangleSprite.GetPointPosition(1).y)/(m_triangleSprite.GetPointPosition(0).x-m_triangleSprite.GetPointPosition(1).x);
            float a2=(m_triangleSprite.GetPointPosition(2).y-m_triangleSprite.GetPointPosition(0).y)/(m_triangleSprite.GetPointPosition(2).x-m_triangleSprite.GetPointPosition(0).x);
            float a3=(m_triangleSprite.GetPointPosition(2).y-m_triangleSprite.GetPointPosition(1).y)/(m_triangleSprite.GetPointPosition(2).x-m_triangleSprite.GetPointPosition(1).x);

            float b1=m_triangleSprite.GetPointPosition(1).y-(a1*m_triangleSprite.GetPointPosition(1).x);
            float b2=m_triangleSprite.GetPointPosition(0).y-(a2*m_triangleSprite.GetPointPosition(0).x);
            float b3=m_triangleSprite.GetPointPosition(2).y-(a3*m_triangleSprite.GetPointPosition(2).x);
            //cout<<"blabla"<<endl;
            //cout<<a1<<" b="<<b1<<" x="<<m_triangleSprite.GetPointPosition(0).x<<" y="<<m_triangleSprite.GetPointPosition(0).y<<" x="<<m_triangleSprite.GetPointPosition(1).x<<" y="<<m_triangleSprite.GetPointPosition(1).y<<endl;

            float difference1=x-((y-b1)/a1);
            float difference2=x-((y-b3)/a3);
            if(difference1<0)difference1*=-1;
            if(difference2<0)difference2*=-1;

           // cout<<"1="<<difference1<<" 2="<<difference2<<endl;

            if(difference1<difference2){
                movVer=a1*(x)+b1-playerRect.Bottom;
                // A ne pas supprimer:
                //cos(atan(a+b))*movy=x
                //y=a*x+b

              //  cout<<"cote gauche"<<endl;
                movHor=movHorTest;
            }
            if(difference1>difference2){
                movVer=a3*(x)+b3-playerRect.Bottom;
               // cout<<"cote droit"<<endl;
                movHor=movHorTest;
            }
               //&&y-a2*x+b2&&y-a3*x+b3)return true;
           // else return false;
           //movVer=movVerTest;
        }
   // }
    if(!collisionPlayerGeneral(m_player.GetMovedPlayerRect(movHor,movVer)))m_player.Move(movHor,movVer);
  //  collisionPlayer();
 }
bool MapTile::collisionTriangle(const sf::IntRect playerRect){
    if(m_triangle){
        float x= (playerRect.Right-playerRect.Left)/2+playerRect.Left;
        float y= playerRect.Bottom;
        float a1=(m_triangleSprite.GetPointPosition(0).y-m_triangleSprite.GetPointPosition(1).y)/(m_triangleSprite.GetPointPosition(0).x-m_triangleSprite.GetPointPosition(1).x);
        float a2=(m_triangleSprite.GetPointPosition(2).y-m_triangleSprite.GetPointPosition(0).y)/(m_triangleSprite.GetPointPosition(2).x-m_triangleSprite.GetPointPosition(0).x);
        float a3=(m_triangleSprite.GetPointPosition(2).y-m_triangleSprite.GetPointPosition(1).y)/(m_triangleSprite.GetPointPosition(2).x-m_triangleSprite.GetPointPosition(1).x);

        float b1=m_triangleSprite.GetPointPosition(1).y-(a1*m_triangleSprite.GetPointPosition(1).x);
        float b2=m_triangleSprite.GetPointPosition(0).y-(a2*m_triangleSprite.GetPointPosition(0).x);
        float b3=m_triangleSprite.GetPointPosition(2).y-(a3*m_triangleSprite.GetPointPosition(2).x);
       // cout<<a1<<" b="<<b1<<" x="<<m_triangleSprite.GetPointPosition(0).x<<" y="<<m_triangleSprite.GetPointPosition(0).y<<" x="<<m_triangleSprite.GetPointPosition(1).x<<" y="<<m_triangleSprite.GetPointPosition(1).y<<endl;
        if(y>=a1*x+b1&&y<=a2*x+b2&&y>=a3*x+b3)return true;
        else return false;
    }
    else{
        return false;
    }

}
 bool MapTile::collisionPlayerGeneral(const sf::IntRect playerRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    bool Collision=false;
    if(collisionTriangle(playerRect))Collision=true;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Bottom-1)/TILEHEIGHT;
    maxWidth=(playerRect.Right-1)/TILEWIDTH;
    if(minHeight<0)minHeight=0;
    if(maxHeight>m_height)maxHeight=m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>m_width)maxWidth=m_width;
    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if(!(x>=m_width or y>=m_height)){
                if(m_typeList[m_tileSet[x][y]].solid){
                   sf::IntRect  theTile(x*TILEWIDTH,y*TILEHEIGHT,(x+1)*TILEWIDTH,(y+1)*TILEHEIGHT);
                    if(playerRect.Intersects(theTile)){
                       cout<<"i hope it work";
                       return true;
                    }
                    cout<<endl;
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
    if(collisionTriangle(playerRect))CollisionHorizontal=true;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Bottom-1)/TILEHEIGHT;
    maxWidth=(playerRect.Right-1)/TILEWIDTH;

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
                    if(x*TILEWIDTH>=playerRect.Left&&x*TILEWIDTH<=playerRect.Right){
                        cout<<" ====Droit==";
                        CollisionHorizontal= true;
                    }
                    if((x+1)*TILEWIDTH<=playerRect.Right&&(x+1)*TILEWIDTH>=playerRect.Left){
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
    if(collisionTriangle(playerRect)){
        CollisionVertical=true;
        m_player.UnlockJump();
        m_player.BottomCollision(true);
    }
 //   cout<<"Start"<<endl;
    minHeight=playerRect.Top/TILEHEIGHT;
    minWidth=playerRect.Left/TILEWIDTH;
    maxHeight=(playerRect.Bottom-1)/TILEHEIGHT;
    maxWidth=(playerRect.Right-1)/TILEWIDTH;

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
                    if(y*TILEHEIGHT<=playerRect.Bottom&&y*TILEHEIGHT>=playerRect.Top){
                        cout<<" ====sol==";
                        m_player.UnlockJump();
                        m_player.BottomCollision(true);
                        //if(m_player.GetVelx()>=0)m_player.setAnimRow(0);
                        //else m_player.setAnimRow(1);
                        //else m_player.animRow(1);
                        CollisionVertical= true;
                    }
                    if((y+1)*TILEHEIGHT>=playerRect.Top&&(y+1)*TILEHEIGHT<=playerRect.Bottom){
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
///    cout<<"x"<<m_player.GetPosition().x<<"y"<<m_player.GetPosition().y<<"Velx"<<m_player.GetVelx()<<"Vely"<<m_player.GetVely()<<endl;
    unsigned char typeNbr;
    sf::FloatRect views=m_app.GetView().GetRect();
    int maxHeight, minHeight, maxWidth, minWidth;
    // (10*40+80-(10*40))/40
    //(400+80-400)/40
    minHeight=views.Top/TILEHEIGHT-1;
    maxHeight=views.Bottom/TILEHEIGHT+1;
    minWidth=views.Left/TILEWIDTH-1;
    maxWidth=views.Right/TILEWIDTH+1;
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
    m_app.Draw(m_player);
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
