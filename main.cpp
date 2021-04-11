#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

constexpr int BEGIN = 1;
constexpr int WINSIZE = 10;
const vector<char> ASCIIS = {'@', '#', 'S', '%', '?', '*', '+', ';', ':', ',', '.'}; //len -> 11

void loadingFrames(vector<vector<string>> &frames){
  for(int i=BEGIN;;i++){
    string name = "TextFiles/bad_apple" + to_string(i) + ".txt";

    ifstream file(name);
    if(file.is_open()){
      string buf;
      frames.push_back(vector<string>());
      while(getline(file,buf)){
        prev(frames.end(),1)->emplace_back(buf);
      }
    }else{
      return;
    }
  }
}

void playFrames(vector<vector<string>> &frames){
  sf::RenderWindow window(sf::VideoMode(frames[0][0].size()*WINSIZE,frames[0].size()*WINSIZE*2),"BadApple");
  window.setFramerateLimit(30);

  sf::Music music;
  if(not music.openFromFile("BadApple.ogg"))
    return;

  music.play();


  int framecnt=0;

  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();


    string buf = "\e[0;0H";
    for(auto &line:frames[framecnt]){
      buf += line;
      buf += "\n";
    }
    cout<<buf<<flush;

    for(int h=0;h<frames[0].size();h++){
      for(int w=0;w<frames[0][0].size();w++){
        sf::RectangleShape rect(sf::Vector2f(WINSIZE,WINSIZE*2));
        rect.setPosition(w*WINSIZE,h*WINSIZE*2);
        for(int i=0;i<ASCIIS.size();i++){
          if(ASCIIS[i] == frames[framecnt][h][w]){
            int color = 255 - (i/11.0 * 255);
            rect.setFillColor(sf::Color(color,color,color));
          }
        }
        window.draw(rect);
      }
    }

    framecnt++;

    window.display();
  }
}

int main(){
  vector<vector<string>> frames;
  cout<<"loading frames..."<<endl;
  
  loadingFrames(frames);

  cout<<"load complete"<<endl;

  cout<<"video: "<<frames.size()<<"\n";
  cout<<"w/h: "<<frames[0][0].size()<<"/"<<frames[0].size()<<"\n";

  cout<<"playing...";

  playFrames(frames);
}
