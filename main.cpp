#include "includes.hpp"


int main(){
    sf::Clock Clock;
    float Time = Clock.GetElapsedTime();
    float lastFrame;
    Clock.Reset();
    float frame= 50;
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Mario MRUA");
    App.EnableVerticalSync(true);
    App.SetFramerateLimit(60);
    bool menu=true,record=false,mouse=false;

    sf::Image imgOrigine;
	imgOrigine.LoadFromFile("origine.png");
	imgOrigine.SetSmooth(false);
    sf::Sprite originePoint(imgOrigine);
    originePoint.SetPosition(0,0);

    string Message;
    sf::Text Text(Message, sf::Font::GetDefaultFont(), 12);

    vector<dataPoint*> dataList;

    sf::Image imgPlayer;
	imgPlayer.LoadFromFile("sprite4.png");
	imgPlayer.SetSmooth(false);
	imgPlayer.CreateMaskFromColor(sf::Color(0,0,0));
    Player newPlayer(imgPlayer,&App,20.f,360.f);
    newPlayer.SetPosition(20,360);

    sf::Image imgPoint;
	imgPoint.LoadFromFile("point.png");
	imgPoint.SetSmooth(false);


    sf::Image imgStop_on;
	imgStop_on.LoadFromFile("stop_on.png");
	imgStop_on.SetSmooth(false);
	sf::Sprite stop_on(imgStop_on);

	MapTile myMap(App,"level11.png","tile4.png","tileimage8.png","tileprop3.txt",newPlayer);

    sf::View View2(newPlayer.GetViewRect());
    while (App.IsOpened()){
        const sf::Input& Input = App.GetInput();
        if(menu){
            App.SetView(App.GetDefaultView());
        }
        else{
            App.SetView(App.GetDefaultView());
           // App.SetView(View2);


            if(Input.IsMouseButtonDown(sf::Mouse::Left)){
                originePoint.SetPosition(App.ConvertCoords(Input.GetMouseX()-originePoint.GetSize().x*2.f/3.f,Input.GetMouseY()-originePoint.GetSize().y*2.f/3.f));
                mouse=true;
            }

            if(record&&Clock.GetElapsedTime()-lastFrame>frame){
                lastFrame = Clock.GetElapsedTime();
                dataList.push_back(new dataPoint(Clock.GetElapsedTime()-Time));
                dataList.back()->SetPosition(newPlayer.GetPosition());
                dataList.back()->SetImage(imgPoint);
                cout<< "frame"<<endl;
            }

            if (App.GetInput().IsKeyDown(sf::Key::Z)&&!record){
                record=true;
                if(!mouse)originePoint.SetPosition(newPlayer.GetPosition());
                lastFrame = Clock.GetElapsedTime();
                Time = Clock.GetElapsedTime();
                vector<dataPoint*>().swap(dataList);
                dataList.push_back(new dataPoint(0));
                dataList.back()->SetPosition(newPlayer.GetPosition());
                dataList.back()->SetImage(imgPoint);
            }
            if ((App.GetInput().IsKeyDown(sf::Key::X)&&record)||(dataList.size()>200&&record)){
                record=false;
                 stringstream ss;
                 ss<<rand()/RAND_MAX * (10000) ;
                string const nomFichier("data/data"+ss.str()+".csv");
                Message=nomFichier+" saved.";
                ofstream monFlux(nomFichier.c_str());
                monFlux<<"\"Temps(Milliseconde)\",\"S(Px)\""<<endl;
                for(unsigned int it=0;it<dataList.size();it++)
                //monFlux<<"\""<<round(dataList.at(it)->GetTime())<<","<<10000000*(dataList.at(it)->GetTime()-round(dataList.at(it)->GetTime()))<<"\""<<",\""<<round(dataList.at(it)->GetPosition().y-originePoint.y)<<"\""<< endl;
                monFlux<<"\""<<dataList.at(it)->GetTime()<<"\""<<",\""<<-1*(dataList.at(it)->GetPosition().y-originePoint.GetPosition().y)<<"\""<< endl;
            }

            if (App.GetInput().IsKeyDown(sf::Key::Up))newPlayer.Jump();
            newPlayer.Turn(App.GetInput().IsKeyDown(sf::Key::Left),App.GetInput().IsKeyDown(sf::Key::Right));
            myMap.thinkPlayer();
            View2.Reset(newPlayer.GetViewRect());
            stop_on.SetPosition(newPlayer.GetViewRect().Left,(newPlayer.GetViewRect().Top-newPlayer.GetViewRect().Height)-stop_on.GetSize().y);
            Text.SetString(Message);
            Text.SetPosition(newPlayer.GetViewRect().Left,newPlayer.GetViewRect().Top);
        }
        sf::Event event;
        unsigned int e=0;
        while (App.PollEvent(event)){
            if(event.Type == sf::Event::KeyPressed)menu=false;
            if (event.Type == sf::Event::Closed) App.Close();
            e++;
        }
        App.Clear();
        if(menu){
        }
        else{
            myMap.draw();
            for(unsigned int it=0;it<dataList.size();it++)App.Draw(*dataList.at(it));
            App.Draw(originePoint);
            App.Draw(newPlayer);
            App.Draw(stop_on);
            App.Draw(Text);
        }
        App.Display();
    }
    return EXIT_SUCCESS;
}
