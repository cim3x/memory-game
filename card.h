#ifndef CARD_H
#define CARD_H

#include <QLayoutItem>
#include <QPushButton>
#include <QIcon>
#include <QString>

class Card : public QPushButton
{
public:
    Card(QWidget *parent = 0);
    Card(QString image, int id, QWidget *parent = 0);
    ~Card();
    void show_photo();
    void hide_photo();
    int get_id();
    void set_id(int id);
    void set_image(QString image);

private:
    int m_id;
    QString m_image;

};

#endif // CARD_H
