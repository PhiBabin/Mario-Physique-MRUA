#include "includes.hpp"


int main()
{
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Mario MRUA", sf::Style::Close | sf::Style::Titlebar );
    App.UseVerticalSync(true);
    App.SetFramerateLimit(true);
    bool menu=true,record=false;
    sf::Vector2f originePoint(0.f,0.f);
    bool triangle,point,schema,show=false;

    vector<dataPoint> dataList;

    sf::Image imgPlayer;
	imgPlayer.LoadFromFile("sprite4.png");
	imgPlayer.SetSmooth(false);
	imgPlayer.CreateMaskFromColor(sf::Color(0,0,0));
    Player newPlayer(imgPlayer,&App,20.f,360.f);
    newPlayer.SetPosition(20,360);
	MapTile myMap(App,"level11.png","tile4.png","tileimage8.png","tileprop3.txt",newPlayer);

    sf::View View2(newPlayer.GetViewRect());
    while (App.IsOpened()){
        const sf::Input& Input = App.GetInput();
        if(menu){
            App.SetView(App.GetDefaultView());
        }
        else{
            App.SetView(View2);

            if (App.GetInput().IsKeyDown(sf::Key::Up))newPlayer.Jump();

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
        }
        App.Display();
    }
    return EXIT_SUCCESS;
}
