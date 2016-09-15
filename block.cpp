#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include "block.h"

//static definitions
QImage Block::blockSkins[16];
bool Block::initialized = false;


void Block::Initialize()
{
    if (initialized) return;
    initialized = true;

    int x = 0;

    for (int i = RED; i <= SPECMATCHED; i++)
    {
        blockSkins[i] = QImage(":/blocks/_pieces.png").copy(x, 0, 20, 20).scaled(66, 66, Qt::KeepAspectRatio);
        x += 20;
    }

    blockSkins[8] = QImage(":/blocks/_pieces.png").copy(160, 0, 20, 20).scaled(66, 66, Qt::KeepAspectRatio);
    blockSkins[9] = QImage(":/blocks/_pieces.png").copy(120, 20, 20, 20).scaled(66, 66, Qt::KeepAspectRatio);

    x = 0;

    for (int i = REDMATCHED; i <= PURPLEMATCHED; i++)
    {
        blockSkins[i] = QImage(":/blocks/_pieces.png").copy(x, 20, 20, 20).scaled(66, 66, Qt::KeepAspectRatio);
        x += 20;
    }
}

Block::Block(BlockType blockType, int posX, int posY, bool allowMatch, QTimer* moveTimer)
{
    this->blockType = blockType;
    setPixmap(QPixmap::fromImage(blockSkins[blockType]));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setPos(posX,posY);
    show();

    this->allowMatch = allowMatch;

    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));

    if (this->blockType != EMPTY)
    {
        setOpacity(0.2);
    }

}

Block::~Block()
{

}

void Block::move()
{
    setPos(x(),y()-SingleGameMode::gameSpeed);
}



BlockType Block::getBlockType() const
{
    return blockType;
}

void Block::setBlockType(const BlockType &value)
{
    blockType = value;
    setPixmap(QPixmap::fromImage(blockSkins[blockType]));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    show();
}

bool Block::getAllowMatch() const
{
    return allowMatch;
}

void Block::setAllowMatch(bool value)
{
    allowMatch = value;
    setOpacity(1);
}

QPointF Block::center()
{
    double x = pos().x() + boundingRect().width()/2;
    double y = pos().y() + boundingRect().height()/2;
    QPointF center;
    center.setX(x);
    center.setY(y);
    return center;
}

BlockType Block::getMatchType() const
{
    BlockType result;

    switch(blockType)
    {
        case RED:
            result = REDMATCHED;
            break;
        case GREEN:
            result = GREENMATCHED;
            break;
        case BLUE:
            result = BLUEMATCHED;
            break;
        case YELLOW:
            result = YELLOWMATCHED;
            break;
        case ORANGE:
            result = ORANGEMATCHED;
            break;
        case PURPLE:
            result = PURPLEMATCHED;
            break;
    }

    return result;
}
