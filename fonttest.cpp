/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
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

#include <string.h>
#include <errno.h>

#include <QtGui>

#include "fonttest.h"

static QMap<int, QString> weights;

static void
initWeights()
{
    weights[1]              = "ultralight";
    weights[QFont::Light]   = "light";
    weights[QFont::Normal]  = "normal";
    weights[QFont::DemiBold]= "demibold";
    weights[QFont::Bold]    = "bold";
    weights[QFont::Black]   = "black";
    weights[99]             = "ultrablack";
}

static QMap<int, QString> stretchMap;

static void
initStretchMap()
{
    stretchMap[QFont::UltraCondensed]   = "ultracondensed";
    stretchMap[QFont::ExtraCondensed]   = "extracondensed";
    stretchMap[QFont::Condensed]        = "condensed";
    stretchMap[QFont::SemiCondensed]    = "semicondensed";
    stretchMap[QFont::Unstretched]      = "unstretched";
    stretchMap[QFont::SemiExpanded]     = "semiexpanded";
    stretchMap[QFont::Expanded]         = "expanded";
    stretchMap[QFont::ExtraExpanded]    = "extraexpanded";
    stretchMap[QFont::UltraExpanded]    = "ultraexpanded";
}

static QString
getText(const char* fileName)
{
    if (fileName != 0)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            fprintf(stderr, "%s: %s\n", fileName, strerror(errno));
        }
        else
        {
            QTextStream in(&file);
            return in.readAll();
        }
    }
    return QString::fromUtf8("Standard Characters\n\
 !\"#$%&'()\303\241+,-./0123456789:;<=>?\n\
@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\303\251]\303\255\303\263\n\
\303\272abcdefghijklmnopqrstuvwxyz\303\247\303\267\303\221\303\261\342\226\210\n\
Special Characters\n\
\302\256\302\260\302\275\302\277\342\204\242\302\242\302\243\342\231\252\
\303\240 \303\250\303\242\303\252\303\256\303\264\303\273\
\302\256\302\260\302\275\302\277\342\204\242\302\242\302\243\342\231\252\
\303\240 \303\250\303\242\303\252\303\256\303\264\303\273\n\
Extended Characters\n\
\303\201\303\211\303\223\303\232\303\234\303\274\342\200\230\302\241\
*\342\200\231\342\200\224\302\251\342\204\240\342\200\242\342\200\234\342\200\235\
\303\200\303\202\303\207\303\210\303\212\303\213\303\253\303\216\
\303\217\303\257\303\224\303\231\303\271\303\233\302\253\302\273\n\
\303\203\303\243\303\215\303\214\303\254\303\222\303\262\303\225\
\303\265{}\\^_\302\246~\
\303\204\303\244\303\226\303\266\303\237\302\245\302\244|\
\303\205\303\245\303\230\303\270\342\214\234\342\214\235\342\214\236\342\214\237\n\
Special Characters\n\
\302\256\302\260\302\275\302\277\342\204\242\302\242\302\243\342\231\252\
\303\240 \303\250\303\242\303\252\303\256\303\264\303\273\
\302\256\302\260\302\275\302\277\342\204\242\302\242\302\243\342\231\252\
\303\240 \303\250\303\242\303\252\303\256\303\264\303\273\n\
Standard Characters\n\
 !\"#$%&'()\303\241+,-./0123456789:;<=>?\n\
@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\303\251]\303\255\303\263\n\
\303\272abcdefghijklmnopqrstuvwxyz\303\247\303\267\303\221\303\261\342\226\210\
");
}

FontTest::FontTest(int w, int h, const char* file)
{
    width = w;
    height = h;
    setWindowTitle("Font Test");

    QWidget *centralWidget = new QWidget;

    QLabel *fontLabel = new QLabel(tr("Font:"));
    fontCombo = new QFontComboBox;
    displayFont = fontCombo->currentFont();

    QLabel *sizeLabel = new QLabel(tr("Size:"));
    sizeBox = new QSpinBox;
    sizeBox->setRange(6,60);
    sizeBox->setValue(QFontInfo(displayFont).pixelSize());

    QLabel *weightLabel = new QLabel(tr("Weight:"));
    weightCombo = new QComboBox;
    initWeights();
    QMapIterator<int, QString> iw(weights);
    while (iw.hasNext())
    {
        iw.next();
        weightCombo->addItem(iw.value());
    }
    weightCombo->setCurrentIndex(weightCombo->findText("normal"));
    displayFont.setWeight(QFont::Normal);

    QLabel *stretchLabel = new QLabel(tr("Stretch:"));
    stretchCombo = new QComboBox;
    initStretchMap();
    QMapIterator<int, QString> is(stretchMap);
    while (is.hasNext())
    {
        is.next();
        stretchCombo->addItem(is.value());
    }
    stretchCombo->setCurrentIndex(stretchCombo->findText("unstretched"));
    displayFont.setStretch(QFont::Unstretched);

    QLabel *italicLabel = new QLabel(tr("Italic:"));
    italicBox = new QCheckBox;
    italicBox->setChecked(displayFont.italic());

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width, height);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->addRect(0, 0, width, height, QPen(Qt::red));
    boundRect = scene->addRect(0, 0,  width, height, QPen(Qt::green), QBrush(Qt::black));
    textItem = scene->addText(getText(file));
    textItem->setDefaultTextColor(Qt::white);
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    QTextDocument* doc = textItem->document();
    doc->setDocumentMargin(0);

    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->centerOn(width/2, height/2);

    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(updateFont(QFont)));
    connect(sizeBox, SIGNAL(valueChanged(int)),
            this, SLOT(updateSize(int)));
    connect(weightCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(updateWeight(QString)));
    connect(stretchCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(updateStretch(QString)));
    connect(italicBox, SIGNAL(toggled(bool)),
            this, SLOT(updateItalic(bool)));

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(fontLabel);
    controlsLayout->addWidget(fontCombo, 1);
    controlsLayout->addWidget(sizeLabel);
    controlsLayout->addWidget(sizeBox, 1);
    controlsLayout->addWidget(weightLabel);
    controlsLayout->addWidget(weightCombo, 1);
    controlsLayout->addWidget(stretchLabel);
    controlsLayout->addWidget(stretchCombo, 1);
    controlsLayout->addWidget(italicLabel);
    controlsLayout->addWidget(italicBox, 1);
    controlsLayout->addStretch(1);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
    centralLayout->addWidget(view);
    centralLayout->addSpacing(4);
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);
    updateFont(displayFont.family());

    QSizeF size = doc->size();
    resize((int)size.width(), (int)(size.height()*1.4));
}

void FontTest::fontUpdate()
{
    textItem->setFont(displayFont);
    textItem->adjustSize();
    QSizeF size = textItem->document()->size();
    QRectF rect((width-size.width())/2, (height-size.height())/2, size.width(), size.height());
    textItem->setPos(rect.topLeft());
    boundRect->setRect(rect);

    update();
    print();
}

void
FontTest::print()
{
    QTextDocument* doc = textItem->document();

    QSizeF size= doc->size();
    printf("size=%.2fx%.2f pixelSize=%d average char size=%.2fx%.2f\n",
        size.width(), size.height(), QFontInfo(displayFont).pixelSize(),
        size.width()/COLS, size.height()/ROWS);

    // Integer metrics
    QFontMetrics fm(displayFont);
    printf("height=%d leading=%d ascent=%d descent=%d\n",
        fm.height(), fm.leading(), fm.ascent(), fm.descent());
    printf("averageCharWidth=%d maxWidth=%d lineSpacing=%d\n",
        fm.averageCharWidth(), fm.maxWidth(), fm.lineSpacing());

    // Floating point metrics
    QFontMetricsF fmf(displayFont);
    printf("height=%.2f leading=%.2f ascent=%.2f descent=%.2f\n",
        fmf.height(), fmf.leading(), fmf.ascent(), fmf.descent());
    printf("averageCharWidth=%.2f maxWidth=%.2f lineSpacing=%.2f\n",
        fmf.averageCharWidth(), fmf.maxWidth(), fmf.lineSpacing());

}

void FontTest::updateFont(const QFont &font)
{
    QString family = font.family();
    printf("updateFont(%s)\n", qPrintable(family));
    displayFont.setFamily(family);
    // Pick a pixel size that will fit in a 90% title safe area
    int pixelSize = height * 9 / ROWS / 10;
    displayFont.setPixelSize(pixelSize);
    QFontMetrics fm(displayFont);
    int fontHeight = fm.height();
    if (fontHeight < fm.lineSpacing())
        fontHeight = fm.lineSpacing();
    int offBy = fontHeight - pixelSize;
    int newPixelSize = pixelSize;
    if (offBy != 0)
    {
        newPixelSize = pixelSize * pixelSize / fontHeight;
        displayFont.setPixelSize(newPixelSize);
    }
    printf("First pixelSize=%d fontHeight=%d offBy=%d newPixelSize=%d\n",
        pixelSize, fontHeight, offBy, newPixelSize);
    fontUpdate();
    sizeBox->setValue(QFontInfo(displayFont).pixelSize());
}

void FontTest::updateSize(int size)
{
    printf("updateSize(%d)\n", size);
    displayFont.setPixelSize(size);
    fontUpdate();
}

void FontTest::updateWeight(const QString &weight)
{
    printf("updateWeight(%s)\n", qPrintable(weight));
    displayFont.setWeight(weights.key(weight));
    fontUpdate();
}

void FontTest::updateStretch(const QString &stretch)
{
    printf("updateStretch(%s)\n", qPrintable(stretch));
    displayFont.setStretch(stretchMap.key(stretch));
    fontUpdate();
}

void FontTest::updateItalic(bool enable)
{
    printf("updateItalic(%d)\n", enable);
    displayFont.setItalic(enable);
    fontUpdate();
}

