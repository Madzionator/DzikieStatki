#include "Board.h"
#include "ShipTile.h"
#include "Textures.h"
#include "WaterTile.h"

Board::Board(Entity* parent) : Entity(parent)
{
	boardBackground = sf::Sprite(*Textures::get()->BoardBackgroundTexture);
	boardBackground.setPosition(-42, -42);

	tiles = new Tile * [tileCount * tileCount];
	for (int y = 0; y < tileCount; y++)
		for (int x = 0; x < tileCount; x++)
		{
			auto tile = new WaterTile(this);
			tiles[y * tileCount + x] = tile;
			tile->setPosition(x * tileSize, y * tileSize);
		}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(boardBackground, states);
	for (int i = 0; i < tileCount * tileCount; i++)
		target.draw(*tiles[i], states);
}

void Board::update(sf::Time delta_time)
{
	for (int i = 0; i < tileCount * tileCount; i++)
		tiles[i]->update(delta_time);

	if (isDrawing && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) isDrawing = false;

	if (isEditMode)
	{
		for (int x = 0; x < tileCount * tileCount; x++)
			if (tiles[x]->IsLeftMouseDown)
			{
				auto tile = tiles[x];
				if (!isDrawing)
				{
					isDrawing = true;
					drawType = tile->TileType;
				}
				if (tile->TileType == drawType)
				{
					tiles[x] = tile->TileType == TileType::Ship
						? (Tile*) new WaterTile(this)
						: (Tile*) new ShipTile(this);
					tiles[x]->setPosition(tile->getPosition());
					delete tile;
				}
			}
	}
}

Board::~Board()
{
	ships.clear();
	std::vector<Ship*>().swap(ships);
	delete[] tiles;
}