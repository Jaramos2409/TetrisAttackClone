#include <QApplication>

#include "soundeffects.h"
#include "soundtype.h"

//static definitions
QSoundEffect SoundEffects::soundEffects[9];
bool SoundEffects::initialized = false;

SoundEffects::SoundEffects()
{

}

void SoundEffects::Initialize()
{
    if (initialized) return;
    initialized = true;

    soundEffects[LOSING].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                       +"/sfx/losing_sound.wav"));
    soundEffects[LOSING].setLoopCount(QSoundEffect::Infinite);
    soundEffects[LOSING].setVolume(1.0f);

    soundEffects[GAMEEND].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/end_game.wav"));
    soundEffects[GAMEEND].setLoopCount(1);
    soundEffects[GAMEEND].setVolume(1.0f);

    soundEffects[MATCHED].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/block_match1.wav"));
    soundEffects[MATCHED].setLoopCount(1);
    soundEffects[MATCHED].setVolume(1.0f);

    soundEffects[REMOVEMATCH].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/remove_match.wav"));
    soundEffects[REMOVEMATCH].setLoopCount(1);
    soundEffects[REMOVEMATCH].setVolume(1.0f);

    soundEffects[SWAPBLOCKS].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/swap_blocks.wav"));
    soundEffects[SWAPBLOCKS].setLoopCount(1);
    soundEffects[SWAPBLOCKS].setVolume(0.5f);

    soundEffects[SPECIALMATCH].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/special_match.wav"));
    soundEffects[SPECIALMATCH].setLoopCount(1);
    soundEffects[SPECIALMATCH].setVolume(0.5f);

    soundEffects[COUNTDOWN_SOUND].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/countdown.wav"));
    soundEffects[COUNTDOWN_SOUND].setLoopCount(1);
    soundEffects[COUNTDOWN_SOUND].setVolume(1.0f);


    soundEffects[GAMEPAUSE].setSource(QUrl::fromLocalFile(qApp->applicationDirPath()
                                                         +"/sfx/game_pause.wav"));
    soundEffects[GAMEPAUSE].setLoopCount(1);
    soundEffects[GAMEPAUSE].setVolume(1.0f);
}

QSoundEffect* SoundEffects::getSoundEffect(SoundType soundType)
{
    return &soundEffects[soundType];
}

void SoundEffects::stopPlayingAllSounds()
{
    for (int i = LOSING; i <= GAMEEND; i++)
    {
        soundEffects[i].stop();
    }
}
