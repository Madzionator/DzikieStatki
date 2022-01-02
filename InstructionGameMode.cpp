#include "InstructionGameMode.h"
#include "Game.h"
#include "MenuGameMode.h"
#include "System.h"
#include "Textures.h"

InstructionGameMode::InstructionGameMode() : menuButton(this, L"Powrót do menu", sf::Vector2f(200, 40), true)
{
	auto size = System::Window->getView().getSize();
	background = sf::Sprite(*Textures::get()->MenuBackgroundTexture, sf::IntRect(0, 0, size.x, size.y));
	background.setColor(sf::Color(255, 255, 255, 100));

	header.setSize(sf::Vector2f(System::Window->getView().getSize().x, 50));
	header.setFillColor(sf::Color(214, 207, 78, 255));

	title = sf::Text(L"Jak grać?", *System::Font, 24);
	title.setFillColor(sf::Color(55, 2, 2, 255));
	title.setPosition(18, 10);

	subtitle1 = sf::Text(L"I - Ustawienie statków", *System::Font, 18);
	subtitle2 = sf::Text(L"II - Rozgrywka", *System::Font, 18);
	subtitle3 = sf::Text(L"III - Koniec gry", *System::Font, 18);
	subtitle1.setFillColor(sf::Color(225, 225, 225, 255));
	subtitle2.setFillColor(sf::Color(225, 225, 225, 255));
	subtitle3.setFillColor(sf::Color(225, 225, 225, 255));
	subtitle1.setStyle(sf::Text::Bold);
	subtitle2.setStyle(sf::Text::Bold);
	subtitle3.setStyle(sf::Text::Bold);
	subtitle1.setPosition(18, 65);
	subtitle2.setPosition(18, 230);
	subtitle3.setPosition(18, 355);

	std::wstring desc1 = LR"(Gra pozwala na tworzenie statków o dowolnym kształcie, który jesteś w stanie sobie wyobrazić.
	Spełniać musi on jednak kilka zasad dla zachowania sprawiedliwej rozgrywki:
	- musi istnieć przynajmniej jeden statek,
	- długość statku nie może przekroczyć 8 pól,
	- statki nie mogą się ze sobą stykać, nawet po skosie,
	- na planszy może się znajdować maksymalnie 10 statków,
	- suma pól zajętych przez statki nie może przekroczyć 40.)" ;

	std::wstring desc2 = LR"(Komputer wygenerował tę samą liczbę statków co Ty (o tej samej długości, ale innym możliwym kształcie i pozycji).
Spróbuj zestrzelić je wszystkie zanim komputer zestrzeli Twoje! Pierwszy ruch należy do Ciebie, strzały wykonujemy
lewym klawiszem myszy. Tury odbywają się na przemian z komputerem, po celnym strzale ma się kolejny ruch.
Możesz sobie ułatwić stawiając lilie wodne w miejsca, gdzie uważasz, że na pewno nie będzie statku przeciwnika.
Stawia się je prawym przyciskiem myszy, a w ich pozycję nie da się strzelić. W każdym momencie możesz je usunąć.)";

	std::wstring desc3 = LR"(Gra się kończy gdy któraś ze stron zniszczy wszystkie statki przeciwnika. W przypadku Twojej przegranej,
nieodkryte jeszcze statki przeciwnika zostają ukazane, abyś mógł zobaczyć jak blisko zwycięstwa byłeś.)";

	description1 = sf::Text(desc1, *System::Font, 16);
	description2 = sf::Text(desc2, *System::Font, 16);
	description3 = sf::Text(desc3, *System::Font, 16);
	description1.setFillColor(sf::Color(225, 225, 225, 255));
	description2.setFillColor(sf::Color(225, 225, 225, 255));
	description3.setFillColor(sf::Color(225, 225, 225, 255));
	description1.setPosition(18, 90);
	description2.setPosition(18, 255);
	description3.setPosition(18, 380);

	menuButton.onClick = [] { Game::SetGameMode(new MenuGameMode()); };
	menuButton.setPosition(size.x / 2, 450);
}

void InstructionGameMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	target.draw(header, states);
	target.draw(title, states);
	target.draw(subtitle1, states);
	target.draw(description1, states);
	target.draw(subtitle2, states);
	target.draw(description2, states);
	target.draw(subtitle3, states);
	target.draw(description3, states);
	target.draw(menuButton, states);
}

void InstructionGameMode::update(sf::Time deltaTime)
{
	menuButton.update(deltaTime);
}