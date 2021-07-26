#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QMouseEvent>
#include "ui_QtApplication.h"


class QtApplication : public QWidget
{
    Q_OBJECT

public:
    QtApplication(QWidget *parent = Q_NULLPTR);
    ~QtApplication();

private:
    QPushButton* playBtn; // кнопка начала новой игры
    QPushButton* quitBtn; // кнопка выхода из приложения
    QPushButton* gameSettingsBtn; // кнопка принятия настроек игры (размера поля и права первого хода)
    QPushButton* restartGameBtn; // кнопка перезапуска игры
    QLineEdit* sizeLine; //строка для ввода размера поля
    QComboBox* validatorComboBox; //выпадающее меню выбора крестики или нолики ходят первыми
    QLineEdit* currentTurnLine; //строка выводящая на экран, крестики или нолики сейчас ходят
    QRect* bufRectPress; //Прямоугольник, содержащий координаты клетки, на которую нажали мышью
    QRect* bufRectMouseMove; //Прямоугольник, содержащий координаты клетки, над которой сейчас находится мышь
    QRect*** cellField; // Указатель на двумерный динамический массив имитирующий игровое поле. 
                        // Каждый элемент - указатель на объект QRect, содержащий координаты и размеры каждой клетки поля

    int fieldSize; //Размер игрового поля
    bool currentTurn; //Отвечает за то, крестики сейчас ходят или нолики
    int numOfCurTurn; //Количество ходов обоих игроков
    int** Field; // Указатель на двумерный динамический массив имитирующий игровое поле, 
                 // если значение элемента массива равно 1 - в клетке игрового поля с таким же индексом (как и у элемента) нолик, если 2 - в клетке крестик
    int iRect; //Индекс строки в массиве cellField
    int jRect; //Индекс столбца в массиве cellField
    int cellWidth; //Ширина одной клетки игрового поля в пикселях
    int cellHeight; //Высота одной клетки игрового поля в пикселях

    void winnerOutput(int i, int j); // Метод завершающий игру и отправляющий сообщение о победителе

    void drawOutput(); // Метод завершающий игру и отправляющий сообщение о ничьей

public slots:
    void quit();
    void play();
    void setField();
    void restartGame();

protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
};

