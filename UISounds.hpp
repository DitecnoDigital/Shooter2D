#include <bits/stdc++.h> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class UISounds : public Drawable {
    private:
        Music music;
        Sound shootSound;
        SoundBuffer soundBuffer;
        Font font;
        Text scoreText;
        Text gameOverText;
        bool live = true;
    public:
        UISounds();
        void ShootSound();
        void UpdateScore(int);
        void UpdateScorePosition(Vector2f);
        void UpdateStatus(bool);
        void UpdateGameOverPosition(Vector2f);
        virtual void draw(RenderTarget&,RenderStates) const;
};