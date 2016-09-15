#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

#include "singlegamemode.h"
#include "blocktype.h"


class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    static QImage blockSkins[16];
    static bool initialized;
    BlockType blockType;
    bool allowMatch;
public:
    static void Initialize();
    explicit Block(BlockType blockType = RED, int posX = 200, int posY = 600
            , bool allowMatch = false, QTimer* moveTimer = new QTimer());
    ~Block();

    BlockType getBlockType() const;
    void setBlockType(const BlockType &value);

    bool getAllowMatch() const;
    void setAllowMatch(bool value);
    QPointF center();

    BlockType getMatchType() const;

signals:

public slots:
    void move();

friend class SingleGameMode;
friend class TetrisAttackClone;
};

#endif // BLOCK_H
