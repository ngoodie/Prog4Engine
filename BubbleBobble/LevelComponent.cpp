#include "LevelComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include <iostream>
#include <fstream>

dae::LevelComponent::LevelComponent(std::string levelPath)
    : m_LevelPath{ levelPath }
{

}

dae::LevelComponent::~LevelComponent()
{

}

void dae::LevelComponent::Initialize()
{
    std::ifstream inFile(m_LevelPath.c_str());

    if (!inFile)
    {
        std::cerr << "Unable to open file";
        return;
    }

    GameObject* pGameObject = GetGameObject();

    std::vector<char> prevLine{};
    std::vector<char> curLine{};
    prevLine.reserve(LEVEL_LINE_SIZE);

    std::string line;
    int lineNr{ 0 };
    while (std::getline(inFile, line))
    {
        if (line.size() != LEVEL_LINE_SIZE)
        {
            std::cerr << "Level has too many or too few tiles";
            return;
        }

        char prevChar{ '0' };
        int linePos{ 0 };
        for (char c : line)
        {
            curLine.emplace_back(c);
            switch (c)
            {
            default:
            case '0':
                if (prevChar != 'e' && prevChar != '0')
                {
                    auto pTileShadowGo = std::make_shared<GameObject>();

                    if (lineNr > 0 && prevLine[linePos] == '0' && linePos > 0 && prevLine[linePos - 1] == '0')
                    {
                        pTileShadowGo->AddComponent(new TextureComponent("tile1_shadow_side_cut_top.png"));
                    }
                    else
                    {
                        pTileShadowGo->AddComponent(new TextureComponent("tile1_shadow_side.png"));
                    }
                    pTileShadowGo->SetPosition(linePos * TILE_SIZE, TILE_SIZE * 2 + lineNr * TILE_SIZE);
                    pGameObject->AddChild(pTileShadowGo);
                }
                if (lineNr > 0 && prevLine[linePos] != '0')
                {
                    auto pTileShadowGo = std::make_shared<GameObject>();
                    if (linePos > 0 && prevLine[linePos - 1] == '0')
                    {
                        pTileShadowGo->AddComponent(new TextureComponent("tile1_shadow_btm_cut_left.png"));
                    }
                    else
                    {
                        pTileShadowGo->AddComponent(new TextureComponent("tile1_shadow_btm.png"));
                    }
                    pTileShadowGo->SetPosition(linePos * TILE_SIZE, TILE_SIZE * 2 + lineNr * TILE_SIZE);
                    pGameObject->AddChild(pTileShadowGo);
                }

                if (linePos > 0 && lineNr > 0 && prevLine[linePos] == '0' && prevChar == '0' && prevLine[linePos - 1] != '0')
                {
                    auto pTileShadowGo = std::make_shared<GameObject>();
                    pTileShadowGo->AddComponent(new TextureComponent("tile1_shadow_corner.png"));
                    pTileShadowGo->SetPosition(linePos * TILE_SIZE, TILE_SIZE * 2 + lineNr * TILE_SIZE);
                    pGameObject->AddChild(pTileShadowGo);
                }
                break;
            case '1':
                auto pTileGo = std::make_shared<GameObject>();
                pTileGo->AddComponent(new TextureComponent("tile1.png"));
                pTileGo->SetPosition(linePos * TILE_SIZE, TILE_SIZE * 2 + lineNr * TILE_SIZE);
                pGameObject->AddChild(pTileGo);
                break;
            }
            //std::cout << c;
            prevChar = c;
            linePos++;
        }
        lineNr++;
        prevLine.clear();
        prevLine = curLine;
        curLine.clear();
        //std::cout << std::endl;
    }

    inFile.close();
}

void dae::LevelComponent::Update(float)
{

}

void dae::LevelComponent::FixedUpdate(float)
{

}
