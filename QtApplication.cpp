#include "QtApplication.h"
#include <QVboxLayout>
#include <QHboxLayout>
#include <QTextEdit>
#include <QIntValidator> 
#include <QLineEdit>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QComboBox>

QtApplication::QtApplication(QWidget *parent)
    : QWidget(parent)
{
    //

    setMouseTracking(true);

    // 
    
    numOfCurTurn = 0;
    fieldSize = 0;
    iRect = -1;
    jRect = -1;
    //QRect* bufRectPress = new QRect(0, 0, 0, 0); 
    //QRect* bufRectMouseMove = new QRect(0, 0, 0, 0);
    Field = nullptr;
    
    //

    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hboxmini = new QHBoxLayout();
    QHBoxLayout* hboxmini1 = new QHBoxLayout();
    QHBoxLayout* hbox = new QHBoxLayout(this);

    vbox->setSpacing(1);

    playBtn = new QPushButton("New Game", this);


    QLabel* fieldSizeLabel = new QLabel(tr("Field size:"));

    sizeLine = new QLineEdit;
    sizeLine->setPlaceholderText("Min Size 5");
    sizeLine->setValidator(new QIntValidator(5, 99, sizeLine));
    sizeLine->setReadOnly(true);


    hboxmini->addWidget(fieldSizeLabel);
    hboxmini->addSpacing(10);
    hboxmini->addWidget(sizeLine);

    QGroupBox* Turn = new QGroupBox(tr("Turns"));
    QLabel* validatorLabel = new QLabel(tr("First turn:"));
    validatorComboBox = new QComboBox;
    validatorComboBox->addItem(tr("Noughts"));
    validatorComboBox->addItem(tr("Crosses"));
    validatorComboBox->setEnabled(false);

    QLabel* currentTurnLabel = new QLabel(tr("Current turn:"));
    currentTurnLine = new QLineEdit(tr(""));
    currentTurnLine->setAlignment(Qt::AlignCenter);
    currentTurnLine->setReadOnly(true);

    hboxmini1->addWidget(currentTurnLabel);
    hboxmini1->addSpacing(10);
    hboxmini1->addWidget(currentTurnLine);


    gameSettingsBtn = new QPushButton(tr("Apply game settings"), this);
    gameSettingsBtn->setEnabled(false);

    restartGameBtn = new QPushButton(tr("Restart Game"));
    restartGameBtn->setEnabled(false);


    QGridLayout* validatorLayout = new QGridLayout;
    validatorLayout->addWidget(validatorLabel, 0, 0);
    validatorLayout->addWidget(validatorComboBox, 0, 1);

    quitBtn = new QPushButton("Quit", this);

    vbox->addWidget(playBtn);
    vbox->addSpacing(50);
    vbox->addLayout(hboxmini);
    vbox->addLayout(validatorLayout);
    vbox->addWidget(gameSettingsBtn);
    vbox->addSpacing(10);
    vbox->addWidget(restartGameBtn);
    vbox->addSpacing(250);
    vbox->addLayout(hboxmini1);
    vbox->addSpacing(250);
    vbox->addWidget(quitBtn);

    hbox->addLayout(vbox);
    hbox->addSpacing(15);
    hbox->addStretch(50);

    setLayout(hbox);

    // 

    connect(quitBtn, SIGNAL(clicked()), this, SLOT(quit()));
    connect(playBtn, SIGNAL(clicked()), this, SLOT(play()));
    connect(gameSettingsBtn, SIGNAL(clicked()), this, SLOT(setField()));
    connect(restartGameBtn, SIGNAL(clicked()), this, SLOT(restartGame()));

    //

    this->setStyleSheet("QPushButton { background-color: #C4D2D9; border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px; } QPushButton:hover { background-color: #8F98D9; } QPushButton:pressed { border-color: black; } QComboBox { background-color: #C4D2D9; border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 7em; padding: 6px; } QComboBox::drop-down { border-radius: 8px; } QComboBox::down-arrow { image: url(C:/Users/Lenovo/Pictures/Icons/down-arrow.png); width: 20px; height: 20px; } QComboBox::drop-down:hover { background-color: #8F98D9; };");
}

QtApplication::~QtApplication()
{
    for (int i = 0; i < fieldSize; i++)
    {
        delete[] Field[i];
    }

    delete[] Field;
}

void QtApplication::quit()
{
    this->close();
}

void QtApplication::play()
{
    gameSettingsBtn->setEnabled(true);
    sizeLine->setReadOnly(false);
    validatorComboBox->setEnabled(true);
    playBtn->setEnabled(false);
    fieldSize = 0;
    numOfCurTurn = 0;
}

void QtApplication::setField()
{
    bool ok;

    if ((sizeLine->text()).toInt(&ok, 10) >= 5)
    {
        fieldSize = (sizeLine->text()).toInt(&ok, 10);

        cellWidth = round((width() - 350) / fieldSize);
        cellHeight = round((height() - 14) / fieldSize);

        sizeLine->setReadOnly(true);
        gameSettingsBtn->setEnabled(false);
        validatorComboBox->setEnabled(false);

        currentTurn = validatorComboBox->currentIndex();

        Field = new int*[fieldSize];
        for (int i = 0; i < fieldSize; i++)
        {
            Field[i] = new int[fieldSize];
            for (int j = 0; j < fieldSize; j++)
            {
                Field[i][j] = 0;
            }
        }

        cellField = new QRect** [fieldSize];
        for (int i = 0; i < fieldSize; i++)
        {
            cellField[i] = new QRect*[fieldSize];
            for (int j = 0; j < fieldSize; j++)
            {
                cellField[i][j] = new QRect(0, 0, 0, 0);
            }
        }

        if (currentTurn == false)
        {
            currentTurnLine->setPlaceholderText(tr("N O U G H T S"));
        }
        else if (currentTurn == true)
        {
            currentTurnLine->setPlaceholderText(tr("C R O S S E S"));
        }

        playBtn->setEnabled(false);
        restartGameBtn->setEnabled(true);

        update();
    }
    else
    {
        QMessageBox::warning(this, "Incorrect input", "Field size must be greater than 4");
        return;
    }
}

void QtApplication::restartGame()
{
    fieldSize = 0;
    numOfCurTurn = 0;
    currentTurnLine->setPlaceholderText(tr(""));
    for (int i = 0; i < fieldSize; i++)
    {
        for (int j = 0; j < fieldSize; j++)
        {
            Field[i][j] = 0;
            cellField[i][j] = new QRect(0, 0, 0, 0);
        }
    }
    playBtn->setEnabled(true);
    update();
}

void QtApplication::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    QRect rectangle(270, 14, width() - 350, height() - 28);
    painter.drawRect(rectangle);
    if (fieldSize == 0)
    {
        painter.drawPixmap(294, 100, QPixmap("C:/Users/Lenovo/Pictures/Icons/tictactoe.png"));
    }

    if (fieldSize > 4)
    {
        int x1_v = 270 + cellWidth;
        int y1_v = 14;
        int x2_v = 270 + cellWidth;
        int y2_v = height() - 14;

        int x1_h = 270;
        int y1_h = 14 + cellHeight;
        int x2_h = width() - 80;
        int y2_h = 14 + cellHeight;

        for (int i = 0; i < fieldSize - 1; i++)
        {
            painter.drawLine(x1_v, y1_v, x2_v, y2_v);
            painter.drawLine(x1_h, y1_h, x2_h, y2_h);

            x1_v += cellWidth;
            x2_v += cellWidth;

            y1_h += cellHeight;
            y2_h += cellHeight;
        }
    }
    if (numOfCurTurn > 0)
    {
        for (int i = 0; i < fieldSize; i++)
        {
            for (int j = 0; j < fieldSize; j++)
            {
                if (Field[i][j] == 1)
                {
                    painter.drawPixmap(*cellField[i][j], QPixmap("C:/Users/Lenovo/Pictures/Icons/noughts.png"));
                }
                else if (Field[i][j] == 2)
                {
                    painter.drawPixmap(*cellField[i][j], QPixmap("C:/Users/Lenovo/Pictures/Icons/crosses.png"));
                }
            }
        }
    }

    if (e->rect().width() == cellWidth)
    {
        painter.fillRect(e->rect(), QColor("yellow"));
    }
};

void QtApplication::mousePressEvent(QMouseEvent* e)
{
    if (fieldSize >= 5)
    {
        int x1 = 270;
        int y1 = 14;

        for (int i = 0; i < fieldSize; i++)
        {
            for (int j = 0; j < fieldSize; j++)
            {
                bufRectPress = new QRect(x1, y1, cellWidth, cellHeight);
                if (bufRectPress->contains(e->x(), e->y()))
                {
                    if ((Field[i][j] == 1) || (Field[i][j] == 2))
                    {
                        QMessageBox::warning(this, "Incorrect cell", "The selected cell is already occupied!\nSelect another cell.");
                        return;
                    }
                    else if (Field[i][j] == 0)
                    {
                        Field[i][j] = currentTurn + 1;
                        cellField[i][j] = bufRectPress;
                        numOfCurTurn++;
                        if (currentTurn == false)
                        {
                            update();
                            currentTurnLine->setPlaceholderText(tr("C R O S S E S"));
                            currentTurn = true;
                        }
                        else if (currentTurn == true)
                        {
                            update();
                            currentTurnLine->setPlaceholderText(tr("N O U G H T S"));
                            currentTurn = false;
                        }
                        //
                        if (numOfCurTurn >= 9)
                        {
                            // Проверка по горизонтали

                            if ((j - 1) >= 0)
                            {
                                if (Field[i][j - 1] == Field[i][j])
                                {
                                    if ((j - 2) >= 0)
                                    {
                                        if (Field[i][j - 2] == Field[i][j])
                                        {
                                            if ((j - 3) >= 0)
                                            {
                                                if (Field[i][j - 3] == Field[i][j])
                                                {
                                                    if ((j - 4) >= 0)
                                                    {
                                                        if (Field[i][j - 4] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                    if ((j + 1) < fieldSize)
                                                    {
                                                        if (Field[i][j + 1] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                            if ((j + 1) < fieldSize)
                                            {
                                                if (Field[i][j + 1] == Field[i][j])
                                                {
                                                    if ((j + 2) < fieldSize)
                                                    {
                                                        if (Field[i][j + 2] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if ((j + 1) < fieldSize)
                                    {
                                        if (Field[i][j + 1] == Field[i][j])
                                        {
                                            if ((j + 2) < fieldSize)
                                            {
                                                if (Field[i][j + 2] == Field[i][j])
                                                {
                                                    if ((j + 3) < fieldSize)
                                                    {
                                                        if (Field[i][j + 3] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }                                                    
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if ((j + 1) < fieldSize)
                            {
                                if (Field[i][j + 1] == Field[i][j])
                                {
                                    if ((j + 2) < fieldSize)
                                    {
                                        if (Field[i][j + 2] == Field[i][j])
                                        {
                                            if ((j + 3) < fieldSize)
                                            {
                                                if (Field[i][j + 3] == Field[i][j])
                                                {
                                                    if ((j + 4) < fieldSize)
                                                    {
                                                        if (Field[i][j + 4] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            // Проверка по вертикали
                            if ((i - 1) >= 0)
                            {
                                if (Field[i - 1][j] == Field[i][j])
                                {
                                    if ((i - 2) >= 0)
                                    {
                                        if (Field[i - 2][j] == Field[i][j])
                                        {
                                            if ((i - 3) >= 0)
                                            {
                                                if (Field[i - 3][j] == Field[i][j])
                                                {
                                                    if ((i - 4) >= 0)
                                                    {
                                                        if (Field[i - 4][j] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                    if ((i + 1) < fieldSize)
                                                    {
                                                        if (Field[i + 1][j] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                            if ((i + 1) < fieldSize)
                                            {
                                                if (Field[i + 1][j] == Field[i][j])
                                                {
                                                    if ((i + 2) < fieldSize)
                                                    {
                                                        if (Field[i + 2][j] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if ((i + 1) < fieldSize)
                                    {
                                        if (Field[i + 1][j] == Field[i][j])
                                        {
                                            if ((i + 2) < fieldSize)
                                            {
                                                if (Field[i + 2][j] == Field[i][j])
                                                {
                                                    if ((i + 3) < fieldSize)
                                                    {
                                                        if (Field[i + 3][j] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if ((i + 1) < fieldSize)
                            {
                                if (Field[i + 1][j] == Field[i][j])
                                {
                                    if ((i + 2) < fieldSize)
                                    {
                                        if (Field[i + 2][j] == Field[i][j])
                                        {
                                            if ((i + 3) < fieldSize)
                                            {
                                                if (Field[i + 3][j] == Field[i][j])
                                                {
                                                    if ((i + 4) < fieldSize)
                                                    {
                                                        if (Field[i + 4][j] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // Проверка по условно главной диагонали

                            if (((j - 1) >= 0) && ((i - 1) >= 0))
                            {
                                if (Field[i - 1][j - 1] == Field[i][j])
                                {
                                    if (((j - 2) >= 0) && ((i - 2) >= 0))
                                    {
                                        if (Field[i - 2][j - 2] == Field[i][j])
                                        {
                                            if (((j - 3) >= 0) && ((i - 3) >= 0))
                                            {
                                                if (Field[i - 3][j - 3] == Field[i][j])
                                                {
                                                    if (((j - 4) >= 0) && ((i - 4) >= 0))
                                                    {
                                                        if (Field[i - 4][j - 4] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                    if (((j + 1) < fieldSize) && ((i + 1) < fieldSize))
                                                    {
                                                        if (Field[i + 1][j + 1] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                            if (((j + 1) < fieldSize) && ((i + 1) < fieldSize))
                                            {
                                                if (Field[i + 1][j + 1] == Field[i][j])
                                                {
                                                    if (((j + 2) < fieldSize) && ((i + 2) < fieldSize))
                                                    {
                                                        if (Field[i + 2][j + 2] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (((j + 1) < fieldSize) && ((i + 1) < fieldSize))
                                    {
                                        if (Field[i + 1][j + 1] == Field[i][j])
                                        {
                                            if (((j + 2) < fieldSize) && ((i + 2) < fieldSize))
                                            {
                                                if (Field[i + 2][j + 2] == Field[i][j])
                                                {
                                                    if (((j + 3) < fieldSize) && ((i + 3) < fieldSize))
                                                    {
                                                        if (Field[i + 3][j + 3] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if (((j + 1) < fieldSize) && ((i + 1) < fieldSize))
                            {
                                if (Field[i + 1][j + 1] == Field[i][j])
                                {
                                    if (((j + 2) < fieldSize) && ((i + 2) < fieldSize))
                                    {
                                        if (Field[i + 2][j + 2] == Field[i][j])
                                        {
                                            if (((j + 3) < fieldSize) && ((i + 3) < fieldSize))
                                            {
                                                if (Field[i + 3][j + 3] == Field[i][j])
                                                {
                                                    if (((j + 4) < fieldSize) && ((i + 4) < fieldSize))
                                                    {
                                                        if (Field[i + 4][j + 4] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // Проверка по условно побочной диагонали

                            if (((j + 1) < fieldSize) && ((i - 1) >= 0))
                            {
                                if (Field[i - 1][j + 1] == Field[i][j])
                                {
                                    if (((j + 2) < fieldSize) && ((i - 2) >= 0))
                                    {
                                        if (Field[i - 2][j + 2] == Field[i][j])
                                        {
                                            if (((j + 3) < fieldSize) && ((i - 3) >= 0))
                                            {
                                                if (Field[i - 3][j + 3] == Field[i][j])
                                                {
                                                    if (((j + 4) < fieldSize) && ((i - 4) >= 0))
                                                    {
                                                        if (Field[i - 4][j + 4] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                    if (((j - 1) >= 0) && ((i + 1) < fieldSize))
                                                    {
                                                        if (Field[i + 1][j - 1] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                            if (((j - 1) >= 0) && ((i + 1) < fieldSize))
                                            {
                                                if (Field[i + 1][j - 1] == Field[i][j])
                                                {
                                                    if (((j - 2) >= 0) && ((i + 2) < fieldSize))
                                                    {
                                                        if (Field[i + 2][j - 2] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (((j - 1) >= 0) && ((i + 1) < fieldSize))
                                    {
                                        if (Field[i + 1][j - 1] == Field[i][j])
                                        {
                                            if (((j - 2) >= 0) && ((i + 2) < fieldSize))
                                            {
                                                if (Field[i + 2][j - 2] == Field[i][j])
                                                {
                                                    if (((j - 3) >= 0) && ((i + 3) < fieldSize))
                                                    {
                                                        if (Field[i + 3][j - 3] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if (((j - 1) >= 0) && ((i + 1) < fieldSize))
                            {
                                if (Field[i + 1][j - 1] == Field[i][j])
                                {
                                    if (((j - 2) >= 0) && ((i + 2) < fieldSize))
                                    {
                                        if (Field[i + 2][j - 2] == Field[i][j])
                                        {
                                            if (((j - 3) >= 0) && ((i + 3) < fieldSize))
                                            {
                                                if (Field[i + 3][j - 3] == Field[i][j])
                                                {
                                                    if (((j - 4) >= 0) && ((i + 4) < fieldSize))
                                                    {
                                                        if (Field[i + 4][j - 4] == Field[i][j])
                                                        {
                                                            winnerOutput(i, j);
                                                            return;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            //
                        }
                        if (numOfCurTurn == fieldSize * fieldSize)
                        {
                            drawOutput();
                            return;
                        }
                        //
                        return;
                    }
                }
                else
                {
                x1 += cellWidth;
                }
            }
            x1 = 270;
            y1 += cellHeight;
        }
    }
}

void QtApplication::mouseMoveEvent(QMouseEvent* e)
{
    if (fieldSize >= 5)
    {
        int x = 270;
        int y = 14;

        for (int i = 0; i < fieldSize; i++)
        {
            for (int j = 0; j < fieldSize; j++)
            {
                bufRectMouseMove = new QRect(x, y, cellWidth, cellHeight);

                int ii = -1;
                int jj = -1;
                
                if (((e->x() - 270) >= 0) && (((e->x() - 270) / cellWidth) < fieldSize))
                {
                    jj = ceil((e->x() - 270) / cellWidth);
                }
                else
                {
                    update();
                    return;
                }
                if (((e->y() - 14) >= 0) && (((e->y() - 14) / cellHeight) < fieldSize))
                {
                   ii = ceil((e->y() - 14) / cellHeight);
                }
                else
                {
                    update();
                    return;
                }

                if ((bufRectMouseMove->contains(e->x(), e->y())) && (Field[ii][jj] == 0))
                {
                    if (iRect != i || jRect != j)
                    {
                        update();
                        iRect = i;
                        jRect = j;
                    }
                    update(*bufRectMouseMove);
                    return;
                }
                else
                {
                    if (Field[ii][jj] != 0)
                    {
                        update();
                    }
                    x += cellWidth;
                }
            }
            x = 270;
            y += cellHeight;
        }
        iRect = -1;
        jRect = -1;
    }
}

void QtApplication::winnerOutput(int i, int j)
{
    if (Field[i][j] == 1)
    {
        QMessageBox::information(this, "Congratulations!", "Noughts won!\nYou can start a new game now.");
    }
    else if (Field[i][j] == 2)
    {
        QMessageBox::information(this, "Congratulations!", "Crosses won!\nYou can start a new game now.");
    }
    playBtn->setEnabled(true);
    restartGameBtn->setEnabled(false);
    fieldSize = 0;
    numOfCurTurn = 0;
    currentTurnLine->setPlaceholderText(tr(""));
    for (int i = 0; i < fieldSize; i++)
    {
        for (int j = 0; j < fieldSize; j++)
        {
            Field[i][j] = 0;
            cellField[i][j] = new QRect(0, 0, 0, 0);
        }
    }
    update();
};

void QtApplication::drawOutput()
{
    QMessageBox::information(this, "Draw!", "Nobody won!\nYou can start a new game now.");
    playBtn->setEnabled(true);
    restartGameBtn->setEnabled(false);
    fieldSize = 0;
    numOfCurTurn = 0;
    currentTurnLine->setPlaceholderText(tr(""));
    for (int i = 0; i < fieldSize; i++)
    {
        for (int j = 0; j < fieldSize; j++)
        {
            Field[i][j] = 0;
            cellField[i][j] = new QRect(0, 0, 0, 0);
        }
    }
    update();
};