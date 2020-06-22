/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphics.h"
#include "graphicsedge.h"
#include "graphicsnode.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

//! [0]
Graphics::Graphics(QWidget *parent)
     : QGraphicsView(new QGraphicsScene, parent), timerId(0)
{
    this->setMouseTracking(true);
    this->setBackgroundRole(QPalette::Base);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0,1600,800);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->scale(qreal(0.8), qreal(0.8));
    this->setMinimumSize(650, 650);
    this->showMaximized();
    widthMargin = 150;
    hieghtMargin = 100;
//! [0]

//! [1]


}
//! [1]
//!
void Graphics::drawNodes(Node* root)
{
    GraphicsNode* RootNode = new GraphicsNode(this,root);
    QString tooltiptext;
    tooltiptext = "<html><body><h4>"+ root->token.tokenType  +"</h4>"
                  "<h4>" + root->token.tokenValue + "</h4>";
    RootNode->setToolTip(tooltiptext);
    RootNode->heightLevel = 50;
    RootNode->widthLevel = 200;
    allNodes.push_back(RootNode);
    RootNode->moveBy(RootNode->widthLevel,RootNode->heightLevel);
    scene->addItem(RootNode);
    GraphicsNode* ChildNode;
    GraphicsEdge* edge;
    if(root->Childrens.size()==3){
        ChildNode = drawNode(root->Childrens[0],RootNode->widthLevel-widthMargin,RootNode->heightLevel+hieghtMargin);
        edge = new GraphicsEdge(RootNode,ChildNode);
        scene->addItem(edge);
        ChildNode = drawNode(root->Childrens[1],RootNode->widthLevel,RootNode->heightLevel+hieghtMargin);
        edge = new GraphicsEdge(RootNode,ChildNode);
        scene->addItem(edge);
        ChildNode = drawNode(root->Childrens[2],RootNode->widthLevel+widthMargin,RootNode->heightLevel+hieghtMargin);
        edge = new GraphicsEdge(RootNode,ChildNode);
        scene->addItem(edge);
    }
    if(root->Childrens.size()==2){
        ChildNode = drawNode(root->Childrens[0],RootNode->widthLevel-widthMargin,RootNode->heightLevel+hieghtMargin);
        edge = new GraphicsEdge(RootNode,ChildNode);
        scene->addItem(edge);
        ChildNode = drawNode(root->Childrens[1],RootNode->widthLevel+widthMargin,RootNode->heightLevel+hieghtMargin);
        edge = new GraphicsEdge(RootNode,ChildNode);
        scene->addItem(edge);
    }
    if(root->Childrens.size()==1){
        ChildNode = drawNode(root->Childrens[0],RootNode->widthLevel,RootNode->heightLevel+hieghtMargin);
        edge = new GraphicsEdge(RootNode,ChildNode);
        scene->addItem(edge);
    }
    if(root->Expression_Expression && root->Sibling!=nullptr){
         GraphicsNode* siblingNode= drawNode(root->Sibling,RootNode->widthLevel+widthMargin,RootNode->heightLevel);
         edge = new GraphicsEdge(RootNode,siblingNode);
         scene->addItem(edge);
    }
}

GraphicsNode* Graphics::drawNode(Node* node,int wLevel,int HeightLevel){
     GraphicsNode* Gnode = new GraphicsNode(this,node);
     QString tooltiptext;
     tooltiptext = "<html><body><h4>"+ node->token.tokenType  +"</h4>"
                   "<h4>" + node->token.tokenValue + "</h4>";
     Gnode->setToolTip(tooltiptext);
     Gnode->heightLevel = HeightLevel;
     Gnode->widthLevel = wLevel;
     Gnode->moveBy(Gnode->widthLevel,Gnode->heightLevel);
     checkNodeCollison(Gnode);
     allNodes.push_back(Gnode);
     scene->addItem(Gnode);
     GraphicsNode* ChildNode;
     GraphicsEdge* edge;
     if(Gnode->node->Childrens.size()==3){
         ChildNode = drawNode(Gnode->node->Childrens[0],Gnode->widthLevel-widthMargin,Gnode->heightLevel+hieghtMargin);
         edge = new GraphicsEdge(Gnode,ChildNode);
         scene->addItem(edge);
         ChildNode = drawNode(Gnode->node->Childrens[1],Gnode->widthLevel,Gnode->heightLevel+hieghtMargin);
         edge = new GraphicsEdge(Gnode,ChildNode);
         scene->addItem(edge);
         ChildNode = drawNode(Gnode->node->Childrens[2],Gnode->widthLevel+widthMargin,Gnode->heightLevel+hieghtMargin);
         edge = new GraphicsEdge(Gnode,ChildNode);
         scene->addItem(edge);
     }
     if(Gnode->node->Childrens.size()==2){
         ChildNode = drawNode(Gnode->node->Childrens[0],Gnode->widthLevel-widthMargin,Gnode->heightLevel+hieghtMargin);
         edge = new GraphicsEdge(Gnode,ChildNode);
         scene->addItem(edge);
         ChildNode = drawNode(Gnode->node->Childrens[1],Gnode->widthLevel+widthMargin,Gnode->heightLevel+hieghtMargin);
         edge = new GraphicsEdge(Gnode,ChildNode);
         scene->addItem(edge);
     }
     if(Gnode->node->Childrens.size()==1){
         ChildNode = drawNode(Gnode->node->Childrens[0],Gnode->widthLevel,Gnode->heightLevel+hieghtMargin);
         edge = new GraphicsEdge(Gnode,ChildNode);
         scene->addItem(edge);
     }
     if(Gnode->node->Expression_Expression && Gnode->node->Sibling !=nullptr ){
          GraphicsNode* siblingNode= drawNode(Gnode->node->Sibling,Gnode->widthLevel+widthMargin+widthMargin,Gnode->heightLevel);
          edge = new GraphicsEdge(Gnode,siblingNode);
          scene->addItem(edge);
     }
     return  Gnode;
}

void Graphics::checkNodeCollison(GraphicsNode *Gnode)
{
    for(int i=0;i<allNodes.size();i++){
        if(Gnode->widthLevel==allNodes[i]->widthLevel && Gnode->heightLevel == allNodes[i]->heightLevel){
            Gnode->moveBy(widthMargin,0);
            Gnode->widthLevel +=widthMargin;
        }
    }
}

//! [2]
void Graphics::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}


//! [2]

//! [3]
void Graphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        root->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        root->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        root->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        root->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void Graphics::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<GraphicsNode *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (GraphicsNode *node = qgraphicsitem_cast<GraphicsNode *>(item))
            nodes << node;
    }

    foreach (GraphicsNode *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (GraphicsNode *node, nodes) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void Graphics::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void Graphics::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Hover on Nodes to see its details,Zoom with the mouse "
                       "wheel or the '+' and '-' keys, "));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}
//! [6]

//! [7]
void Graphics::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void Graphics::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<GraphicsNode *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(1200), -150 + QRandomGenerator::global()->bounded(1200));
    }
}

void Graphics::zoomIn()
{
    scaleView(qreal(1.2));
}

void Graphics::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

