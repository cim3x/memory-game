#include "card.h"

#include <QPixmap>

Card::Card(QWidget *parent) : QPushButton(parent)
{

    QSize size(100,150);
    setFixedSize(size);
    setIconSize(size);
}

Card::Card(QString image, int id, QWidget *parent) :
    QPushButton(parent),
    m_image(image),
    m_id(id)
{
    QSize size(100,150);
    setFixedSize(size);
    setIconSize(size);
}

Card::~Card(){
}

void Card::show_photo(){
    setIcon(QIcon(QPixmap(m_image)));
    setEnabled(false);
}

void Card::hide_photo(){
    setIcon(QIcon());
    setEnabled(true);
}

int Card::get_id(){
    return m_id;
}

void Card::set_id(int id){
    m_id = id;
}

void Card::set_image(QString image){
    m_image = image;
}
