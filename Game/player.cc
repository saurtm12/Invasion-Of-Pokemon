#include "player.h"

namespace Model
{

Player::Player(const QPixmap& pixmap, Interface::Location loc, int max_fuel, int speed ):
    Character(pixmap, loc), max_fuel_(max_fuel), speed_(speed)
{
    fuel_ = max_fuel_;
    giveStep(speed);
}

Player::~Player()
{

}

Interface::Location Player::giveLocation() const
{
    return getLocation();
}

bool Player::isRemoved() const
{
    return false;
}

void Player::bonusFuel(int bonus)
{
    fuel_ = std::min(fuel_+bonus, max_fuel_);
}

void Player::addPokemon(Pokemon pokemon)
{
    int rareIndex = 400;
    if (pokemon.score() >= rareIndex)
    {
        fuel_ = std::min(max_fuel_, fuel_ + max_fuel_/10);
    }
    bag_.push_back(pokemon);
}

void Player::moveDirection(int horizontalMultiplier, int verticalMultiplier)
{
    if (fuel_ > 0)
    {
        if (Character::move(horizontalMultiplier, verticalMultiplier))
        {
            fuel_ -= speed_;
        }
    }
}

int Player::getFuel() const
{
    return fuel_;
}

QDialog* Player::getBag(QWidget* parent) const
{
    QDialog* bagDialog = new QDialog(parent);
    bagDialog->setWindowTitle("BAG");
    bagDialog->setFixedSize(400, 530);

    QScrollArea* area = new QScrollArea(bagDialog);
    area->setFixedSize(360, 500);
    area->move(20, 20);
    area->show();
    QGridLayout* layout = new QGridLayout(area);

    for (unsigned int i = 0; i < bag_.size(); ++i) {
        QLabel* label = new QLabel(bagDialog);
        label->setPixmap(QPixmap::fromImage(bag_.at(i).getImage()).scaled(100, 100));
        label->setFixedSize(100, 100);
        label->setStyleSheet("border-width: 2px; border-style: solid;");
        layout->addWidget(label, i / 3, i % 3);
    }

    return bagDialog;
}

void Player::remove()
{

}

void Player::move(Interface::Location loc)
{
    setTrueCoord(loc);
}

}
