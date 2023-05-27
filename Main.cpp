#include <bits/stdc++.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemie.hpp"
#include "UISounds.hpp"

using namespace std;
using namespace sf;

int main(){
	RenderWindow window(VideoMode(1000,650),"Shooter 2D Top Down");
	window.setFramerateLimit(60);

	View view;
	view.setSize(1000,650);
	view.setCenter(0,0);

	Texture playerTexture;
	Texture enemieTexture;
	Texture bulletTexture;
	Texture bloodTexture;
	Texture backgroundTexture;

	if(!playerTexture.loadFromFile("player.png")){
		cout<<"Error al cargar la textura"<<endl;
	}
	if(!enemieTexture.loadFromFile("enemie.png")){
		cout<<"Error al cargar la textura"<<endl;
	}
	if(!bulletTexture.loadFromFile("bullet.png")){
		cout<<"Error al cargar la textura"<<endl;
	}
	if(!bloodTexture.loadFromFile("blood.png")){
		cout<<"Error al cargar la textura"<<endl;
	}
	if(!backgroundTexture.loadFromFile("background.png")){
		cout<<"Error al cargar la textura"<<endl;
	}

	Sprite background;
	background.setTexture(backgroundTexture);
	background.setOrigin(backgroundTexture.getSize().x/2,backgroundTexture.getSize().y/2);
	background.setPosition(0,0);

	UISounds uisounds;
	Player player(playerTexture);
	vector<Enemie> enemies;
	vector<Bullet> bulletsPlayer;
	vector<pair<Sprite,float>> bloodEnemies;
	Vector2f bulletPosition;
	Vector2f playerPos;
	Vector2f enemiePos;
	bool live = true;
	int dist=350;
	int score=0;

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed) window.close();
		}

		if(live){

			srand(time(NULL));
			while((int)enemies.size()<60){
				IntRect backgroundRect(player.GetPosition().x-500,player.GetPosition().y-325,1000,650);
				int x = rand()%1450-725; int y = rand()%950-475;
				if(!backgroundRect.contains(x,y)) enemies.push_back(Enemie(Vector2f(x,y),enemieTexture));
			}

			player.Update(window,view);

			for(int i = 0; i < (int)enemies.size(); i++){
				enemies[i].Update(player.GetPosition(),dist);
			}

			playerPos = Vector2f(window.mapCoordsToPixel(player.GetPosition()));
			IntRect playerRect(playerPos.x-10,playerPos.y-10,25,25);
			for(int i = 0; i < (int)enemies.size(); i++){
				enemiePos = Vector2f(window.mapCoordsToPixel(enemies[i].GetPosition()));
				IntRect enemiesRect(enemiePos.x-10,enemiePos.y-10,25,25);
				if(enemiesRect.intersects(playerRect)) live = false;
			}

			pair<bool,Vector2f> infoBullet = player.AnswerShoot(window);
			if(infoBullet.first){
				bulletsPlayer.push_back(Bullet(Vector2f(player.GetPosition().x+infoBullet.second.x*40,player.GetPosition().y+infoBullet.second.y*40),infoBullet.second,player.GetRotation(),bulletTexture));
				uisounds.ShootSound();
			}

			for(int i = 0; i < (int)bulletsPlayer.size(); i++){
				bulletsPlayer[i].Update();
			}

			for(int i = 0; i < (int)bulletsPlayer.size(); i++){
				bulletPosition = Vector2f(window.mapCoordsToPixel(bulletsPlayer[i].GetPosition()));
				if((bulletPosition.x> 1005 || bulletPosition.x < -5)||(bulletPosition.y> 655 || bulletPosition.y < -5)){ 
					bulletsPlayer.erase(bulletsPlayer.begin()+i);
					break;
				}
				if((bulletsPlayer[i].GetPosition().x > 735 || bulletsPlayer[i].GetPosition().x < -735)||(bulletsPlayer[i].GetPosition().y > 485 || bulletsPlayer[i].GetPosition().y < -485)){
					bulletsPlayer.erase(bulletsPlayer.begin()+i);
					break;
				}
			}

			for(int i = 0; i < (int)bulletsPlayer.size(); i++){
				bulletPosition = Vector2f(window.mapCoordsToPixel(bulletsPlayer[i].GetPosition()));
				IntRect bulletRect(bulletPosition.x-0.75,bulletPosition.y-0.75,5,5);
				for(int j = 0; j < (int)enemies.size(); j++){
					enemiePos=Vector2f(window.mapCoordsToPixel(enemies[j].GetPosition()));
					IntRect enemiesRect(enemiePos.x-10,enemiePos.y-10,25,25);
					if(enemiesRect.intersects(bulletRect)){
						bulletsPlayer.erase(bulletsPlayer.begin()+i);
						enemies[j].TakeLife();
						break;
					}
				}
			}

			for(int i = 0; i < (int)enemies.size(); i++){
				if(enemies[i].ConsultLife()<=0){
					dist+=5;
					score+=5;
					Sprite sp;
					sp.setTexture(bloodTexture);
					sp.setOrigin(bloodTexture.getSize().x/2,bloodTexture.getSize().y/2);
					sp.setPosition(enemies[i].GetPosition());
					bloodEnemies.push_back({sp,255});
					enemies.erase(enemies.begin()+i);
				}
			}

			uisounds.UpdateScore(score);
			uisounds.UpdateScorePosition(Vector2f(view.getCenter().x-80,view.getCenter().y+225));
			uisounds.UpdateGameOverPosition(Vector2f(view.getCenter().x-300,view.getCenter().y-40));
		}

		uisounds.UpdateStatus(live);

		for(int i = 0; i < (int)bloodEnemies.size(); i++){
			bloodEnemies[i].second-=0.1;
			bloodEnemies[i].first.setColor(Color(255,255,255,bloodEnemies[i].second));
			if(bloodEnemies[i].second<=0) bloodEnemies.erase(bloodEnemies.begin()+i);
		}

		window.clear();
		window.setView(view);
		window.draw(background);
		for(int i = 0; i < (int)bloodEnemies.size(); i++) window.draw(bloodEnemies[i].first);
		if(live){
			for(int i = 0; i < (int)bulletsPlayer.size(); i++) window.draw(bulletsPlayer[i]);
			window.draw(player);
		}
		for(int i = 0; i < (int)enemies.size(); i++) window.draw(enemies[i]);
		window.draw(uisounds);
		window.display();
	}
	return 0;
}