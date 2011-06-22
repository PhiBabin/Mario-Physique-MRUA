#include "includes.hpp"


int main()
{
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Heritage", sf::Style::Close | sf::Style::Titlebar );
    //App.SetFramerateLimit(60);
    App.UseVerticalSync(true);
    float x,y;
    bool menu=true;
    bool triangle,point,schema,show=false;
   // triangle=false;
    sf::Image imgPlayer;
	imgPlayer.LoadFromFile("sprite4.png");
	imgPlayer.SetSmooth(false);
	imgPlayer.CreateMaskFromColor(sf::Color(0,0,0));
    Player newPlayer(imgPlayer,20.f,360.f);
    newPlayer.SetPosition(20,360);
	MapTile myMap(App,"level11.png","tile4.png","tileimage8.png","tileprop3.txt",newPlayer);

    sf::Image backgroundImg;
    backgroundImg.LoadFromFile("background.png");
	backgroundImg.SetSmooth(false);
	sf::Sprite background(backgroundImg);

    sf::Image heritImg;
    heritImg.LoadFromFile("projet heritage.png");
	heritImg.SetSmooth(false);
	sf::Sprite herit(heritImg);
    herit.SetPosition(10,420);

    sf::Image proImg;
    proImg.LoadFromFile("protic.png");
	proImg.SetSmooth(false);
	sf::Sprite pro(proImg);
    pro.SetPosition(500,450);

    sf::String titre("Les collisions et l'optimisation",sf::Font::GetDefaultFont(), 40);
    titre.SetColor(sf::Color(0, 0, 0));
    titre.SetPosition(150,5);

    sf::Image CrochetImg;
    CrochetImg.LoadFromFile("crochet.png");
	CrochetImg.SetSmooth(false);


    sf::Image XImg;
    XImg.LoadFromFile("x.png");
	XImg.SetSmooth(false);


	sf::String back("Retour",sf::Font::GetDefaultFont(), 24);
    back.SetColor(sf::Color(255, 255, 255));
   back.SetPosition(600,500);


	sf::Sprite symbCollision(CrochetImg);
	symbCollision.SetPosition(250,0);
	sf::String collisionText("Il ya une collision.",sf::Font::GetDefaultFont(), 24);
    collisionText.SetColor(sf::Color(255, 255, 255));
   collisionText.SetPosition(330,10);
    sf::Shape triangleShape;
    triangleShape.AddPoint(60, 510,  sf::Color(255, 0, 0), sf::Color(0, 128, 128));
     triangleShape.AddPoint(150, 300,  sf::Color(255, 0, 0), sf::Color(0, 128, 128));
    triangleShape.AddPoint(500, 510,  sf::Color(255, 0, 0), sf::Color(0, 128, 128));
     triangleShape.SetColor(sf::Color(255, 255, 255, 200));
    sf::Shape rectShape=sf::Shape::Rectangle(100,100,400,400, sf::Color(255, 0, 0));
       //bool monde=true;
//    sf::Font MyFont;
//    if (!MyFont.LoadFromFile("font/MyriadWebPro.ttf", 70))
//    {0
//        cerr<<"Impossible d'ouvrir la police.";
//        App.Close();
//    }
    sf::Image ButtonBack;
    ButtonBack.LoadFromFile("button2.png");
	ButtonBack.SetSmooth(false);
    sf::Sprite ButtonBackSprite;
    ButtonBackSprite.SetPosition(590,495);
    ButtonBackSprite.SetImage(ButtonBack);

    sf::Image ButtonDefault;
    ButtonDefault.LoadFromFile("button3.png");
	ButtonDefault.SetSmooth(false);
    sf::Sprite ButtonDefaultSprite;
    ButtonDefaultSprite.SetPosition(190,90);
    ButtonDefaultSprite.SetImage(ButtonDefault);

    sf::String MenuDroite("Collision point et droite",sf::Font::GetDefaultFont(), 18);
    MenuDroite.SetColor(sf::Color(255, 255, 255));
    MenuDroite.SetPosition(200,100);

    sf::String MenuPointRect("Collision point et rectangle",sf::Font::GetDefaultFont(), 18);
    MenuPointRect.SetColor(sf::Color(255, 255, 255));
    MenuPointRect.SetPosition(200,150);

    sf::String MenuPointRectSchema("Collision point et rectangle schema",sf::Font::GetDefaultFont(), 18);
    MenuPointRectSchema.SetColor(sf::Color(255, 255, 255));
    MenuPointRectSchema.SetPosition(200,250);

    sf::String MenuRectRect("Collision rectangle et rectangle",sf::Font::GetDefaultFont(), 18);
    MenuRectRect.SetColor(sf::Color(255, 255, 255));
    MenuRectRect.SetPosition(200,200);

    sf::String MenuTriangle("Collision point et triangle",sf::Font::GetDefaultFont(), 18);
    MenuTriangle.SetColor(sf::Color(255, 255, 255));
    MenuTriangle.SetPosition(200,300);

    sf::String MenuPointTrianSchema("Collision point et triangle schema",sf::Font::GetDefaultFont(), 18);
    MenuPointTrianSchema.SetColor(sf::Color(255, 255, 255));
    MenuPointTrianSchema.SetPosition(200,350);

	//myMap.loadMap("level2.png","tile2.png","tileimage3.png","tileprop.txt");
	//myMap.setPlayer(newPlayer);

   // sf::Image Image1(15, 15, sf::Color(0, 255, 7));
    sf::View View2(sf::FloatRect(40, 40, 140, 140));
    while (App.IsOpened()){
        const sf::Input& Input = App.GetInput();
        x=Input.GetMouseX();
        y=Input.GetMouseY();
        if(!menu){
            if( Input.IsMouseButtonDown(sf::Mouse::Left)){
                if(back.GetRect().Contains(x,y)){
                    menu=true;
                }
            }
        }
        if(menu){
            App.SetView(App.GetDefaultView());
            if(x>200&&x<560&&y>100&&y<400){
                show=true;
                for(int g=0;g<6;g++){
                    if(x>200&&x<560&&y>(100+(g*50))&&y<160+(g*50))
                ButtonDefaultSprite.SetPosition(190,90+(g*50));

                }
            }
            else{
                show=false;
            }
            if( Input.IsMouseButtonDown(sf::Mouse::Left)){
                if(MenuDroite.GetRect().Contains(x,y)){
                    //cout<<"Dave..."<<endl;
                    menu=false;
                    newPlayer.SetPosition(20,360);
                    point=true;
                    schema=false;
                    triangle=false;
                    myMap.loadMap("level15.png","tile4.png","tileimage8.png","tileprop3.txt",triangle);
                }
                if(MenuPointRect.GetRect().Contains(x,y)){
                    //cout<<"Dave..."<<endl;
                    menu=false;
                    newPlayer.SetPosition(20,360);
                    point=true;
                    triangle=false;
                    schema=false;
                    myMap.loadMap("level16.png","tile4.png","tileimage8.png","tileprop3.txt",triangle);
                }
                if(MenuRectRect.GetRect().Contains(x,y)){
                    //cout<<"Dave..."<<endl;
                    menu=false;
                    newPlayer.SetPosition(20,360);
                    point=false;
                    schema=false;
                    triangle=false;
                    myMap.loadMap("level16.png","tile4.png","tileimage8.png","tileprop3.txt",triangle);
                }
                if(MenuTriangle.GetRect().Contains(x,y)){
                    //cout<<"Dave..."<<endl;

                    schema=false;
                    menu=false;
                    newPlayer.SetPosition(20,360);
                    point=false;
                    triangle=true;
                    myMap.loadMap("level15.png","tile4.png","tileimage8.png","tileprop3.txt",triangle);
                }
                if(MenuPointRectSchema.GetRect().Contains(x,y)){
                    menu=false;
                    schema=true;
                    point=false;
                    triangle=false;
                }
                if(MenuPointTrianSchema.GetRect().Contains(x,y)){
                    menu=false;
                    schema=true;
                    point=true;
                    triangle=true;
                }
            }
          //  App.draw(MenuTriangle);
        }
        if(!menu){
           if(schema){
                App.SetView(App.GetDefaultView());
                if(!triangle && !point){
                    x=Input.GetMouseX();
                    y=Input.GetMouseY();
                    cout<<rectShape.GetPointPosition(3).x<<endl;
                    sf::IntRect rectangleTest(rectShape.GetPointPosition(0).x,rectShape.GetPointPosition(0).y,rectShape.GetPointPosition(2).x,rectShape.GetPointPosition(3).y);
                    if(rectangleTest.Contains(x,y)){
                        symbCollision.SetImage(CrochetImg);
                        collisionText.SetText("Il y a une collision.");
                    }
                    else {
                        symbCollision.SetImage(XImg);
                        collisionText.SetText("Il n'y a pas de collision.");
                    }

                }

                if(triangle){
                    float a1=(triangleShape.GetPointPosition(0).y-triangleShape.GetPointPosition(1).y)/(triangleShape.GetPointPosition(0).x-triangleShape.GetPointPosition(1).x);
                    float a2=(triangleShape.GetPointPosition(2).y-triangleShape.GetPointPosition(0).y)/(triangleShape.GetPointPosition(2).x-triangleShape.GetPointPosition(0).x);
                    float a3=(triangleShape.GetPointPosition(2).y-triangleShape.GetPointPosition(1).y)/(triangleShape.GetPointPosition(2).x-triangleShape.GetPointPosition(1).x);

                    float b1=triangleShape.GetPointPosition(1).y-(a1*triangleShape.GetPointPosition(1).x);
                    float b2=triangleShape.GetPointPosition(0).y-(a2*triangleShape.GetPointPosition(0).x);
                    float b3=triangleShape.GetPointPosition(2).y-(a3*triangleShape.GetPointPosition(2).x);
                    if(y>=a1*x+b1&&y<=a2*x+b2&&y>=a3*x+b3){
                        symbCollision.SetImage(CrochetImg);
                        collisionText.SetText("Il y a une collision.");
                    }
                    else {
                        symbCollision.SetImage(XImg);
                        collisionText.SetText("Il n'y a pas de collision.");
                    }
                }

           }
            else{
                App.SetView(View2);

                if (App.GetInput().IsKeyDown(sf::Key::Up))newPlayer.Jump();
                if (App.GetInput().IsKeyDown(sf::Key::Space)||App.GetInput().IsKeyDown(sf::Key::Escape))menu=true;
                newPlayer.Turn(App.GetInput().IsKeyDown(sf::Key::Left),App.GetInput().IsKeyDown(sf::Key::Right));
    //            if (App.GetInput().IsKeyDown(sf::Key::A)){
    //                myMap.loadMap("level13.png","tile4.png","tileimage8.png","tileprop3.txt",triangle);
    //            }
    //            if (App.GetInput().IsKeyDown(sf::Key::S)){
    //                myMap.loadMap("level14.png","tile4.png","tileimage8.png","tileprop3.txt",triangle);
    //            }
                myMap.thinkPlayer();
                View2.SetFromRect(newPlayer.GetViewRect());

                if(point)newPlayer.SetPoint(true);
                else newPlayer.SetPoint(false);
           }
        }
	//if (App.GetInput().IsKeyDown(sf::Key::S))myMap.loadMap("level14.png","tile4.png","tileimage8.png","tileprop3.txt");
//        if (App.GetInput().IsKeyDown(sf:d:Key::Left))  Velx=-100;
//        if (App.GetInput().IsKeyDown(sf::Key::Right)) Velx=100;
//        if (App.GetInput().IsKeyDown(sf::Key::Left)&&App.GetInput().IsKeyDown(sf::Key::Right))  Velx=0;
//        if (!App.GetInput().IsKeyDown(sf::Key::Left)&&!App.GetInput().IsKeyDown(sf::Key::Right))  Velx=0;
//        if (App.GetInput().IsKeyDown(sf::Key::Up)&&jump){Vely+=-150.f;
//        jump=false;}
//        if (App.GetInput().IsKeyDown(sf::Key::Return)){ Sprite.SetY(100); jump=false;Vely=0;}
       // if(!myMap.collisionPlayer(sf::IntRect(Sprite.GetPosition().x,Sprite.GetPosition().y+(Vely* App.GetFrameTime()),Sprite.GetPosition().x+PLAYERCOLLISIONWIDTH,Sprite.GetPosition().y+PLAYERCOLLISIONHEIGHT+(Vely* App.GetFrameTime()) )))Vely+=200.f* App.GetFrameTime();
       //if(!Collision(Sprite.GetPosition().y+(Vely* App.GetFrameTime())))Vely+=200.f* App.GetFrameTime();
      //  else Vely=0;
        //if(Collision(Sprite.GetPosition().y+(Vely* App.GetFrameTime())))jump=true;
      //  if(myMap.collisionPlayer(sf::IntRect(Sprite.GetPosition().x,Sprite.GetPosition().y+(Vely* App.GetFrameTime()),Sprite.GetPosition().x+PLAYERCOLLISIONWIDTH,Sprite.GetPosition().y+PLAYERCOLLISIONHEIGHT+(Vely* App.GetFrameTime()) )))jump=true;
       // if(!myMap.collisionPlayer(sf::IntRect(Sprite.GetPosition().x,Sprite.GetPosition().y+(Vely* App.GetFrameTime()),Sprite.GetPosition().x+PLAYERCOLLISIONWIDTH,Sprite.GetPosition().y+PLAYERCOLLISIONHEIGHT+(Vely* App.GetFrameTime()) )))Sprite.Move(0, Vely* App.GetFrameTime());
       //if(!Collision(Sprite.GetPosition().y+Vely* App.GetFrameTime()))Sprite.Move(0, Vely* App.GetFrameTime());
    //cout << Vely << endl;
		//if(Collisionx(Sprite.GetPosition().x+(Velx* App.GetFrameTime())))Sprite.Move(Velx* App.GetFrameTime(),0);
		// if(!myMap.collisionPlayer(sf::IntRect(Sprite.GetPosition().x+(Velx* App.GetFrameTime()),Sprite.GetPosition().y,Sprite.GetPosition().x+PLAYERCOLLISIONWIDTH+(Velx* App.GetFrameTime()),Sprite.GetPosition().y+PLAYERCOLLISIONHEIGHT )))Sprite.Move(Velx* App.GetFrameTime(),0);
       //cout<<Sprite.GetPosition().x<<" "<<Sprite.GetPosition().y<<endl;
        //if(myMap.collisionPlayer(sf::IntRect(Sprite.GetPosition().x,Sprite.GetPosition().y,Sprite.GetPosition().x+PLAYERCOLLISIONWIDTH,Sprite.GetPosition().y+PLAYERCOLLISIONHEIGHT )))cout<<"collision!!!"<<endl;
        //else cout<<Sprite.GetPosition().x<<endl;
       //c//out<<"i think"<<endl;

        //View2.SetFromRect(sf::FloatRect(Sprite.GetPosition().x-320, Sprite.GetPosition().y-240, Sprite.GetPosition().x+320, Sprite.GetPosition().y+240));
        //View2.SetFromRect(sf::FloatRect(Sprite.GetPosition().x-320, Sprite.GetPosition().y-240, Sprite.GetPosition().x+320, Sprite.GetPosition().y+240));
        //cout<<"wtf3"<<endl;
        sf::Event event;
        unsigned int e=0;
        while (App.GetEvent(event)&&e<5)
        {
            if (event.Type == sf::Event::Closed) App.Close();//else cout<<"wtf4"<<endl;
            e++;
        }
        App.Clear();
        if(menu){
            App.Draw(background);
            if(show)App.Draw(ButtonDefaultSprite);
            App.Draw(MenuDroite);
            App.Draw(MenuPointRect);
            App.Draw(MenuPointRectSchema);
            App.Draw(MenuPointTrianSchema);
            App.Draw(MenuRectRect);
            App.Draw(MenuTriangle);
            App.Draw(herit);
            App.Draw(pro);
            App.Draw(titre);
        }
        else{
            if(schema){
                App.Draw(background);
                App.Draw(symbCollision);
                App.Draw(collisionText);
                if(triangle)App.Draw(triangleShape);
                if(!point)App.Draw(rectShape);

            }
            else{
                myMap.draw();
            }
            App.Draw(ButtonBackSprite);
            App.Draw(back);
        }
        //newPlayer.Draw(App);
        //App.Draw(Sprite);
        App.Display();
    }
    return EXIT_SUCCESS;
}
