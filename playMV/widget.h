#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QVideoWidget>
#include<QMediaPlayer>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //播放
    void play();
    //播放状态
    void mediaStateChanged(QMediaPlayer::State state);
    //改变播放位置
    void positionChanged(qint64 position);
    //获取播放位置
    void setPosition(int position );
    //获取媒体播放长度
    void durationChanged(qint64 position);
    //抛出播放异常槽函数
    void handleError();




private:
    Ui::Widget *ui;
    QMediaPlayer *mediaPlayer;//QVideoWidget中播放

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_toolButton_clicked();



    void on_horizontalSlider_sliderMoved(int position);
    void on_toolButton_2_clicked();
};

#endif // WIDGET_H
