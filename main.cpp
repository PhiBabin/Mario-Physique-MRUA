#include "includes.hpp"


int main(){
    /// Set the seed
    srand((unsigned)time(0));
    /// Set the Clock
    sf::Clock Clock;
    float Time = Clock.GetElapsedTime();
    float lastFrame;
    Clock.Reset();
    float frame= 50;
    /// Set the bool condition to default
    bool menu=false,record=false,mouse=false;

    /// Create the vector of data points
    vector<dataPoint*> dataList;


    /// Load the image and set the sprite of the origine point
    sf::Image imgOrigine;
	imgOrigine.LoadFromFile("origine.png");
    sf::Sprite originePoint(imgOrigine);
    originePoint.SetPosition(-300.f,-300.f);

    /// Load the font
    sf::Font MyFont;
    MyFont.LoadFromFile("font/emulogic.ttf");

    /// Create the information text
    string Message;
    sf::Text Text(Message, MyFont, 8);


    /// Load the image of the player
    sf::Image imgPlayer;
	imgPlayer.LoadFromFile("sprite4.png");
	imgPlayer.CreateMaskFromColor(sf::Color(0,0,0));

    /// Load the image player data point
    sf::Image imgPoint;
	imgPoint.LoadFromFile("point.png");

    /// Load the image and set the sprite of record button
    sf::Image imgStop_on;
	imgStop_on.LoadFromFile("stop_on.png");
	sf::Sprite stop_on(imgStop_on);

    /// Set the view width and height
    sf::View GameView(sf::FloatRect(0,0,SCREENWIDTH/2,SCREENHEIGHT/2));

    /// Create the Window
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Mario MRUA");

    /// Set the framerate
    App.EnableVerticalSync(true);
    App.SetFramerateLimit(60);

    /// Create the instance of the player
    Player newPlayer(imgPlayer,&App);

    /// Create the instance of the Map
	MapTile myMap(App,"level11.png","tile.png","tileimage.png","tileprop.txt",newPlayer);

    /// Start window loop
    while (App.IsOpened()){
        /// Check Events
        sf::Event event;
        while (App.PollEvent(event)){
            /// If any key is press close the menu
            if(event.Type == sf::Event::KeyPressed)menu=false;
            if (event.Type == sf::Event::Closed) App.Close();
        }
        /// Load Inputs
        const sf::Input& Input = App.GetInput();
        if(menu){
            /// Set the full window view.
            App.SetView(App.GetDefaultView());
        }
        else{
            /// The Scolling view
            App.SetView(GameView);

            /// Set the origin point
            if(Input.IsMouseButtonDown(sf::Mouse::Left)){
                originePoint.SetPosition(App.ConvertCoords(Input.GetMouseX()-originePoint.GetSize().x*2.f/3.f,Input.GetMouseY()-originePoint.GetSize().y*2.f/3.f));
                mouse=true;
            }
            /// If it's recording and a frame time past you add a point
            if(record&&Clock.GetElapsedTime()-lastFrame>frame){
                lastFrame = Clock.GetElapsedTime();
                dataList.push_back(new dataPoint(Clock.GetElapsedTime()-Time));
                dataList.back()->SetPosition(newPlayer.GetPosition());
                dataList.back()->SetImage(imgPoint);
                cout<< "frame"<<endl;
            }

            /// Start recording
            if (App.GetInput().IsKeyDown(sf::Key::Z)&&!record){
                Message="Recording";
                record=true;
                if(!mouse)originePoint.SetPosition(newPlayer.GetPosition());
                lastFrame = Clock.GetElapsedTime();
                Time = Clock.GetElapsedTime();
                vector<dataPoint*>().swap(dataList);
                dataList.push_back(new dataPoint(0));
                dataList.back()->SetPosition(newPlayer.GetPosition());
                dataList.back()->SetImage(imgPoint);
            }

            /// Stop the recording
            if ((App.GetInput().IsKeyDown(sf::Key::X)&&record)||(dataList.size()>200&&record)){
                record=false;
                mouse=false;
                 stringstream ss;
                 ss<<(rand()%10000)+1;;
                string const nomFichier("data/data"+ss.str()+".csv");
                Message=nomFichier+" saved.";
                ofstream monFlux(nomFichier.c_str());
                monFlux<<"\"Temps(Milliseconde)\",\"S(Px)\""<<endl;
                for(unsigned int it=0;it<dataList.size();it++)
                monFlux<<"\""<<dataList.at(it)->GetTime()<<"\""<<",\""<<-1*(dataList.at(it)->GetPosition().y-originePoint.GetPosition().y)<<"\""<< endl;
            }

            /// Player moving inputs
            if (App.GetInput().IsKeyDown(sf::Key::Up))newPlayer.Jump();
            newPlayer.Turn(App.GetInput().IsKeyDown(sf::Key::Left),App.GetInput().IsKeyDown(sf::Key::Right));

            /// Check collision
            myMap.thinkPlayer();

            /// Set the camera on Mario
            GameView.SetCenter(newPlayer.GetPosition());

            /// Move the button on the bottom of the screen
            stop_on.SetPosition(App.GetView().GetCenter().x-SCREENWIDTH/4,
            (App.GetView().GetCenter().y+SCREENHEIGHT/4)-stop_on.GetSize().y);

            /// Update and position the information text
            Text.SetString(Message);
            Text.SetPosition(App.GetView().GetCenter().x-SCREENWIDTH/4, App.GetView().GetCenter().y-SCREENHEIGHT/4);
        }
        /// Clear the screen
        App.Clear();
        if(menu){
            /// Display menu
        }
        else{
            /// Display the map
            myMap.draw();
            /// Display the data point
            for(unsigned int it=0;it<dataList.size();it++)App.Draw(*dataList.at(it));
            /// Display the origin point
            App.Draw(originePoint);
            /// Display the player
            App.Draw(newPlayer);
            /// Display the menu
            App.Draw(stop_on);
            /// Display the information text
            App.Draw(Text);
        }
        App.Display();
    }
    return EXIT_SUCCESS;
}
