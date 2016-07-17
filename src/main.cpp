/*
 *      PokemonTextEditor (PTE)
 *      Éditeur de texte pour les jeux de Pokémon de génération III
 *      Copyright (C) 2016-2017 HopelessFrench
 *      License: General Public License 3.0
 */


/* Included headers */
#include <QApplication>
#include <QStyleFactory>
#include <mainwindow.h>


/* Application entry point */
int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);

#ifdef Q_OS_UNIX
    // Specifies the fusion style for unix systems
    QApplication::setStyle(QStyleFactory::create("fusion"));
#endif

    MainWindow window(NULL);
    window.show();
    qapp.exec();
}
