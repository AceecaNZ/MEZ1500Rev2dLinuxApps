#include "inputdevice.h"
#include <QVariant>
#include <QValidator>

InputDevice::InputDevice()
{
    keyboard = new Keyboard;
    numpad = new Numpad;
    keyboard->setObjectName("keyboard");
    numpad->setObjectName("numpad");
    connect(keyboard,SIGNAL(dataSet(QVariant*)),this,SLOT(dataSet(QVariant*)));
    connect(numpad,SIGNAL(dataSet(QVariant*)),this,SLOT(dataSet(QVariant*)));
    qApp->installEventFilter(this);
}

bool InputDevice::eventFilter(QObject *obj,  QEvent *event)
{
    QString tmpClassName;
    if (event->type() == QEvent::RequestSoftwareInputPanel)
    {
        if (obj != NULL)
        {
            if (obj->property("enabled").toBool())
            {
                tmpClassName=obj->metaObject()->className();
                if (obj->property("keyboard").toBool())
                {
                    if (tmpClassName == "QLineEdit")
                    {
                        currentEditType = tQLineEdit;
                        tmpEditObj=obj;
                        const QValidator * tmpValidator = static_cast<QLineEdit *>(tmpEditObj)->validator();
                        if (qobject_cast<const QDoubleValidator *>(tmpValidator) || qobject_cast<const QIntValidator *>(tmpValidator))
                        {
                            updatePosition();
                            numpad->activate(getText(),static_cast<QLineEdit *>(tmpEditObj)->validator());
                            numpad->setEchoMode(static_cast<QLineEdit *>(tmpEditObj)->echoMode());
                        }
                        else
                        {
                            updatePosition();
                            keyboard->activate(getText(),obj->property("maxLength").toInt(),false);
                            keyboard->setEchoMode(static_cast<QLineEdit *>(tmpEditObj)->echoMode());
                            keyboard->setValidator(static_cast<QLineEdit *>(tmpEditObj)->validator());
                        }
                    }
                }
            }
        }
        return true;
    }
    else if (event->type() == QEvent::CloseSoftwareInputPanel)
    {
            numpad->close();
            keyboard->close();
            return true;
    }
    return false;
}

QString InputDevice::getText()
{
    switch(currentEditType)
    {
        case tQLineEdit:
            return qobject_cast<QLineEdit *>(tmpEditObj)->text();
        break;
        default:
            return "";
    }
}

void InputDevice::setText(QString text)
{
    switch(currentEditType)
    {
        case tQLineEdit:
            qobject_cast<QLineEdit *>(tmpEditObj)->setText(text);
        break;
    }
}

void InputDevice::dataSet(QVariant * data)
{
    setText(data->toString());
}


void InputDevice::updatePosition()
{
    QWidget *widget = focusWidget();
    if (!widget)
        return;

    QRect widgetRect = widget->rect();
    QPoint panelPos = QPoint(widgetRect.left(), widgetRect.bottom() + 2);
    panelPos = widget->mapToGlobal(panelPos);
    keyboard->move(panelPos);
    numpad->move(panelPos);
}


QString InputDevice::identifierName()
{
    return "InputDevice";
}

void InputDevice::reset()
{
}

bool InputDevice::isComposing() const
{
    return false;
}

QString InputDevice::language()
{
    return "en_US";
}
