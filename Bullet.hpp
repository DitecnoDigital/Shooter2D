#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class  Bullet : public Drawable{
    private:
        Sprite sprite;
        float vel;
        Vector2f dir;
        void Movement();
    public:
        Bullet(Vector2f,Vector2f,float,Texture&);
        void Update();
        Vector2f GetPosition();
        virtual void draw(RenderTarget&,RenderStates) const;
};
