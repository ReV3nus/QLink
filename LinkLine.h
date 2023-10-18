#ifndef LINKLINE_H
#define LINKLINE_H

#include <QWidget>
#include <QPainter>

class LinkLine : public QWidget {
public:
    LinkLine(QWidget *parent = nullptr) : QWidget(parent) {points.clear();}
    std::vector<QPoint>points;
    void AddPoint(int x,int y){points.push_back(QPoint(x,y));}
    void ClearPoints(){points.clear();}
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPen pen;
        pen.setColor(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        for(int i=0;i<points.size()-1;i++)
            painter.drawLine(points[i],points[i+1]);
    }
};

#endif // LINKLINE_H
