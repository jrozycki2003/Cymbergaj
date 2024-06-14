module game;

import sfml.graphics;
import sfml.window;
import sfml.system;
import sfml.window.event;
import std.core;
import std.filesystem;
import std.thread;
import std.mutex;
import std.condition_variable;
import std.ranges;

export module game;

using namespace sf;
using namespace std;

class Entity {
public:
    virtual void update() = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual Vector2f getPosition() const = 0;
};

class Player : public Entity {
private:
    CircleShape shape;
    Vector2f velocity;
public:
    Player(float radius = 20) : velocity(0.f, 0.f) {
        shape.setRadius(radius);
        shape.setFillColor(Color::Blue);
        shape.setPosition(100.f, 100.f);
    }

    void update() override {
        shape.move(velocity);
    }

    void render(RenderWindow& window) override {
        window.draw(shape);
    }

    Vector2f getPosition() const override {
        return shape.getPosition();
    }

    void move(float offsetX, float offsetY) {
        velocity.x = offsetX;
        velocity.y = offsetY;
    }
};

class TextureManager {
private:
    filesystem::path directory;
    vector<Texture> textures;

public:
    TextureManager(const filesystem::path& dir) : directory(dir) {
        loadTextures();
    }

    const Texture& getTexture(size_t index) const {
        return textures[index];
    }

private:
    void loadTextures() {
        if (!filesystem::exists(directory) || !filesystem::is_directory(directory)) {
            cerr << "Invalid directory: " << directory << endl;
            return;
        }

        for (const auto& entry : filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                Texture texture;
                if (texture.loadFromFile(entry.path().string())) {
                    textures.push_back(texture);
                }
                else {
                    cerr << "Failed to load texture: " << entry.path() << endl;
                }
            }
        }
    }
};

class Game {
private:
    RenderWindow window;
    Player player;
    vector<unique_ptr<Entity>> entities;
    mutex mtx;
    condition_variable cv;
    bool isRunning;

public:
    Game() : window(VideoMode(800, 600), "SFML Game"), player(), isRunning(true) {
        entities.push_back(make_unique<Player>(player));
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    void processEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if (event.key.code == Keyboard::W)
                    player.move(0.f, -1.f);
                if (event.key.code == Keyboard::S)
                    player.move(0.f, 1.f);
                if (event.key.code == Keyboard::A)
                    player.move(-1.f, 0.f);
                if (event.key.code == Keyboard::D)
                    player.move(1.f, 0.f);
            }
        }
    }

    void update() {
        for (auto& entity : entities)
            entity->update();

        // Check collisions, update game state, etc.
    }

    void render() {
        window.clear();
        for (auto& entity : entities)
            entity->render(window);
        window.display();
    }
};

int main() {
    Game game;
    game.run();

    return 0;
}

