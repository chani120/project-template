#include <cmath>
#include <string>
#include <chrono>
#include <vector>
#include "agl/window.h"


using namespace std;
using namespace glm;
using namespace agl;

struct Particle {
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec4 color;
    float rot;
    float size;
    float t;
    bool counted = false;
};

class Viewer : public Window {
public:
    Viewer() : Window () {
    }
    int score = 0;

    void setup() {
        setWindowSize(1000, 1000);

        renderer.loadTexture("particle", "../textures/tax.png", 0);
        renderer.loadTexture("coin", "../textures/coin.png", 0);
        renderer.loadTexture("bag", "../textures/bag.png", 0);
        renderer.loadTexture("name", "../textures/name.png", 0);
        renderer.loadTexture("win", "../textures/win.png", 0);
        renderer.setDepthTest(false);
        renderer.blendMode(agl::BLEND);
        renderer.loadTexture("zero", "../textures/0.png", 0);
        renderer.loadTexture("one", "../textures/1.png", 0);
        renderer.loadTexture("two", "../textures/2.png", 0);
        renderer.loadTexture("three", "../textures/3.png", 0);
        renderer.loadTexture("four", "../textures/4.png", 0);
        renderer.loadTexture("five", "../textures/5.png", 0);
        renderer.loadTexture("six", "../textures/6.png", 0);
        renderer.loadTexture("seven", "../textures/7.png", 0);
        renderer.loadTexture("eight", "../textures/8.png", 0);
        renderer.loadTexture("nine", "../textures/9.png", 0);

    }


    void createTaxes(int size)
    {

        for (int i = 0; i < size; i++)
        {
            Particle particle;
            particle.color = vec4(1, 1, 1, 1);
            particle.t = glfwGetTime();
            particle.size = 0.25;
            particle.rot = 0;
            particle.pos.x = clamp(agl::randomUnitCube().x * 3.0f, -3.0f, 3.0f);
            particle.vel = vec3(0, clamp(agl::randomUnitCube().x, -2.0f, -1.0f), 0);
            mParticles.push_back(particle);
        }
    }

    void createCoins(int size)
    {

        for (int i = 0; i < size; i++)
        {
            Particle particle;
            particle.color = vec4(.98f, 0.83f, 0.22f, 1);
            particle.t = glfwGetTime();
            particle.size = 0.15;
            particle.rot = 0;
            particle.pos.x = clamp(agl::randomUnitCube().x * 3.0f, -3.0f, 3.0f);
            particle.vel = vec3(0, clamp(agl::randomUnitCube().x, -2.0f, -1.0f), 0);
            mCoins.push_back(particle);
        }
    }

    void updateTaxes()
    {
        for (int i = 0; i < mParticles.size(); i++) {
            mParticles[i].pos = mParticles[i].pos + (mParticles[i].vel * dt());
            if (mParticles[i].pos.y <= -1.5f) {
                mParticles[i].t = glfwGetTime();
                mParticles[i].size = 0.25;
                mParticles[i].rot = 0;
                mParticles[i].pos = position;
                mParticles[i].vel.y = clamp(agl::randomUnitCube().x, -2.0f, -1.0f);

            }
        }
    }

    void updateCoins()
    {
        for (int i = 0; i < mCoins.size(); i++) {
            mCoins[i].pos = mCoins[i].pos + (mCoins[i].vel * dt());
            mCoins[i].rot += 0.1f;
            if (mCoins[i].pos.y <= -1.5f) {
                mCoins[i].t = glfwGetTime();
                mCoins[i].size = 0.15;
                mCoins[i].rot += 2;
                mCoins[i].pos = position;
                mCoins[i].vel.y = clamp(agl::randomUnitCube().x, -2.0f, -1.0f);

            }
        }
    }


    void drawTaxes()
    {
        renderer.texture("image", "particle");
        for (int i = 0; i < mParticles.size(); i++)
        {
            Particle particle = mParticles[i];
            renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
        }
    }

    void drawCoins() {
        renderer.texture("image", "coin");
        for (int i = 0; i < mCoins.size(); i++)
        {
            Particle particle = mCoins[i];
            renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
        }
    }

    void checkBagCoinCollision() {
        for (int i = 0; i < mCoins.size(); i++)
        {
            if ((mCoins[i].pos.y <= bagPos.y + 0.25) && (mCoins[i].pos.y >= bagPos.y - 0.25) && (mCoins[i].pos.x <= bagPos.x + 0.25) && (mCoins[i].pos.x >= bagPos.x - 0.25) && !mCoins[i].counted) {
                mCoins[i].color = vec4(1, 0, 0, 0);
                mCoins[i].counted = true;
                points++;
                
            }
            if (points == 20) {
                bagColor = vec4(1, 0, 0, 0);
            }
            if (points > 20) {
                points = 20;
            }
        
        }
    }

    void checkBagTaxCollision() {
        for (int i = 0; i < mParticles.size(); i++)
        {
            if ((mParticles[i].pos.y <= bagPos.y + 0.25) && (mParticles[i].pos.y >= bagPos.y - 0.25) && (mParticles[i].pos.x <= bagPos.x + 0.25) && (mParticles[i].pos.x >= bagPos.x - 0.25) && !mParticles[i].counted) {
                mParticles[i].color = vec4(1, 0, 0, 0);
                mParticles[i].counted = true;
                if (points != 20) {
                    points--;
                    if (points < 0) {
                        points = 0;
                    }
                }
            }
        }
    }


    void mouseMotion(int x, int y, int dx, int dy) {
    }

    void mouseDown(int button, int mods) {
    }

    void mouseUp(int button, int mods) {
    }

    void scroll(float dx, float dy) {
        eyePos.z += dy;
    }

    void keyUp(int key, int mods) {
        if (key == GLFW_KEY_LEFT) {
            bagPos.x -= 0.15;
        }
        else if (key == GLFW_KEY_RIGHT) {
            bagPos.x += 0.15;
        }
    }

    void draw() {

        renderer.beginShader("sprite");
        position.x = clamp(agl::randomUnitCube().x * 3.0f, -3.0f, 3.0f);
        position.y = 3.0f;

        if (glfwGetTime() - createTimeC >= 1.5) {
            createCoins(1);
            createTimeC = glfwGetTime();
        }
        if (glfwGetTime() - createTimeT >= 2) {
            createTaxes(1);
            createTimeT = glfwGetTime();
        }
        float aspect = ((float)width()) / height();
        renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
        renderer.lookAt(eyePos, lookPos, up);
        checkBagCoinCollision();
        checkBagTaxCollision();
        drawScore(points);
        updateTaxes();
        updateCoins();
        drawTaxes();
        drawCoins();
        renderer.scale(vec3(1, 0.6, 1));
        renderer.texture("image", "bag");
        renderer.sprite(bagPos, bagColor, 1.2, 0);
        renderer.texture("image", "name");
        renderer.sprite(vec3(0.1, 2.5, 0), vec4(1), 1, 0);
        if (points == 20) {
            renderer.texture("image", "win");
            renderer.sprite(vec3(0, 0, 0), vec4(1), 6, 0);
        }
        renderer.endShader();
    }

protected:
    string numPics[10] ={ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    vec3 eyePos = vec3(0, 0, 3);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    vec3 position = vec3(1, 2, 0);
    int createTimeC = 1;
    int createTimeT = 1;
    std::vector<Particle> mParticles;
    std::vector<Particle> mCoins;
    vec3 bagPos = vec3(0, -1, 0);
    vec4 bagColor = vec4(1);
    int points = 0;

    void drawScore(int s) {
        if (s < 21) {
            int hold = s;
            int onesInd = hold % 10;
            hold = hold / 10;
            int tensInd = hold % 10;
            hold = hold / 10;
            int hundsInd = hold % 10;
            renderer.push();
            renderer.texture("image", numPics[onesInd]);
            renderer.sprite(vec3(1.7, 1.6, 0), vec4(1), .3, 0);
            renderer.texture("image", numPics[tensInd]);
            renderer.sprite(vec3(1.5, 1.6, 0), vec4(1), .3, 0);
            renderer.texture("image", numPics[hundsInd]);
            renderer.sprite(vec3(1.3, 1.6, 0), vec4(1), .3, 0);
            renderer.pop();
        }
    }
    
};

int main(int argc, char** argv)
{
    Viewer viewer;
    viewer.run();
    return 0;
}

