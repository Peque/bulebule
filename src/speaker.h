#ifndef __SPEAKER_H
#define __SPEAKER_H

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <libopencm3/stm32/timer.h>

#include "setup.h"

void speaker_play(char note, uint8_t octave, int8_t accidental, float duration);
void speaker_play_score(char *score);
void speaker_play_score2(char *score);

#endif /* __SPEAKER_H */
