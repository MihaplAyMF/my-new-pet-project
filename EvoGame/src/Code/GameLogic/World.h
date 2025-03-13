#pragma once

#include <string>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <unordered_set>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "Player.h"
#include "Label.h"


class World : public sf::NonCopyable
{
public:

    explicit World(sf::RenderWindow& window, FontHolder& fonts);
    
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue(); 
    void clean();
    bool hasAlivePlayer();

private:
    void buildScene();
    void handleCollisions();
    void updateCamera();

    bool loadTexture(std::string filename);
    bool loadFromFile(std::string filename);

    void createHUD();
    void drawHUD();
    void playerUpdate();

    void cleanup();
    void saveFirstGameState();
    void saveGameState();
    void loadGameState();
    void switchMap(const std::string& filename);
    void changeMapPlayerOutsideView();

    sf::FloatRect getViewBounds() const;
    sf::FloatRect getEvoGameBounds() const;

    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderTarget& mTarget;
    sf::RenderTexture mSceneTexture;
    sf::View mWorldView, mHUDView;
    TextureHolder mTextures;
    FontHolder& mFonts;
    std::string mCurrentMap;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    Player* mPlayer;
    sf::Vector2f mGlobalPos;
    sf::Vector2f mPlayerPos;
    sf::Vector2f mStartPos;

    sf::Sprite mHeartSprite;
    sf::Sprite mCoinSprite;
    GUI::Label mCoinLabel;
    int mCoinCollected;

    std::map<std::string, std::set<int>> coinIDCollected;

};
