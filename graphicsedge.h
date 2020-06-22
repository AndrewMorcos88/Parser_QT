#ifndef GRAPHICSEDGE_H
#define GRAPHICSEDGE_H


#include <QGraphicsItem>

class GraphicsNode;

class GraphicsEdge:public QGraphicsItem
{
public:
    GraphicsEdge(GraphicsNode *sourceNode, GraphicsNode *destNode);

    GraphicsNode *sourceNode() const;
    GraphicsNode *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    GraphicsNode *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // GRAPHICSEDGE_H
