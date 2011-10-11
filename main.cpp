/**
Copyright (C) 2011 babin philippe

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#include "includes.hpp"


int main(){
    //! Set the seed
    srand((unsigned)time(0));

    //! Set the Clock
    sf::Clock Clock;
    float Time = Clock.GetElapsedTime();
    float lastFrame;
    Clock.Reset();
    float frame;
	int Gravity;

    //! Load the configuration file
    FILE* configFile = NULL;
	configFile = fopen("config.txt", "r");
	if(configFile==NULL){ cerr<<"[FATAL ERROR] Configuration file not found."<<endl; exit(1);}
    fscanf(configFile, "%d %f",&Gravity,&frame);

    //! Set the bool condition to default
    bool record=false,mouse=false;

    //! Create the vector of data points
    vector<dataPoint*> dataList;


    //! Load the image and set the sprite of the origine point
    sf::Texture imgOrigine;
	imgOrigine.LoadFromFile("origine.png");
    sf::Sprite originePoint(imgOrigine);
    originePoint.SetPosition(-300.f,-300.f);

    //! Load the font
    sf::Font MyFont;
    MyFont.LoadFromFile("font/emulogic.ttf");

    //! Create the information text
    string Message;
    sf::Text Text(Message, MyFont, 8);

    //! Create the framerate text
    string TextInfo;
    sf::Text DataText(Message, MyFont, 8);


    //! Load the image of the player
    sf::Texture imgPlayer;
	imgPlayer.LoadFromFile("sprite4.png");

    //! Load the image player data point
    sf::Texture imgPoint;
	imgPoint.LoadFromFile("point.png");

    //! Load the image and set the sprite of record button
    sf::Texture imgRecord;
	imgRecord.LoadFromFile("record.png");
	ImgAnim Record(imgRecord,2,1);
	Record.stop();

    //! Load the image and set the sprite of stop button
    sf::Texture imgStop;
	imgStop.LoadFromFile("stop.png");
	ImgAnim Stop(imgStop,2,1);
	Stop.stop();
	Stop.setFrame(1);

    //! Set the view width and height
    sf::View GameView(sf::FloatRect(0,0,SCREENWIDTH/2,SCREENHEIGHT/2));

    //! Create the Window
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "Mario MRUA");

    //! Set the framerate
    App.EnableVerticalSync(true);
    App.SetFramerateLimit(60);

    //! Create the instance of the player
    Player newPlayer(imgPlayer,&App,Gravity);

    //! Create the instance of the Map
	MapTile myMap(App,"level.png","tile.png","tileimage.png","tileprop.txt",newPlayer);

    //! Start window loop
    while (App.IsOpened()){
        //! Check Events
        sf::Event event;
        while (App.PollEvent(event)){
            //! If any key is press close the menu
            if (event.Type == sf::Event::Closed) App.Close();
        }
        //! The Scolling view
        App.SetView(GameView);

        //! Set the origin point
        if(sf::Mouse::IsButtonPressed(sf::Mouse::Left)){
            originePoint.SetPosition(App.ConvertCoords(sf::Mouse::GetPosition().x-originePoint.GetSize().x*2.f/3.f,sf::Mouse::GetPosition().y-originePoint.GetSize().y*2.f/3.f));
            mouse=true;
        }

        //! If it's recording and a frame time past you add a point
        if(record&&Clock.GetElapsedTime()-lastFrame>frame){
            lastFrame = Clock.GetElapsedTime();
            dataList.push_back(new dataPoint(Clock.GetElapsedTime()-Time));
            dataList.back()->SetPosition(newPlayer.GetPosition());
            dataList.back()->SetTexture(imgPoint);
            cout<< "frame"<<endl;
        }

        //! Start recording
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Z)&&!record){
            Message="Recording";
            record=true;
            Record.setFrame(1);
            Stop.setFrame(0);
            if(!mouse)originePoint.SetPosition(newPlayer.GetPosition());
            lastFrame = Clock.GetElapsedTime();
            Time = Clock.GetElapsedTime();
            vector<dataPoint*>().swap(dataList);
            dataList.push_back(new dataPoint(0));
            dataList.back()->SetPosition(newPlayer.GetPosition());
            dataList.back()->SetTexture(imgPoint);
        }

        //! Stop the recording
        if ((sf::Keyboard::IsKeyPressed(sf::Keyboard::X)&&record)||(dataList.size()>=200&&record)){
            record=false;
            Record.setFrame(0);
            Stop.setFrame(1);
            mouse=false;
             stringstream ss;
             ss<<(rand()%10000)+1;
            string const nomFichier("data/data"+ss.str()+".csv");
            Message=nomFichier+" saved.";
            ofstream monFlux(nomFichier.c_str());
            monFlux<<"\"Temps(Milliseconde)\",\"x en Px\",\"y en Px\""<<endl;
            for(unsigned int it=0;it<dataList.size();it++)
                monFlux<<"\""<<dataList.at(it)->GetTime()<<"\""
                <<",\""<<(dataList.at(it)->GetPosition().x-originePoint.GetPosition().x)<<"\""
                <<",\""<<-1*(dataList.at(it)->GetPosition().y-originePoint.GetPosition().y)<<"\""<< endl;
        }

        //! Player moving inputs
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))newPlayer.Jump();
        newPlayer.Turn(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left),sf::Keyboard::IsKeyPressed(sf::Keyboard::Right));

        //! Check collision
        myMap.thinkPlayer();

        //! Set the camera on Mario
        GameView.SetCenter(newPlayer.GetPosition());

        //! Move the button on the bottom of the screen
        Record.SetPosition(App.GetView().GetCenter().x-SCREENWIDTH/4+10.f,
        (App.GetView().GetCenter().y+SCREENHEIGHT/4)-Record.GetSize().y-5.f);
        Stop.SetPosition(App.GetView().GetCenter().x-SCREENWIDTH/4+70.f,
        (App.GetView().GetCenter().y+SCREENHEIGHT/4)-Stop.GetSize().y-5.f);

        //! Update and position the information text
        Text.SetString(Message);
        Text.SetPosition(App.GetView().GetCenter().x-SCREENWIDTH/4, App.GetView().GetCenter().y-SCREENHEIGHT/4);
        stringstream ss;
        ss<<dataList.size();
        TextInfo=ss.str()+"/200";
        DataText.SetString(TextInfo);
        DataText.SetPosition(App.GetView().GetCenter().x+SCREENWIDTH/4-70.f, App.GetView().GetCenter().y-SCREENHEIGHT/4);

        //! Clear the screen
        App.Clear();
        //! Display the map
        myMap.draw();
        //! Display the data point
        for(unsigned int it=0;it<dataList.size();it++)App.Draw(*dataList.at(it));
        //! Display the origin point
        App.Draw(originePoint);
        //! Display the player
        App.Draw(newPlayer);
        //! Display the menu
        App.Draw(Record);
        App.Draw(Stop);
        //! Display the information text
        App.Draw(Text);
        App.Draw(DataText);
        ///! Diplay everything
        App.Display();
    }
    return EXIT_SUCCESS;
}
