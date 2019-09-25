#pragma once

extern void uiSetupProgress(size_t stepCount);

/** Throws an exception when abortion is requested */
extern void uiAdvanceProgress(const std::string &stepName);

extern void uiTeardownProgress();

/** Progress is advanced each `checkProgressFrameInterval` frames when exporting
 * animation instead of each frame, due reduce the overhead of update the
 * progress UI */
const int checkProgressFrameInterval = 10;