#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <QSoundEffect>

#include "soundtype.h"

class SoundEffects
{
    static QSoundEffect soundEffects[9];
    static bool initialized;
public:
    SoundEffects();
    static void Initialize();

    static QSoundEffect* getSoundEffect(SoundType);
    static void stopPlayingAllSounds();
};

#endif // SOUNDEFFECTS_H
