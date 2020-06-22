#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "node.h"


class GraphicsNode;class GraphicsEdge ;

class Graphics : public QGraphicsView
{
    Q_OBJECT

public:
    Graphics(QWidget *parent = 0);

    void itemMoved();
    void drawNodes(Node* root);
    GraphicsNode* drawNode(Node* node,int wLevel,int HeightLevel);
    void checkNodeCollison(GraphicsNode* Gnode);
    void drawBackground(QPainter *painter, const QRectF &rect) override;

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    GraphicsNode *root;
    QGraphicsScene *scene;
    QVector<float> graphicsCentrality;
    QVector<GraphicsNode *> Nodes;
    QVector<GraphicsEdge *> Edges;
    int widthMargin;
    int hieghtMargin;
    QVector<GraphicsNode*> allNodes;


};

#endif // GRAPHICS_H
