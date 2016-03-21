#include "window.h"
#include "card.h"

#include <cstdlib>
#include <ctime>

#include <QThread>

#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

Window::Window(QWidget *parent) : QWidget(parent, Qt::Window),
    m_tries(0),
    m_clicked(-1), //not clicked else keep clicked item id
    m_clickable(true),
    m_guessed(0),
    m_cards_pairs(12)
{
    m_mapper = new QSignalMapper(this);
    m_cards_list = new Card*[m_cards_pairs * 2];
    m_cards_names = new QString[m_cards_pairs * 2];
    set_card_names();

    QVBoxLayout *window_layout = new QVBoxLayout();

    createBoard(window_layout);
    createFooter(window_layout);

    setWindow(window_layout);
}

Window::~Window()
{
    //TODO free vars
    delete(m_mapper);
    delete(m_cards_list);
    delete(m_cards_names);
    delete(m_footer_text);
}

void Window::set_card_names(){

    m_cards_names[0] = QString(":/images/1.jpg");
    m_cards_names[1] = QString(":/images/2.jpg");
    m_cards_names[2] = QString(":/images/3.jpg");
    m_cards_names[3] = QString(":/images/4.jpg");
    m_cards_names[4] = QString(":/images/5.jpg");
    m_cards_names[5] = QString(":/images/6.jpg");
    m_cards_names[6] = QString(":/images/7.jpg");
    m_cards_names[7] = QString(":/images/8.jpg");
    m_cards_names[8] = QString(":/images/9.jpg");
    m_cards_names[9] = QString(":/images/10.jpg");
    m_cards_names[10] = QString(":/images/11.jpg");
    m_cards_names[11] = QString(":/images/12.jpg");
}

void Window::createBoard(QVBoxLayout* window_layout){
    QGridLayout *grid = new QGridLayout();

    int cards = m_cards_pairs * 2; //number of all cards

    int per_row = 6;
    int row = 0;
    int col = 0;
    for(int i=0;i<cards;i++){

        Card *card = new Card();

        connect(card, SIGNAL(clicked()), m_mapper, SLOT(map()));
        grid -> addWidget(card, row, col);
        m_cards_list[i] = card;

        col++;
        if(col >= per_row){
            col = 0;
            row++;
        }
    }

    shuffleBoard();
    connect(m_mapper, SIGNAL(mapped(int)), this, SLOT(on_card_clicked(int)));
    window_layout -> addLayout(grid);

}

void Window::on_card_clicked(const int index){

    if(m_clickable){
        m_tries++; //increment counter
        m_footer_text -> setText(QString("You tried %1 times").arg(m_tries));

        Card *card = m_cards_list[index];

        card -> show_photo();
        if(m_clicked < 0){
            m_clicked = index;
        }else{
            m_clickable = false; //disallow further clicking when two buttons clicked
            Card *clicked = m_cards_list[m_clicked];

            int id1 = card -> get_id();
            int id2 = clicked -> get_id();

            if(id1 == id2){ //check if guessed
                m_guessed++;
                if(m_guessed >= m_cards_pairs){
                    m_footer_text -> setText(QString("You won %1 in clicks").arg(m_tries));
                    m_reset_button -> setVisible(true);
                }
            }else{

                //Sleep - time for remembering images (2sec)
                QTime sleep = QTime::currentTime().addSecs(2);
                while( QTime::currentTime() < sleep )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                card -> hide_photo();
                clicked -> hide_photo();
            }
            m_clickable = true; //allow clicking
            m_clicked = -1;
        }
    }
}

void Window::shuffleBoard(){

    int cards = m_cards_pairs * 2; //number of all cards
    int *occupied = new int[m_cards_pairs]; //initialize checking array
    for(int i=0;i<m_cards_pairs;i++) occupied[i] = 0;

    srand(time(NULL));

    for(int i=0;i<cards;i++){

        int index = rand() % m_cards_pairs; // [0, 12)
        while(occupied[index] > 1){ //find first not used
           index++;
           if(index > m_cards_pairs) index = 0;
        }
        occupied[index]++;

        Card *card = m_cards_list[i];
        m_mapper->setMapping(card, i);
        card -> set_id(index);
        card -> set_image(m_cards_names[index]);
        card -> hide_photo();
    }

    delete(occupied);
}

void Window::on_reset(){
    shuffleBoard();
    m_reset_button -> setVisible(false); //hide reset button
    m_footer_text -> setText(QString("Start game"));
    m_tries = 0;
    m_guessed = 0;
}

void Window::createFooter(QVBoxLayout* window_layout){
    m_footer_text = new QLabel("Start game");
    window_layout->addWidget(m_footer_text);

    m_reset_button = new QPushButton("Play again");
    m_reset_button -> setVisible(false);
    connect(m_reset_button, SIGNAL(clicked()), this, SLOT(on_reset()));
    window_layout -> addWidget(m_reset_button);
}

void Window::setWindow(QVBoxLayout* window_layout){

    setLayout(window_layout);
    setWindowTitle("Memory game");
}
