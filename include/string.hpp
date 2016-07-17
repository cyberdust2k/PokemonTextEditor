/*
 *      PokemonTextEditor (PTE)
 *      Éditeur de texte pour les jeux de Pokémon de génération III
 *      Copyright (C) 2016-2017 HopelessFrench
 *      License: General Public License 3.0
 */


#ifndef PTESTRING
#define PTESTRING


/* Included headers */
#include <QString>


extern void loadtable();
extern const QString readpokestring(uchar *rom, uint offset, bool beg = false);
extern void writepokestring(uchar *rom, uint offset, const QString &str);
extern QByteArray getstringbytes(const QString &str);


#endif
