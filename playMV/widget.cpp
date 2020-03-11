#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QDebug>
#include<QFileDialog>
#include<QString>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建meidaPalyer
    mediaPlayer=new QMediaPlayer(this);
    //设置mediaPlayer的QVideoWIdget
    mediaPlayer->setVideoOutput(ui->widget);

    //设置播放属性
    //1）播放暂停信息改变
    connect(mediaPlayer,&QMediaPlayer::stateChanged,this,&Widget::mediaStateChanged);
    //2)播放位置变换，随着改变进度条
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,&Widget::positionChanged);
    //3）媒体播放长度信号变换
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,&Widget::durationChanged);
    //4)播放异常处理
    connect(mediaPlayer,static_cast<void (QMediaPlayer:: *)(QMediaPlayer::Error)>(&QMediaPlayer::error) ,this,&Widget::handleError);

    //设置按钮暂停格式
    ui->toolButton->setToolTip("暂停");
    ui->toolButton->setIcon(QPixmap(":/new/prefix1/images/u=1648998499,165919943&fm=26&gp=0.jpg"));

    //使按钮自动去掉背景
    ui->toolButton->setAutoRaise(true);
    ui->toolButton_2->setAutoRaise(true);

    //设置播放内容
    //mediaPlayer->setMedia(QUrl::fromLocalFile(":D/VID_20191213_202728(0).mp4"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    //给主界面设置背景
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(), QPixmap(":/new/prefix1/images/u=2399101105,962006484&fm=26&gp=0.jpg"));
}

void Widget::play()
{

    //获取播放状态
    switch (mediaPlayer->state()) {
    case QMediaPlayer::PlayingState://如果是播放状态
        mediaPlayer->pause();//暂停
        break;
    default:
        mediaPlayer->play();//播放
        break;
    }

}

void Widget::on_toolButton_clicked()
{
      play();
}

void Widget::mediaStateChanged(QMediaPlayer::State state)
{
    //播放过程中暂停与开始的变换
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->toolButton->setToolTip("暂停");
        ui->toolButton->setIcon(QPixmap(":/new/prefix1/images/u=1129145644,412791288&fm=26&gp=0.jpg"));
        break;
    default:
        ui->toolButton->setToolTip("播放");
        ui->toolButton->setIcon(QPixmap(":/new/prefix1/images/u=1648998499,165919943&fm=26&gp=0.jpg")
                                );
        break;
    }
}

void Widget::positionChanged(qint64 position)
{
    //改变进度条播放位置
    ui->horizontalSlider->setValue(position);
}

void Widget::setPosition(int position)
{
    //获取meidaPlayer进度条位置
    mediaPlayer->setPosition(position);
}

void Widget::durationChanged(qint64 position)//posotion 为最大长度
{
    //设置进度条范围
    ui->horizontalSlider->setRange(0,position);
}

void Widget::handleError()
{
    //异常抛出处理
    //将播放按钮设置为不可按下
    ui->toolButton->setEnabled(false);
}


//根据进度条位置调整视频播放位置
void Widget::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}

void Widget::on_toolButton_2_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    //设置播放内容
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    ui->toolButton->setEnabled(true);


}
