#ifndef WINDOW_H
#define WINDOW_H

#include "card.h"

#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QSignalMapper>
#include <QList>
#include <QLabel>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

public slots:
    void on_card_clicked(int index);
    void on_reset();

private:

    void set_card_names();
    void createBoard(QVBoxLayout* window_layout);
    void shuffleBoard();
    void createFooter(QVBoxLayout* window_layout);
    void setWindow(QVBoxLayout* window_layout);

    int m_tries;
    int m_clicked;
    bool m_clickable;
    int m_guessed;
    const int m_cards_pairs;

    QString *m_cards_names;
    Card **m_cards_list;
    QLabel *m_footer_text;
    QPushButton *m_reset_button;
    QSignalMapper *m_mapper;

};

#endif // WINDOW_H
