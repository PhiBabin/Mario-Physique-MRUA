#include "includes.hpp"


int main(){
    sf::Clock Clock;
    float Time = Clock.GetElapsedTime();
    float lastFrame;
    Clock.Reset();
    float frame= 0.05;
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Mario MRUA", sf::Style::Close | sf::Style::Titlebar );
    App.UseVerticalSync(true);
    App.SetFramerateLimit(60);
    bool menu=true,record=false;
    sf::Vector2f originePoint(0.f,0.f);
    bool triangle,point,schema,show=false;

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

	MapTile myMap(App,"level11.png","tile4.png","tileimage8.png","tileprop3.txt",newPlayer);

    sf::View View2(newPlayer.GetViewRect());
    while (App.IsOpened()){
        const sf::Input& Input = App.GetInput();
        if(menu){
            App.SetView(App.GetDefaultView());
        }
        else{
            App.SetView(View2);
            //cout<< Clock.GetElapsedTime()-lastFrame<<endl;
            if(record&&Clock.GetElapsedTime()-lastFrame>frame){
                lastFrame = Clock.GetElapsedTime();
                dataList.push_back(new dataPoint(Clock.GetElapsedTime()-Time));
                dataList.back()->SetPosition(newPlayer.GetPosition());
                dataList.back()->SetImage(imgPoint);
                cout<< "frame"<<endl;
            }

            if (App.GetInput().IsKeyDown(sf::Key::Z)&&!record){
                record=true;
                if(originePoint.x==0 && originePoint.y==0)originePoint=newPlayer.GetPosition();
                lastFrame = Clock.GetElapsedTime();
                vector<dataPoint*>().swap(dataList);
                dataList.push_back(new dataPoint(0));
                dataList.back()->SetPosition(newPlayer.GetPosition());
                dataList.back()->SetImage(imgPoint);
            }
            if ((App.GetInput().IsKeyDown(sf::Key::X)&&record)||dataList.size()>200){
                record=false;
                for(int it=0;it<dataList.size();it++)cout<<dataList.at(it)->GetPosition().x-originePoint.x<<endl;
            }

            if (App.GetInput().IsKeyDown(sf::Key::Up))newPlayer.Jump();
            newPlayer.Turn(App.GetInput().IsKeyDown(sf::Key::Left),App.GetInput().IsKeyDown(sf::Key::Right));
            myMap.thinkPlayer();
            View2.SetFromRect(newPlayer.GetViewRect());
        }
        sf::Event event;
        unsigned int e=0;
        while (App.GetEvent(event))
        {
            if(event.Type == sf::Event::KeyPressed)menu=false;
            if (event.Type == sf::Event::Closed) App.Close();
            e++;
        }
        App.Clear();
        if(menu){
        }
        else{
            myMap.draw();
            for(int it=0;it<dataList.size();it++)App.Draw(*dataList.at(it));
        }
        App.Display();
    }
    return EXIT_SUCCESS;
}
