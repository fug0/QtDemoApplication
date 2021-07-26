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
    QPushButton* playBtn; // ������ ������ ����� ����
    QPushButton* quitBtn; // ������ ������ �� ����������
    QPushButton* gameSettingsBtn; // ������ �������� �������� ���� (������� ���� � ����� ������� ����)
    QPushButton* restartGameBtn; // ������ ����������� ����
    QLineEdit* sizeLine; //������ ��� ����� ������� ����
    QComboBox* validatorComboBox; //���������� ���� ������ �������� ��� ������ ����� �������
    QLineEdit* currentTurnLine; //������ ��������� �� �����, �������� ��� ������ ������ �����
    QRect* bufRectPress; //�������������, ���������� ���������� ������, �� ������� ������ �����
    QRect* bufRectMouseMove; //�������������, ���������� ���������� ������, ��� ������� ������ ��������� ����
    QRect*** cellField; // ��������� �� ��������� ������������ ������ ����������� ������� ����. 
                        // ������ ������� - ��������� �� ������ QRect, ���������� ���������� � ������� ������ ������ ����

    int fieldSize; //������ �������� ����
    bool currentTurn; //�������� �� ��, �������� ������ ����� ��� ������
    int numOfCurTurn; //���������� ����� ����� �������
    int** Field; // ��������� �� ��������� ������������ ������ ����������� ������� ����, 
                 // ���� �������� �������� ������� ����� 1 - � ������ �������� ���� � ����� �� �������� (��� � � ��������) �����, ���� 2 - � ������ �������
    int iRect; //������ ������ � ������� cellField
    int jRect; //������ ������� � ������� cellField
    int cellWidth; //������ ����� ������ �������� ���� � ��������
    int cellHeight; //������ ����� ������ �������� ���� � ��������

    void winnerOutput(int i, int j); // ����� ����������� ���� � ������������ ��������� � ����������

    void drawOutput(); // ����� ����������� ���� � ������������ ��������� � ������

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

