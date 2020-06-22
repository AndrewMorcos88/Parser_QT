#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include <QGraphicsItem>
#include <QList>
#include "node.h"
#include "graphics.h"

class Graphics;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class GraphicsEdge;

class GraphicsNode :public QGraphicsItem
{
public:
    GraphicsNode(Graphics *graphicsView,Node* n);
    void addEdge(GraphicsEdge *edge);
    QList<GraphicsEdge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


public:
    Graphics *parent;
    Node* node;
    QPointF newPos;
    int nodeWidth;
    int nodeHight;
    int widthLevel;
    int heightLevel;
    QList<GraphicsEdge *> edgeList;

};

#endif // GRAPHICSNODE_H
