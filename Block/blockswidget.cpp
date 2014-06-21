#include "blockswidget.h"

BlocksWidget::BlocksWidget(QWidget* parent):
       QWidget(parent)
{

    _items = JsonHandle::getInstance()->parserConfigJson(BlockConfigPath,JsonHandle::ConfigFile);
    qDebug() << "items is size" <<  _items.size();

    setAutoFillBackground(true);
    setGeometry(50,50,140+20,_items.size()/2*70+5*_items.size());
    setMaximumSize(140+20,_items.size()/2*70+5*_items.size());
    _gridLayout = new QGridLayout(this);
    blocksInit();

}
void BlocksWidget:: blocksInit()
{
    int row = 0;
    for(int i = 0 ; i < _items.size() ; i++)
    {

        int column =i % 2;
        BlockButton* block = new BlockButton(_items.at(i),this);
        connect(block,SIGNAL(Click(GeneralBlock*)),this,SIGNAL(Clicked(GeneralBlock*)));
        if (i % 2 == 0 && i != 0)
        {
            row++;
        }
        _gridLayout->addWidget(block,row,column);
    }


}
