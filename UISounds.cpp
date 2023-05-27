#include "UISounds.hpp"

UISounds::UISounds(){
    music.openFromFile("music.ogg");
    music.setLoop(true);
    music.play();
    if(!font.loadFromFile("Chernobyl.otf")){
        cout<<"Error al cargar la fuente"<<endl;
    }
    if(!soundBuffer.loadFromFile("shoot.ogg")){
        cout<<"Error al cargar el sonido"<<endl;
    }
    shootSound.setBuffer(soundBuffer);
    shootSound.setVolume(80);
    scoreText.setFont(font);
    scoreText.setCharacterSize(80);
    scoreText.setFillColor(Color::White);
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(125);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("GAME OVER");
}

void UISounds::ShootSound(){
    shootSound.play();
}

void UISounds::UpdateScore(int s){
    if(s<=9) scoreText.setString("000"+to_string(s));
    else if(s<=99) scoreText.setString("00"+to_string(s));
    else if(s<=999) scoreText.setString("0"+to_string(s));
    else scoreText.setString(to_string(s));
}

void UISounds::UpdateScorePosition(Vector2f pos){
    scoreText.setPosition(pos);
}

void UISounds::UpdateGameOverPosition(Vector2f pos){
    gameOverText.setPosition(pos);
}

void UISounds::UpdateStatus(bool s){
    live=s;
}

void UISounds::draw(RenderTarget &rt, RenderStates rs) const{
    rt.draw(scoreText,rs);
    if(!live) rt.draw(gameOverText,rs);
}