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

#include <stdio.h>
#include <getopt.h>

#include <QApplication>

#include "fonttest.h"

static const char* shortOpts = "w:h:f:";

static struct option longOpts[] =
{
    { "width",  required_argument,  0,  'w' },
    { "height", required_argument,  0,  'h' },
    { "file",   required_argument,  0,  'f' },
    { 0, 0, 0, 0 }
};

void
usage(const char* prog)
{
    fprintf(stderr, "Usage: %s [option ...]\n", prog);
    fprintf(stderr, "Valid options are:\n\
-w, --width width   Scene width\n\
                    Default: 1280\n\
-h, --height height Scene height\n\
                    Default: 720\n\
-f, --file file     Input file to display in scene\n\
                    Default: all CC characters in 15x32 grid\n\
");
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    argc = QCoreApplication::argc();
    argv = QCoreApplication::argv();

    int c;
    int index = 0;
    int width = WIDTH;
    int height = HEIGHT;
    char* file = 0;

    while ((c = getopt_long(argc, argv, shortOpts, longOpts, &index)) != -1)
    {
        switch (c)
        {
            case 'w':
                width = atoi(optarg);
                if (width < 32)
                {
                    usage(argv[0]);
                    exit(1);
                }
                break;
            case 'h':
                height = atoi(optarg);
                if (height < 15)
                {
                    usage(argv[0]);
                    exit(1);
                }
                break;
            case 'f':
                file = strdup(optarg);
                break;
            default:
                usage(argv[0]);
                exit(1);
                break;
        }
    }

    FontTest window(width, height, file);
    window.show();
    return app.exec();
}
