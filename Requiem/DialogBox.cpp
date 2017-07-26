#include "DialogBox.hpp"


DialogBox::DialogBox()
{
	mfont.loadFromFile("../resources/fonts/consola.ttf");
	mtext.setFont(mfont);
}

DialogBox::~DialogBox()
{
}

bool DialogBox::isActive() { return misActive; }
void DialogBox::isActive(bool active) { misActive = active; }

void DialogBox::addText(const std::string &_text) { mtexts.push_back(_text); }

void DialogBox::update()
{
	if (mtexts.size() > index)
		index++;
	else
		mtext.setString("Dialog box is out! :("); mtext.setScale(10.f, 10.f);

	update_dialogBox = true;
}

void DialogBox::setBounds(sf::FloatRect _bounds) { mbox = _bounds; }

sf::Sprite& DialogBox::get_dialog()
{

	//Temp: Assume the player sprite is 16x16
	const unsigned player_width = 16;

	if (!update_dialogBox)
		return dialogBox;
	else
		;//Do This v

	sf::RenderTexture ret;
	if (!ret.create(1280u, (720u / 2u) - player_width))
	{
		std::cerr << "Failed to create space to render dialog box!\n";
	}
	//TODO: Add texture for dialog box. Might look better.
	sf::RectangleShape shape;

	ret.clear();

	shape.setSize({ mbox.width, mbox.height - player_width });
	shape.setPosition({ mbox.left, mbox.top });
	shape.setPosition({ 0, 0 });
	shape.setFillColor(sf::Color(88, 88, 88));
	//shape.setOutlineColor(sf::Color::Red);
	ret.draw(shape);
	mtext.setPosition(mbox.left, mbox.top + player_width);
	ret.draw(mtext);
	ret.display();
	mbox_rendered = ret.getTexture();
	if (ret.getTexture().getSize().x == 0 || ret.getTexture().getSize().y == 0)
		std::cout << "Internal error: Failed to create buffer for dialogbox";
	dialogBox.setPosition(mbox.left, mbox.top);
	dialogBox.setTexture(mbox_rendered);
	//std::cout << "Drawing sprite at <" << dialogBox.getPosition().x << "," << dialogBox.getPosition().y << ">\nSize " << dialogBox.getGlobalBounds().width << "x" << dialogBox.getGlobalBounds().height << "\n";
	return dialogBox;
}
